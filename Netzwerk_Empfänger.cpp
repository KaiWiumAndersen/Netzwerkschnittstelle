#include <iostream>
#include <ws2tcpip.h>
#include <thread>
#include <winsock2.h>
#include <chrono>
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#pragma comment(lib, "ws2_32.lib")
using namespace std;
using namespace std::chrono;

int main() {
	WSADATA WD;
	if (WSAStartup(MAKEWORD(2, 2), &WD) != 0) {
		cout << "WSAStartup ist fehlgeschlagen: " << WSAGetLastError() << endl;
		return 1;
	}
	SOCKET Socket1 = socket(AF_INET, SOCK_STREAM, 0);

	if (Socket1 == INVALID_SOCKET) {
		cout << "Schlechter Socket: " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	else {
		cout << "Guter Socket" << endl;
	}

	sockaddr_in ServerAdress;
	ServerAdress.sin_family = AF_INET;
	ServerAdress.sin_port = htons(4444);
	if (inet_pton(AF_INET, "127.0.0.1", &(ServerAdress.sin_addr)) <= 0) {
		cout << "fehlerhafte IP-Adresse: " << WSAGetLastError() << endl;
	}
	else {
		cout << "erfolgreiche IP-Adresse" << endl;
	}
	if (bind(Socket1, (struct sockaddr*)&ServerAdress, sizeof(ServerAdress)) == SOCKET_ERROR) {
		cout << "Fehler beim Binden: " << WSAGetLastError() << endl;
		closesocket(Socket1);
		WSACleanup();
	}
	else {
		cout << "Das Binden war erfolgreich" << endl;
	}
	if (listen(Socket1, SOMAXCONN) == SOCKET_ERROR) {
		cout << "Fehler beim Abhören: " << WSAGetLastError() << endl;
		closesocket(Socket1);
		WSACleanup();
		return 1;
	}
	else {
		cout << "Abhören war erfolgreich" << endl;
	}
	this_thread::sleep_for(milliseconds(4000));
	char Buffer[4096];
	memset(Buffer, 0, sizeof(Buffer));
	int BytesRead = recv(Socket1, Buffer, sizeof(Buffer), 0);
	if (BytesRead == SOCKET_ERROR) {
		cout << "Fehler beim Empfangen der Daten: " << WSAGetLastError() << endl;
	}
	else if (BytesRead == 0) {
		cout << "Verbindung geschlossen: " << WSAGetLastError() << endl;
	}
	else {
		cout << Buffer << endl;
	}
	closesocket(Socket1);
	WSACleanup();
}
