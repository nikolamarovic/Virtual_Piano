#ifndef COMPOSITION_H
#define COMPOSITION_H

#include "Part.h"
#include "Razlomak.h"
#include "Greske.h"
#include "Note.h"
#include "Chord.h"
#include "Pause.h"

#include<iostream>
#include<map>
#include<fstream>
#include<regex>
#include<iterator>
using namespace std;

struct MapStruct {
	bool sharp;
	int midi;
	int octave;
	char tone;
	MapStruct(bool sharp = false, int midi = -1, int octave = -1, char tone = '.') {
		this->sharp = sharp;
		this->midi = midi;
		this->octave = octave;
		this->tone = tone;
	}
	friend ostream& operator<<(ostream& os, MapStruct& m) {
		os << "Midi:" << m.midi << endl << (m.sharp ? "Povisena." : "Nije povisena.") << endl << "Octave:" << m.octave << endl << "Tone:" << m.tone << endl;
		return os;
	}
};

class Composition {
private:
	map<char, MapStruct> m;
	Part leftPart, rightPart;
	Razlomak duzinaTakta;
	string filename;
public:
	Composition() { }
	Composition(string s,Razlomak d) :filename(s),duzinaTakta(d) { }
	void loadMap(string);
	bool loadComposition();
	void setFilename(string s) { this->filename = s; }
	bool setDuration(Razlomak r) { 
		this->duzinaTakta.imenilac = r.imenilac; this->duzinaTakta.brojilac = r.brojilac;
		if (duzinaTakta.imenilac != 4 && duzinaTakta.imenilac != 8) { cout << "Greska! Imenilac razlomka mora da bude 4 ili 8." << endl; return false; }
		else return true;
	}
	Part& getLeftPart() { return leftPart; }
	Part& getRightPart() { return rightPart; }
	void deleteComposition();
	void fillWithPauses(Measure&, Measure&);
	void addPauseBoth(Measure&, Measure&, Pause&);
	void addPauseSingle(Measure&, Pause&, int);
	void addChord(Measure&, Chord&, int);
	void addNote(Measure&, Measure&, Note&, Pause&, int);
	void changeDuration(Razlomak n);
	void moveCompositionUp(int x);
	void moveCompositionDown(int x);
	void iterationThroughTheMeasures();
	void iterationThroughTheNotes(vector<Measure>::iterator);
	friend ostream& operator<<(ostream& os, const Composition& c) {
		if (c.rightPart.getNumOfMeasures() == 0 && c.leftPart.getNumOfMeasures() == 0) os << "Kompozicija je prazna." << endl;
		else {
			os << "Desna ruka[" << c.rightPart.getNumOfMeasures() << "]" << endl << c.rightPart << endl;
			os <<endl<< "Leva ruka[" << c.leftPart.getNumOfMeasures() << "]" << endl << c.leftPart << endl;
		}
		return os;
	}
	~Composition() { deleteComposition(); }
};

#endif