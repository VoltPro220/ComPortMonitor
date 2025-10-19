import serial
import serial.tools.list_ports
import threading
import time
import sys


class VirtualCOMPort:
    def __init__(self, port_name, baudrate=9600, bytesize=8, parity='N', stopbits=1, timeout=1):
        self.port_name = port_name
        self.baudrate = baudrate
        self.bytesize = bytesize
        self.parity = parity
        self.stopbits = stopbits
        self.timeout = timeout
        self.is_running = False
        self.serial_connection = None

    def start(self):
        """Запуск виртуального COM-порта"""
        try:
            # Пытаемся открыть порт
            self.serial_connection = serial.Serial(
                port=self.port_name,
                baudrate=self.baudrate,
                bytesize=self.bytesize,
                parity=self.parity,
                stopbits=self.stopbits,
                timeout=self.timeout
            )

            self.is_running = True
            print(f"COM-порт {self.port_name} запущен с параметрами:")
            print(f"  Baudrate: {self.baudrate}")
            print(f"  Data bits: {self.bytesize}")
            print(f"  Parity: {self.parity}")
            print(f"  Stop bits: {self.stopbits}")

            # Запускаем потоки для чтения и записи
            read_thread = threading.Thread(target=self._read_data)
            read_thread.daemon = True
            read_thread.start()

            return True

        except serial.SerialException as e:
            print(f"Ошибка: Не удалось открыть порт {self.port_name}")
            print(f"Детали: {e}")
            return False

    def _read_data(self):
        """Чтение данных из порта"""
        while self.is_running:
            if self.serial_connection and self.serial_connection.in_waiting > 0:
                try:
                    data = self.serial_connection.read(self.serial_connection.in_waiting)
                    print(f"Получены данные: {data.hex()} | ASCII: {data.decode('ascii', errors='ignore')}")
                except Exception as e:
                    print(f"Ошибка чтения: {e}")
            time.sleep(0.1)

    def send_data(self, data):
        """Отправка данных через порт"""
        if self.serial_connection and self.serial_connection.is_open:
            try:
                if isinstance(data, str):
                    data = data.encode('utf-8')
                self.serial_connection.write(data)
                print(f"Отправлены данные: {data.hex()} | ASCII: {data.decode('ascii', errors='ignore')}")
                return True
            except Exception as e:
                print(f"Ошибка отправки: {e}")
                return False
        return False

    def send_bits(self, bits):
        """Отправка битовой последовательности"""
        if self.serial_connection and self.serial_connection.is_open:
            try:
                # Преобразуем биты в байты
                byte_data = self._bits_to_bytes(bits)
                self.serial_connection.write(byte_data)
                print(f"Отправлены биты: {bits}")
                print(f"В виде байтов: {byte_data.hex()}")
                return True
            except Exception as e:
                print(f"Ошибка отправки битов: {e}")
                return False

    def _bits_to_bytes(self, bits):
        """Преобразование строки битов в байты"""
        # Удаляем пробелы и небитовые символы
        clean_bits = ''.join(filter(lambda x: x in '01', bits))

        # Дополняем до кратного 8
        while len(clean_bits) % 8 != 0:
            clean_bits += '0'

        # Преобразуем в байты
        byte_array = bytearray()
        for i in range(0, len(clean_bits), 8):
            byte_str = clean_bits[i:i + 8]
            byte_val = int(byte_str, 2)
            byte_array.append(byte_val)

        return bytes(byte_array)

    def change_settings(self, baudrate=None, bytesize=None, parity=None, stopbits=None):
        """Изменение настроек порта"""
        if baudrate: self.baudrate = baudrate
        if bytesize: self.bytesize = bytesize
        if parity: self.parity = parity
        if stopbits: self.stopbits = stopbits

        if self.serial_connection and self.serial_connection.is_open:
            self.serial_connection.close()
            return self.start()

        return True

    def stop(self):
        """Остановка порта"""
        self.is_running = False
        if self.serial_connection and self.serial_connection.is_open:
            self.serial_connection.close()
        print(f"COM-порт {self.port_name} остановлен")


def list_available_ports():
    """Список доступных COM-портов"""
    ports = serial.tools.list_ports.comports()
    print("\nДоступные COM-порты:")
    for port in ports:
        print(f"  {port.device} - {port.description}")


def main():
    # Показываем доступные порты
    list_available_ports()

    # Настройки порта
    port_settings = {
        'port_name': input("\nВведите имя COM-порта (например COM3): "),
        'baudrate': int(input("Введите скорость (9600, 115200, etc): ") or "9600"),
        'bytesize': int(input("Введите количество бит данных (7, 8): ") or "8"),
        'parity': input("Введите четность (N, E, O): ").upper() or "N",
        'stopbits': int(input("Введите стоп-биты (1, 2): ") or "1")
    }

    # Создаем и запускаем виртуальный порт
    virtual_port = VirtualCOMPort(**port_settings)

    if not virtual_port.start():
        print("Не удалось запустить COM-порт. Возможно, порт занят или не существует.")
        return

    try:
        while True:
            print("\n" + "=" * 50)
            print("Меню:")
            print("1. Отправить текст")
            print("2. Отправить биты")
            print("3. Изменить настройки")
            print("4. Показать настройки")
            print("5. Выход")

            choice = input("Выберите действие: ")

            if choice == '1':
                text = input("Введите текст для отправки: ")
                virtual_port.send_data(text)

            elif choice == '2':
                bits = input("Введите битовую последовательность (например: 01010101 11110000): ")
                virtual_port.send_bits(bits)

            elif choice == '3':
                print("Новые настройки (оставьте пустым для сохранения текущего):")
                new_baudrate = input(f"Скорость [{virtual_port.baudrate}]: ")
                new_bytesize = input(f"Биты данных [{virtual_port.bytesize}]: ")
                new_parity = input(f"Четность [{virtual_port.parity}]: ")
                new_stopbits = input(f"Стоп-биты [{virtual_port.stopbits}]: ")

                settings = {}
                if new_baudrate: settings['baudrate'] = int(new_baudrate)
                if new_bytesize: settings['bytesize'] = int(new_bytesize)
                if new_parity: settings['parity'] = new_parity.upper()
                if new_stopbits: settings['stopbits'] = int(new_stopbits)

                virtual_port.change_settings(**settings)

            elif choice == '4':
                print(f"\nТекущие настройки {virtual_port.port_name}:")
                print(f"  Baudrate: {virtual_port.baudrate}")
                print(f"  Data bits: {virtual_port.bytesize}")
                print(f"  Parity: {virtual_port.parity}")
                print(f"  Stop bits: {virtual_port.stopbits}")

            elif choice == '5':
                break

            time.sleep(1)

    except KeyboardInterrupt:
        print("\nПрограмма прервана пользователем")
    finally:
        virtual_port.stop()


if __name__ == "__main__":
    main()