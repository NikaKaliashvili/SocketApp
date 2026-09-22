#pragma once

#include "socket/socket_manager.h"

#include <Windows.h>
#include <thread>
#include <iostream>
#include <string>

#define BG_COLOR RGB(69, 132, 204)

#define CLIENT_SERVER_FRAME 5
#define CLIENT_SERVER_CLIENT 6
#define CLIENT_SERVER_SERVER 7

#define CONNECT_HOST_FRAME 10
#define CONNECT_HOST_IP_LABEL 11
#define CONNECT_HOST_IP_FIELD 12
#define CONNECT_HOST_PORT_LABEL 13
#define CONNECT_HOST_PORT_FIELD 14
#define CONNECT_HOST_BUTTON 15

#define MESSAGE_FRAME 20
#define MESSAGE_TEXTS 21
#define MESSAGE_FIELD 22
#define MESSAGE_SEND 23

inline extern HWND _hwnd = nullptr;
inline extern HBRUSH _hStaticBg = nullptr;
inline extern unsigned int sock = 0;
inline extern bool hosted = false;
inline extern bool connected = false;

#include "window/window.h"
#include "window/wndProc.h"
#include "window/wmMessages.h"