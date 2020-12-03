#ifndef CHORD_H
#define CHORD_H

#include "MusicSymbol.h"
#include "Razlomak.h"
#include "Note.h"

using namespace std;


class Chord :public MusicSymbol {
public:
	Chord(Razlomak d, int t) :MusicSymbol(d, t) { }
	Chord(const Chord& c, Razlomak d, int t) :MusicSymbol(c, d, t) { }
	Chord& add(const Note& n) {
		notesInChord.push_back(n.kopija());
		return *this;
	}
	void setDivided() { divided = true; for (int i = 0; i < getNumOfNotes(); i++) notesInChord[i]->setDivided(); }
	string opis() const override {
		string s = "[";
		for (int i = 0; i < notesInChord.size(); i++) { s += notesInChord[i]->opis(); if (i != getNumOfNotes() - 1) s += ", "; }
		s += "]";
		return s;
	}
	Chord* kopija() const & override { return new Chord(*this); }
};

#endif