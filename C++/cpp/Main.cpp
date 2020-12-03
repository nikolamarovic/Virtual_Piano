#include<iostream>
using namespace std;

#include "Composition.h"
#include "Greske.h"
#include "Formatter.h"
#include "MIDIFormatter.h"
#include "MusicXMLFormatter.h"
#include "BMPFormatter.h"

void printMainEx1() {
	cout << "***MENI***" << endl;
	cout << "0. Prekid programa." << endl;
	cout << "1. Kreiranje kompozicije." << endl;
	cout << "2. Manipulacija nad kompozicijom." << endl;
	cout << "3. Eksportovanje kompozicije." << endl;
	cout << "4. Ispis kompozicije." << endl;
	cout << endl;
}
void printMainEx2() {
	cout << "***Iteriranje kroz kompoziciju***" << endl;
	cout << "1. Prelazak na sledeci takt." << endl;
	cout << "2. Povratak na prethodni takt." << endl;
	cout << "3. Zapocinjanje iteriranja kroz note. " << endl;
	cout << "4. Izmena duzine takta kompozicije." << endl;
}
void  printMainEx23() {
	cout << "***Zapocinjanje iteriranja kroz note takta***" << endl;
	cout << "1. Prelazak na sledecu notu." << endl;
	cout << "2. Povratak na prethodnu notu." << endl;
	cout << "3. Menjanje oktave note." << endl;
	cout << "4. Dodavanje/uklanjanje povisilice" << endl;
}
void printMainEx3() {
	cout << "***Eksportovanje kompozicije***" << endl;
	cout << "1. Kreiranje MIDI formata." << endl;
	cout << "2. Kreiranje MusicXML formata." << endl;
	cout << "3. Kreiranje BMP formata." << endl;
}

