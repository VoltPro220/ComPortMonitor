#include "stducp.h"


HANDLE open_com_port(HANDLE hCom, const char* portName)
{
	// CreateFile: This Windows API function opens the COM port. 
	// If it fails, it prints an error message.
	// Open the specified COM port
	hCom = CreateFileA(portName,
					   GENERIC_READ | GENERIC_WRITE,
					   0, // No sharing
					   NULL, // Default security
					   OPEN_EXISTING,
					   0, // No attributes
					   NULL); // No template file

	// Check if the COM port was opened successfully
	if (hCom == INVALID_HANDLE_VALUE)
	{
		return INVALID_HANDLE_VALUE;
	}
	// DCB Structure: A DCB (Device Control Block) structure is used to define the parameters 
	// of the COM port. The baud rate, byte size, stop bits, and parity are set.
	// Setup the COM port parameters
	DCB dcb;
	if (!GetCommState(hCom, &dcb))
	{
		CloseHandle(hCom);
		return INVALID_HANDLE_VALUE;
	}

	// Set parameters (baud rate, byte size, stop bits, parity)
	dcb.BaudRate = BAUDRATE; // Baud rate
	dcb.StopBits = STOPBITS; // One stop bit
	dcb.Parity = PARITY; // No parity
	dcb.ByteSize = BYTESIZE; // 8 data bits

	// SetCommState: This function applies the settings to the COM port.
	// Set the COM port settings
	if (!SetCommState(hCom, &dcb))
	{
		CloseHandle(hCom);
		return INVALID_HANDLE_VALUE;
	}
	// COMMTIMEOUTS: This structure sets timeouts for read and write operations.
	// Optionally, set timeouts
	COMMTIMEOUTS timeouts;
	timeouts.ReadIntervalTimeout = READINTERVALTIMEOUT;
	timeouts.ReadTotalTimeoutConstant = READTOTALTIMEOUTCONSTANT;
	timeouts.ReadTotalTimeoutMultiplier = READTOTALTIMEOUTMULTIPLIER;
	timeouts.WriteTotalTimeoutConstant = WRITETOTALTIMEOUTCONSTANT;
	timeouts.WriteTotalTimeoutMultiplier = WRITETOTALTIMEOUTMULTIPLIER;

	if (!SetCommTimeouts(hCom, &timeouts))
	{
		// CloseHandle: Once done with the COM port, it’s important to close the handle to release the resource.
		CloseHandle(hCom);
		return INVALID_HANDLE_VALUE;
	}
	isConnected = TRUE;
	// Return the handle to the opened COM port
	return hCom;
}

void close_com_port(HANDLE* hCom)
{
	if (isConnected)
		CloseHandle(hCom);
}

int check_com_port(int n)
{
	if (n >= 257 || n < 1)
		return -1;
	char buf[8];
	sprintf_s(buf, sizeof(buf), "COM%d", n);
	HANDLE h = CreateFileA(buf,
						   GENERIC_READ | GENERIC_WRITE,
						   0, // No sharing
						   NULL, // Default security
						   OPEN_EXISTING,
						   0, // No attributes
						   NULL); // No template file;
	if (h != INVALID_HANDLE_VALUE)
	{
		CloseHandle(h);
		return n;
	}
	return -1;
}

const char* read_from_com_port(HANDLE hCom)
{
	if (!isConnected)
	{
		return NULL;
	}
	char* buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
	int bytesRead = 0;
	if (!ReadFile(hCom, buffer, BUFFER_SIZE - 1, (LPDWORD)&bytesRead, NULL))
	{
		free(buffer);
		return NULL;
	}
	return buffer;
}

long is_available(HANDLE hCom)
{
	if (!isConnected)
	{
		return -1;
	}
	DWORD errors;
	COMSTAT cs;
	unsigned long res = 0;
	if (ClearCommError(hCom, &errors, &cs))
	{
		if (cs.cbInQue > 0)
		{
			res = cs.cbInQue;
		}
	}
	else
	{
		return -1;
	}
	return res;
}

BOOLEAN write_to_com_port(HANDLE hCom, const char* data)
{
	if (!isConnected)
	{
		return FALSE;
	}
	DWORD bytesWritten;
	if (!WriteFile(hCom, data, strlen(data), &bytesWritten, NULL))
	{
		return FALSE;
	}
	return TRUE;
}
