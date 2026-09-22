#pragma once
#include "../socketApp.h"

#ifdef _WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#pragma comment(lib, "ws2_32.lib")
#endif

void InitializeWSAData();

void ConnectToServer();
void SendClientMessage();
void DisconnectFromServer();
void HostServer();
void EndServer();