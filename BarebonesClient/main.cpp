#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void main() {
	string ipAdress = "127.0.0.1";  // IP Adress сервера
	int port = 5223;				//Порт сервера
	//string str = "Darling, you look perfect";

	//Инциализируем винсокет
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);

	if (wsResult != 0) {
		cerr << "Can't startup winsock" << endl;
		return;
	}

	//Создаем сокет
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cerr << "Can't create socket" << endl;
		WSACleanup();
		return;
	}

	//Заполняем хинт-структуру
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAdress.c_str(), &hint.sin_addr);

	//Connect to server
	int conResult = connect(sock, (sockaddr*)&hint, sizeof(hint));

	if (conResult == SOCKET_ERROR) {
		cerr << "Can't connect to server" << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	int random = (rand() % 10 + 2)*1000;
	Sleep(random);
	//Отправляем и получаем инфу

	char buff[4096];
	string userInput;

	do {
		//Ждем ввода инфы
		cout << ">";
		getline(cin, userInput);

		if (userInput.size() > 0) {				//Если что-то введено

			//Отправляем текст

			//int sendResult = send(sock, str.c_str(), str.size() + 1, 0);
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {

				/*//Ждем ответа
				ZeroMemory(buff, 4096);

				int bytesReceived = recv(sock, buff, 4096, 0);
				if (bytesReceived > 0) {
					//Выводим строку
					cout << "SERVER>" << string(buff, 0, bytesReceived) << endl;
				}*/
			}
		}

	} while (userInput.size() != 0);

		//random = (rand() % 10 + 2) * 1000;
		//Sleep(random);
	// Close down everything
	closesocket(sock);
	WSACleanup();
}