#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <iterator>
using namespace std;
using namespace boost::asio;

int main()
{
	vector<string>Nomen{ "Hund", "Katze", "Haus", "Auto", "Hammer", "Programmiersprache", "Computerprogramm" };
	vector<string>Verben{ "programmieren, " "debuggen, " "lesen, " "schlagen, " "klicken, " "springen, " };
	vector<string>Abjektive{ "gro�", "klein", "gut", "schlecht", "weich", "hart" };
	vector<string>Pr�position{ "hinter", "vor", "unter", "�ber", "rechts", "links", "in", "au�erhalb" };
	vector<string>Konjunktion{ "weil", "und", "aber", "ober", "obwohl" };

	try {
		io_service IO;
		ip::tcp::socket socket(IO);
		ip::tcp::acceptor acceptor(IO, ip::tcp::endpoint(ip::tcp::v4(), 1122));

		while (true) {
			ip::tcp::socket socket(IO);
			acceptor.accept(socket);

			char Daten[1024];
			size_t Programm2 = socket.read_some(buffer(Daten));
			string DatenSender(Daten, Programm2);

			write(socket, buffer("Hallo Empf�nger"));
			write(socket, buffer("Wie geht es dir?"));

			if (DatenSender == "Nomen") {
				for (string& Noun : Nomen) {
					write(socket, buffer(Noun));
				}
			}
			else if (DatenSender == "Verben") {
				for (string& Verbs : Verben) {
					write(socket, buffer(Verbs));
				}
			}
			else if (DatenSender == "Abjektive") {
				for (string& Abjektiv : Abjektive) {
					write(socket, buffer(Abjektiv));
				}
			}
			else if (DatenSender == "Pr�position") {
				for (string& Pr�positions : Pr�position) {
					write(socket, buffer(Pr�positions));
				}
			}
			else if (DatenSender == "Konjuktionen") {
				for (string& Conjunktions : Konjunktion) {
					write(socket, buffer(Conjunktions));
				}
			}
		}
	}
	catch (exception& Ausnahme) {
		cout << "Ausnahme: " << Ausnahme.what() << endl;
	}
}