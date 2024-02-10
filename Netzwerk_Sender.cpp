#include <iostream>
#include <winsock2.h>
#include <wS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main() {
	WSADATA WD;
	if (WSAStartup(MAKEWORD(2, 2), &WD) != 0) {
		cout << "WSAStartup ist fehlgeschlagen: " << WSAGetLastError() << endl;
		return 1;
	}
	else {
		cout << "WSAStartup war erfolgreich" << endl;
	}
	SOCKET Socket1 = socket(AF_INET, SOCK_STREAM, 0);
	if (Socket1 == INVALID_SOCKET) {
		cout << "Socket1 ist fehlgeschlagen: " << WSAGetLastError() << endl; 
		WSACleanup();
		return 1;
	}
	else {
		cout << "Socket1 war erfolgreich" << endl; 
	}

	sockaddr_in ServerAdress;
	ServerAdress.sin_family = AF_INET;
	ServerAdress.sin_port = htons(4444);
	if (inet_pton(AF_INET, "127.0.0.1", &(ServerAdress.sin_addr)) <= 0) {
		cout << "fehlerhafte IP-Adresse: " << WSAGetLastError();
		closesocket(Socket1);
		WSACleanup();
	}
	else {
		cout << "fehlerfreie IP-Adresse" << endl;
	}
	if (connect(Socket1, (struct sockaddr*)&ServerAdress, sizeof(ServerAdress)) == SOCKET_ERROR) {  
		cout << "Verbindung ist fehlgeschlagen: " << WSAGetLastError() << endl;
		closesocket(Socket1);
		WSACleanup();
		return 1;
	}
	else {
		cout << "Verbind war erfolgreich" << endl;
	}
	char Buffer[1024];
	string Nachricht1 = "Hallo Server!";
	if (send(Socket1, Nachricht1.c_str(), Nachricht1.size(), 0) == SOCKET_ERROR) {
		cout << "Nachricht wurde nicht erfolgreich geschickt: " << WSAGetLastError() << endl;
	}
	else {
		cout << "Nachricht wurde erfolgreich verschickt" << endl; 
	}
	closesocket(Socket1);
	WSACleanup();
	return 0;
}
