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
	vector<string>Abjektive{ "groß", "klein", "gut", "schlecht", "weich", "hart" };
	vector<string>Präposition{ "hinter", "vor", "unter", "über", "rechts", "links", "in", "außerhalb" };
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

			write(socket, buffer("Hallo Empfänger"));
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
			else if (DatenSender == "Präposition") {
				for (string& Präpositions : Präposition) {
					write(socket, buffer(Präpositions));
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