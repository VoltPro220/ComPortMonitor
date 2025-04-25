#pragma once

#ifndef STDUCP_H
#define STDUCP_H

#include <windows.h>
#include <stdio.h>

constexpr int BUFFER_SIZE = 256;

#define BAUDRATE CBR_9600
#define STOPBITS ONESTOPBIT
#define PARITY NOPARITY

constexpr int BYTESIZE = 8;

constexpr int READINTERVALTIMEOUT = 50;
constexpr int READTOTALTIMEOUTCONSTANT = 50;
constexpr int READTOTALTIMEOUTMULTIPLIER = 10;
constexpr int WRITETOTALTIMEOUTCONSTANT = 50;
constexpr int WRITETOTALTIMEOUTMULTIPLIER = 50;


#if defined(__cplusplus)
#define BOOLEAN bool
#define EXTERN extern "C"
#else
#define BOOLEAN _Bool
#define EXTERN extern
#endif


static BOOLEAN isConnected = FALSE;

EXTERN HANDLE open_com_port(HANDLE, const char*);

EXTERN void close_com_port(HANDLE*);

EXTERN int check_com_port(int);

EXTERN const char* read_from_com_port(HANDLE);

EXTERN long is_available(HANDLE);

EXTERN BOOLEAN write_to_com_port(HANDLE, const char*);

#endif // !STDUCP_H