int main() {
	Composition *c = new Composition();
	int choice; bool created = false;
	printMainEx1();
	cout << "Unesite zeljenu opciju:" << endl;
	cin >> choice;
	try {
		while (choice) {
			//PRAVLJENJE KOMPOZICIJE
			if (choice == 1) {
				cout << "***Kreiranje kompozicije***" << endl;
				cout << "Unesite duzinu trajanja takta kompozicije u formatu (brojilac imenilac): " << endl;
				int imen, brojil;
				cin >> brojil >> imen;
				Razlomak r = Razlomak(brojil, imen);
				cout << "Unesite naziv fajla u kojem se nalazi kompozicija (dodati ekstenziju .txt): " << endl;
				string filename;
				cin >> filename;
				c->setFilename(filename);
				c->setDuration(r);
				c->loadMap("map.csv");
				bool ok = c->loadComposition();
				if (ok) { cout << "Kompozicija uspesno ucitana. " << endl; created = true; }
				else cout << "Greska pri ucitavanju kompozicije." << endl;
			}
			//ITERIRANJE
			if (choice == 2) {
				if (!created) { cout << "Kompozicija nije kreirana." << endl; break; }
				cout << "Izgled taktova u levom i desnom delu po rednim brojevima." << endl;
				c->iterationThroughTheMeasures();
				printMainEx2();

				cout << "Unesite zeljenu opciju:" << endl;
				int choicePrint;
				cin >> choicePrint;
				if (choicePrint == 1) {
					cout << "Izaberite kojem delu zelite da pristupite." << endl;
					cout << "1.Levi" << endl;
					cout << "2.Desni" << endl;
					int choicePart; cin >> choicePart;
					Part part;
					if (choicePart == 2) part = c->getRightPart();
					else part = c->getLeftPart();

					cout << "Izaberite redni broj takta koji zelite da dohvatite (indeks ne treba da prelazi broj taktova u izabranom delu - " << part.getNumOfMeasures() << ")" << endl;
					int indOfMeasure;
					cin >> indOfMeasure;
					Measure measure = part.getMeasure(indOfMeasure - 1);
					cout << "Trenutni takt: " << endl;
					cout << measure << endl;
					measure = part.getMeasure(indOfMeasure);
					cout << "Sledeci takt: " << endl;
					cout << measure << endl;
				}
				if (choicePrint == 2) {
					cout << "Izaberite kojem delu zelite da pristupite." << endl;
					cout << "1.Levi" << endl;
					cout << "2.Desni" << endl;
					int choicePart; cin >> choicePart;
					Part part;
					if (choicePart == 2) part = c->getRightPart();
					else part = c->getLeftPart();

					cout << "Izaberite redni broj takta koji zelite da dohvatite (indeks ne treba da prelazi broj taktova u izabranom delu - " << part.getNumOfMeasures() << ")" << endl;
					int indOfMeasure;
					cin >> indOfMeasure;
					Measure measure = part.getMeasure(indOfMeasure - 1);
					cout << "Trenutni takt: " << endl;
					cout << measure << endl;
					measure = part.getMeasure(indOfMeasure - 2);
					cout << "Prethodni: " << endl;
					cout << measure << endl;
				}
				if (choicePrint == 3) {
					cout << "Izaberite kojem delu zelite da pristupite." << endl;
					cout << "1.Levi" << endl;
					cout << "2.Desni" << endl;
					int choicePart; cin >> choicePart;
					Part part;
					if (choicePart == 2) part = c->getRightPart();
					else part = c->getLeftPart();

					cout << "Izaberite redni broj takta koji zelite da dohvatite (indeks ne treba da prelazi broj taktova u izabranom delu - " << part.getNumOfMeasures() << ")" << endl;
					int index;
					cin >> index;
					Measure measure = part.getMeasure(index - 1);
					cout << "Trenutni takt: " << endl;
					cout << measure << endl;
					cout << "Izaberite redni broj simbola kojem zelite da pristupite(uneti broj ne treba da prelazi broj simbola u taktu-" << measure.getSize() << ")" << endl;
					cin >> index;
					MusicSymbol& note = measure.getMusicSymbol(index - 1);
					if (note.getType() == 2) cout << "Akord: ";
					if (note.getType() == 1) cout << "Nota: ";
					if (note.getType() == 0) cout << "Pauza: ";
					cout << note << endl;
					//nota u akordu
					if (note.getType() == 2) {
						cout << "S obzirom da je izabrana nota akord, izaberite redni broj simbola kojem zelite da pristupite(uneti broj ne treba da prelazi broj simbola u akordu-" << note.getNumOfNotes() << ")" << endl;
						int indInChord; cin >> indInChord;
						MusicSymbol& noteInChord = note.getNote(indInChord);
						printMainEx23();
						cout << "Izaberite zeljenu opciju:" << endl;
						cin >> choicePart;
						if (choicePart == 1) {
							if ((index) < note.getNumOfNotes() && (index) >= 0)cout << "Sledeca nota je: " << note.getNote(index);
							else cout << "Nevalidan indeks." << endl;
						}
						if (choicePart = 2) {
							if ((index - 2) < note.getNumOfNotes() && (index - 2) >= 0) cout << "Prethodni simbol je: " << note.getNote(index - 2);
							else cout << "Nevalidan indeks." << endl;
						}
						if (choicePart == 3) {
							cout << "1. Povecati oktavu." << endl;
							cout << "2. Smanjivanje oktave." << endl;
							int izbor; cin >> izbor;
							cout << "Za koliko?" << endl;
							int za; cin >> za;
							if (izbor == 1) {
								for (int i = 0; i < note.getNumOfNotes(); i++) note.getNote(i).changeOctaveUp(za);
							}
							else {
								for (int i = 0; i < note.getNumOfNotes(); i++) 	note.getNote(i).changeOctaveDown(za);
							}
						}
						if (choicePart == 4) {
							cout << "1. Dodati povisilicu." << endl;
							cout << "2. Ukloniti povisilicu." << endl;
							int choicePart1; cin >> choicePart1;
							if (choicePart1 == 1) {
								if (noteInChord.getSharp()) cout << "Nota je vec povisena." << endl;
								else { noteInChord.removeSharp(); cout << "Nota je uspesno povisena." << endl; }
								cout << "Opis note posle promene:" << note;
							}
							if (choicePart1 == 2) {
								if (!noteInChord.getSharp()) cout << "Nota je vec snizena." << endl;
								else { noteInChord.setSharp(); cout << "Nota je uspesno snizena." << endl; }
								cout << "Opis note posle promene:" << note;
							}
						}
					}
					else {
						//nota obicno
						printMainEx23();
						int ch;
						cout << "Izaberite zeljenu opciju:" << endl;
						cin >> ch;
						if (ch == 1) {
							if ((index) < measure.getSize() && (index) >= 0)cout << "Sledeca nota je: " << measure.getMusicSymbol(index);
							else cout << "Nevalidan indeks." << endl;
						}
						if (ch == 2) {
							if ((index - 2) < measure.getSize() && (index - 2) >= 0) cout << "Prethodni simbol je: " << measure.getMusicSymbol(index - 2);
							else cout << "Nevalidan indeks." << endl;
						}
						if (ch == 3) {
							cout << "1. Povecati oktavu." << endl;
							cout << "2. Smanjivanje oktave." << endl;
							int izbor; cin >> izbor;
							cout << "Za koliko?" << endl;
							int za; cin >> za;
							if (izbor == 1) note.changeOctaveUp(za);
							else note.changeOctaveDown(za);
						}
						if (ch == 4) {
							cout << "1. Dodati povisilicu." << endl;
							cout << "2. Ukloniti povisilicu." << endl;
							int choicePart1; cin >> choicePart1;
							if (choicePart1 == 1) {
								if (note.getSharp()) cout << "Nota je vec povisena." << endl;
								else { note.setSharp(); cout << "Nota je uspesno povisena." << endl; }
								cout << "Opis note posle promene:" << note;
							}
							if (choicePart1 == 2) {
								if (!note.getSharp()) cout << "Nota je vec snizena." << endl;
								else { note.removeSharp(); cout << "Nota je uspesno snizena." << endl; }
								cout << "Opis note posle promene:" << note;
							}
						}
					}
				}
				if (choicePrint == 4) {
					cout << "Unesite novu duzinu takta (brojilac imenilac)" << endl;
					Razlomak r; cin >> r.brojilac >> r.imenilac;
					c->changeDuration(r);
					c->iterationThroughTheMeasures();
				}
			}

			//FORMATIRANJE
			if (choice == 3) {
				if (!created) { cout << "Kompozicija nije kreirana." << endl; break; }
				printMainEx3();
				int choicePart3;
				cout << "Unesite zeljenu opciju:" << endl;
				cin >> choicePart3;
				if (choicePart3 == 1) {
					cout << "Unesite ime fajla koji pravite (sa ekstenzijom .mid)" << endl;
					string s;
					cin >> s;
					MidiFormatter midi(s);
					midi.createFormat(*c);
					cout << "Pustite kompoziciju." << endl;
				}
				if (choicePart3 == 2) {
					cout << "Unesite ime fajla koji pravite (sa ekstenzijom .musicxml)" << endl;
					string s;
					cin >> s;
					MusicXMLFormatter xml(s);
					xml.createFormat(*c);
					cout << "Pustite kompoziciju." << endl;
				}
				if (choicePart3 == 3) {
					cout << "Unesite ime fajla koji pravite (sa ekstenzijom .bmp)" << endl;
					string s;
					cin >> s;
					BMPFormatter bmp(s);
					cout << "Unesite sirinu u broju piksela:" << endl;
					int x;
					cin >> x;
					bmp.setWidth(x);
					bmp.createMap();
					bmp.createFormat(*c);
					cout << "Otvorite sliku uz pomoc Microsoft Visual Studio-a." << endl;
				}
			}
			//ISPIS
			if (choice == 4) cout << *c;

			cout << endl;
			printMainEx1();
			cout << "Unesite zeljenu opciju:" << endl;
			cin >> choice;
		}
	}
	catch (exception &e) { cout << e.what(); }
	return 0;
}
