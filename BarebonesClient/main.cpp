#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void main() {
	string ipaddress;
	int port;
	cout << "Ip-address: ";
	getline(cin, ipaddress);
	cout << "Port: ";
	cin >> port;
	//string ipAdress = "192.168.43.198";  // IP Adress сервера
	//int port = 5223;				//Порт сервера

	//Инциализируем винсокет
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);

	if (wsResult != 0) {
		cerr << "Can't startup winsock" << endl;
		system("pause");
		return;
	}

	//Создаем сокет
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cerr << "Can't create socket" << endl;
		WSACleanup();
		system("pause");
		return;
	}

	//Заполняем хинт-структуру
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipaddress.c_str(), &hint.sin_addr);

	//Connect to server
	int conResult = connect(sock, (sockaddr*)&hint, sizeof(hint));

	if (conResult == SOCKET_ERROR) {
		cerr << "Can't connect to server" << endl;
		closesocket(sock);
		WSACleanup();
		system("pause");
		return;
	}

	//Отправляем и получаем инфу

	char buff[4096];
	string userInput;
	int random = (rand() % 10 + 2) * 1000;

	//Ждем ввода информации
	cout << ">";
	//getline(cin, userInput);
	cin >> userInput;
	Sleep(random);
	if (userInput.size() > 0) {				//Если что-то введено

			//Отправляем текст

		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
		if (sendResult != SOCKET_ERROR) {

				//Ждем ответа
			ZeroMemory(buff, 4096);

			int bytesReceived = recv(sock, buff, 4096, 0);
			if (bytesReceived > 0) {

				cout << "SERVER>" << string(buff, 0, bytesReceived) << endl;
			}
		}
	}

	random = (rand() % 10 + 2) * 1000;
	Sleep(random);

	closesocket(sock);
	WSACleanup();
}