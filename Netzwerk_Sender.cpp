#include <iostream>
#include <boost/asio.hpp>
#include <thread>
using namespace std;
using namespace boost::asio;
using namespace std::chrono;
int main() {
	try {
		string Nachricht1 = "Hallo Programm 1";
		string Nachricht2 = "Mir geht es sehr gut";
		cout << "Sender" << endl;
		io_service IO;
		ip::tcp::socket socket(IO); 
		ip::tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), 1122); 

		system("start C:\\Users\\kaiwa\\OneDrive\\Desktop\\Netzwerkschnittstelle\\Netzwerk_Empfänger\\Netzwerk_Empfänger");
		this_thread::sleep_for(milliseconds(500));
		cout << "start fertig" << endl;
		this_thread::sleep_for(milliseconds(500));
		system("start /d");
		this_thread::sleep_for(milliseconds(3500));
		cout << "/d fertig" << endl;
		this_thread::sleep_for(milliseconds(500));
		socket.connect(endpoint);

		write(socket, buffer(Nachricht1));
		write(socket, buffer(Nachricht2));

		char Data1[1024];
		size_t Data2 = socket.read_some(buffer(Data1));
		Data1[Data2];
		cout << "Empfangene Daten vom Sender: " << Data1 << endl;
	}
	catch (exception& Ausnahme) {
		cout << "Empfänger Ausnahme: " << Ausnahme.what() << endl;
	}
}
