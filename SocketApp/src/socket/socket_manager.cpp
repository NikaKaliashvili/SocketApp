#include "../../include/socketApp.h"

#define BUFFER_SIZE 1024

static std::vector<SOCKET> clients;
static fd_set fdset;

void InitializeWSAData() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
}

static void SendServerMessage_Text(std::string& buffer) {
    for (SOCKET client : clients) {
        send(client, buffer.c_str(), buffer.length(), 0);
    }
}

void HostServer()
{
    InitializeWSAData();

    SOCKET server_fd;
    sockaddr_in address{};

    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (server_fd == INVALID_SOCKET)
    {
        std::cout << "Failed to create socket\n";
        return;
    }

    int opt = 1;

    setsockopt(
        server_fd,
        SOL_SOCKET,
        SO_REUSEADDR,
        (char*)&opt,
        sizeof(opt)
    );

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;

    char portBuffer[16]{};

    SendDlgItemMessageA(
        _hwnd,
        CONNECT_HOST_PORT_FIELD,
        WM_GETTEXT,
        sizeof(portBuffer),
        (LPARAM)portBuffer
    );

    address.sin_port = htons(atoi(portBuffer));

    if (bind(
        server_fd,
        (sockaddr*)&address,
        sizeof(address)
    ) == SOCKET_ERROR)
    {
        std::cout << "Couldn't bind!\n";
        closesocket(server_fd);
        return;
    }

    if (listen(server_fd, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cout << "Couldn't listen!\n";
        closesocket(server_fd);
        return;
    }

    std::cout << "Server is running\n";

    hosted = true;

    UpdatePropertyText(CONNECT_HOST_BUTTON,"End Server");

    clients.clear();

    std::string buffer;
    buffer.resize(BUFFER_SIZE);

    while (hosted)
    {
        FD_ZERO(&fdset);

        // Monitor server socket
        FD_SET(server_fd, &fdset);

        // Monitor all clients
        for (SOCKET client : clients)
        {
            FD_SET(client, &fdset);
        }

        // Wait until something happens
        int activity = select(
            0,
            &fdset,
            nullptr,
            nullptr,
            nullptr
        );

        if (activity == SOCKET_ERROR)
        {
            std::cout << "select() error\n";
            break;
        }

        // new connection

        if (FD_ISSET(server_fd, &fdset))
        {
            SOCKET newClient = accept(
                server_fd,
                nullptr,
                nullptr
            );

            if (newClient != INVALID_SOCKET)
            {
                clients.push_back(newClient);

                std::cout
                    << "Client connected: "
                    << newClient
                    << '\n';
            }
        }

        // client messages

        for (auto it = clients.begin(); it != clients.end();)
        {
            SOCKET client = *it;

            if (FD_ISSET(client, &fdset))
            {
                char* tempBuffer = new char[BUFFER_SIZE];
                
                int bytesReceived = recv(client, tempBuffer, BUFFER_SIZE, 0);

                // Client sent data
                if (bytesReceived > 0)
                {
                    tempBuffer[bytesReceived] = '\0';

                    buffer.resize(bytesReceived);

                    buffer = tempBuffer;

                    delete[] tempBuffer;

                    std::cout
                        << "Client "
                        << client
                        << ": "
                        << buffer
                        << '\n';

                    AddTextToMessages(buffer);

                    SendServerMessage_Text(buffer);

                    ++it;
                }

                // Client disconnected
                else if (bytesReceived == 0)
                {
                    std::cout
                        << "Client disconnected: "
                        << client
                        << '\n';

                    closesocket(client);

                    it = clients.erase(it);
                }

                // Error
                else
                {
                    std::cout
                        << "recv() error on client: "
                        << client
                        << '\n';

                    closesocket(client);

                    it = clients.erase(it);
                }
            }
            else
            {
                ++it;
            }
        }
    }

    for (SOCKET client : clients)
    {
        closesocket(client);
    }

    clients.clear();

    closesocket(server_fd);

    WSACleanup();

    std::cout << "Server stopped\n";
}

void EndServer() {
	hosted = false;
	// set button text to host
	UpdatePropertyText(CONNECT_HOST_BUTTON, "Host");
}

static bool GetFileData(std::string& buffer) {
    char szFile[260] = { 0 };

    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL; // Set to your window handle if applicable
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);

    if (GetOpenFileNameA(&ofn)) {
        // if read correctly
        FILE* hFile = fopen(szFile, "rb");
        if (hFile) {
            int realSize = fread(buffer.data(), 1, BUFFER_SIZE, hFile);
            if (!ferror(hFile)) {
                buffer.resize(realSize);
                fclose(hFile); // close file
                return 1;
            }
        }
    }
}


void SendClientMessage(int mode) { // send message from client
    if (!sock) {
        std::cout << "Socket not found" << std::endl;
        return;
    }

    if (mode == 0) {
        std::string message;
        message.resize(BUFFER_SIZE);
        int realSize = SendDlgItemMessageA(_hwnd, MESSAGE_FIELD, WM_GETTEXT, message.size(), (LPARAM)message.data());
        message.resize(realSize);

        // add 'You: ' to the message
        std::string buffer = "You: ";

        AddTextToMessages(buffer.c_str(), false);

        if (send(sock, message.data(), message.length(), 0) < 0) {
            std::cout << "Message Couldn't sent!" << std::endl;
            return;
        }

    }
    else if (mode == 1) {
        std::string buffer;
        buffer.resize(BUFFER_SIZE);
        if (GetFileData(buffer)) {
            if (send(sock, buffer.data(), buffer.length(), 0) < 0) {
                std::cout << "Message Couldn't sent!" << std::endl;
                return;
            }
            else {
                std::string message = "File sent!";

                AddTextToMessages(message.c_str());
            }
        }
        else {
            std::cout << "Couldn't receive file content!\n";
        }
    }


}



void SendServerMessage(int mode) // send message from server
{
    if (mode == 0) { // send message
        std::string buffer;
        buffer.resize(BUFFER_SIZE);
        int realSize = SendDlgItemMessageA(_hwnd, MESSAGE_FIELD, WM_GETTEXT, BUFFER_SIZE, (LPARAM)buffer.data());
        buffer.resize(realSize);
        SendServerMessage_Text(buffer);
        std::string message = "You: " + buffer;
        AddTextToMessages(message.c_str());
    }
    else if (mode == 1) { // send file
        std::string buffer;
        buffer.resize(BUFFER_SIZE);
        if (GetFileData(buffer)) {
            SendServerMessage_Text(buffer);
            AddTextToMessages("File sent!");
        }
        else {
            std::cout << "Couldn't receive file content!\n";
        }
    }
}

void ConnectToServer() { // connects client to server
	InitializeWSAData();
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

		if (bytesReceived > 0)
		{
			buffer[bytesReceived] = '\0';

			AddTextToMessages(buffer);
		}

	}

	closesocket(sock);

	WSACleanup();
}

void DisconnectFromServer() {
	connected = false;
	// set button text to connect
	UpdatePropertyText(CONNECT_HOST_BUTTON, "Connect");
}