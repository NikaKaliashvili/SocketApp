#include "../../include/socketApp.h"

#define BUFFER_SIZE 1024

void InitializeWSAData() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
}

void HostServer() { // hosts server
	UINT server_fd, new_socket;
	struct sockaddr_in address;
	int timeout = 100;
	socklen_t addrlen = sizeof(address);
	char buffer[BUFFER_SIZE] = { 0 };

	server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&timeout, sizeof(timeout));

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;

	char portBuffer[16];
	if (!SendDlgItemMessageA(_hwnd, CONNECT_HOST_PORT_FIELD, WM_GETTEXT, sizeof(portBuffer), (LPARAM)&portBuffer))
	{
		std::cout << "Couldn't load port" << std::endl;
		return;
	}

	address.sin_port = htons(atoi(portBuffer));

	bind(server_fd, (struct sockaddr*)&address, sizeof(address));
	listen(server_fd, 3);

	std::cout << "Server is running" << std::endl;
	hosted = true;

	// set button text to host
	UpdatePropertyText(CONNECT_HOST_BUTTON, "End Server");

	hosted = true;
	while (hosted)
	{
		int bytesReceived = recv(sock, buffer, BUFFER_SIZE, 0);

		if (bytesReceived <= 0)
		{
			break;
		}

		buffer[bytesReceived] = '\0';

		SendDlgItemMessageA(_hwnd, MESSAGE_TEXTS, EM_SETSEL, -1, 1);
		SendDlgItemMessageA(_hwnd, MESSAGE_TEXTS, EM_REPLACESEL, FALSE, (LPARAM)buffer);
		SendDlgItemMessageA(_hwnd, MESSAGE_TEXTS, EM_REPLACESEL, FALSE, (LPARAM)"\r\n");
	}

	closesocket(sock);

	WSACleanup();
}

void EndServer() {
	hosted = false;
	// set button text to host
	UpdatePropertyText(CONNECT_HOST_BUTTON, "Host");
}

void SendClientMessage() { // send client
	if (!connected) {
		std::cout << "Please connect first!" << std::endl;
		return;
	}

	if (!sock) {
		std::cout << "Socket not founed" << std::endl;
		return;
	}

	std::string message;
	message.resize(BUFFER_SIZE);
	SendDlgItemMessageA(_hwnd, MESSAGE_FIELD, WM_GETTEXT, message.size(), (LPARAM)message.data());

	if (send(sock, message.data(), message.length(), 0) < 0) {
		std::cout << "Message Couldn't sent!" << std::endl;
		return;
	}

	// add 'You: ' to the message
	std::string buffer = "You: " + message;

	AddTextToMessages(buffer.c_str());
}

void ConnectToServer() { // connects client to server
	struct sockaddr_in serv_addr;
	char buffer[BUFFER_SIZE] = { 0 };

	sock = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;

	char ipBuffer[256];
	char portBuffer[16];

	if (!SendDlgItemMessageA(_hwnd, CONNECT_HOST_IP_FIELD, WM_GETTEXT, sizeof(ipBuffer), (LPARAM)&ipBuffer))
	{
		std::cout << "Couldn't load ip" << std::endl;
		return;
	}

	if (!SendDlgItemMessageA(_hwnd, CONNECT_HOST_PORT_FIELD, WM_GETTEXT, sizeof(portBuffer), (LPARAM)&portBuffer))
	{
		std::cout << "Couldn't load port" << std::endl;
		return;
	}

	serv_addr.sin_port = htons(atoi(portBuffer));

	inet_pton(AF_INET, ipBuffer, &serv_addr.sin_addr);

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout << "Connection Failed" << std::endl;
		return;
	}

	std::cout << "Connected to server!" << std::endl;

	// set button text to connect
	UpdatePropertyText(CONNECT_HOST_BUTTON, "Disconnect");

	connected = true;
	while (connected)
	{
		int bytesReceived = recv(sock, buffer, BUFFER_SIZE, 0);

		if (bytesReceived <= 0)
		{
			break;
		}

		buffer[bytesReceived] = '\0';

		AddTextToMessages(buffer); // add new text line
	}

	closesocket(sock);

	WSACleanup();
}

void DisconnectFromServer() {
	connected = false;
	// set button text to connect
	UpdatePropertyText(CONNECT_HOST_BUTTON, "Connect");
}