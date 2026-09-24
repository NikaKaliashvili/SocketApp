#include "../../../include/socketApp.h"

LRESULT WMCOMMAND(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == BN_CLICKED) {

		switch (LOWORD(wParam)) {

		case MESSAGE_SEND: {
			if (connected) {
				SendClientMessage(0);
			}
			else if (hosted) {
				SendServerMessage(0);
			}
			else {
				UpdatePropertyText(MESSAGE_FIELD, "Please connect first!");
			}
			break;
		}

		case MESSAGE_FILE_SEND: {
			if (connected)
				SendClientMessage(1);

			if (hosted)
				SendServerMessage(1);
				break;
		}

		case CONNECT_HOST_BUTTON: // if connect or host is clicked

			if (SendDlgItemMessageA(hwnd, CLIENT_SERVER_CLIENT, BM_GETCHECK, 0, 0)) { // if client is selected
				if (!connected) {
					std::thread(ConnectToServer).detach();
				}
				else {
					DisconnectFromServer();
				}
			}

			if (SendDlgItemMessageA(hwnd, CLIENT_SERVER_SERVER, BM_GETCHECK, 0, 0)) // if server is selected
			{
				if (!hosted) {
					std::thread(HostServer).detach();
				}
				else {
					EndServer();
				}
			}

			break;


		case CLIENT_SERVER_CLIENT: {// if client was selected
			if (hosted || connected)
				break;

			EnableWindow(GetDlgItem(hwnd, CONNECT_HOST_IP_LABEL), TRUE); // enable ip label
			SendDlgItemMessageA(hwnd, CONNECT_HOST_IP_FIELD, EM_SETREADONLY, FALSE, 0); // enable typing on ip field

			// set button text to connect
			UpdatePropertyText(CONNECT_HOST_BUTTON, "Connect"); // set button text to host


			break;
		}

		case CLIENT_SERVER_SERVER: { // if server was selected
			if (hosted || connected)
				break;

			EnableWindow(GetDlgItem(hwnd, CONNECT_HOST_IP_LABEL), FALSE); // disable ip label
			SendDlgItemMessageA(hwnd, CONNECT_HOST_IP_FIELD, EM_SETREADONLY, TRUE, 0); // disable typing on ip field

			UpdatePropertyText(CONNECT_HOST_BUTTON, "Host"); // set button text to host
			break;

		}

		}

	}

	return 0;

}
