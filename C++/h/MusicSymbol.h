#ifndef MUSIC_SYMBOL_H
#define MUSIC_SYMBOL_H

#include<string>
#include<iomanip>
#include<iostream>
using namespace std;
#include<vector>
#include "Razlomak.h"

class Razlomak;

class MusicSymbol {
protected:
	vector<MusicSymbol*> notesInChord;
	Razlomak duration;
	int type;//0 - pauza, 1 - nota, 2 - akord
	bool sharp = false;
	int midi = -1;
	int octave = -1;
	char tone = '.';
	bool divided = false;
	bool changed = false;
public:
	MusicSymbol(Razlomak tr, int t) :duration(tr), type(t) { }
	MusicSymbol(bool s, int m, int o, char t, Razlomak d, int ty) : duration(d), type(ty), sharp(s), midi(m), octave(o), tone(t) { }
	MusicSymbol(const MusicSymbol& c, Razlomak d, int t) :duration(d), type(t) {
		for (int i = 0; i < c.getNumOfNotes(); i++)
			notesInChord.push_back(c.notesInChord[i]);
	}
	Razlomak getDuration() const { return duration; }
	friend Razlomak operator+(const MusicSymbol & m1, const MusicSymbol & m2) { return m1.duration + m2.duration; }
	operator Razlomak() const { return duration; }
	int getType() const { return type; }
	bool isDivided() { return divided; }
	void setDivided() { divided = true; }
	bool getSharp() { return sharp; }
	void setSharp() { 
		if (tone == 'E') {
			tone = 'F'; 
			sharp = false;
			return;
		}
		if (tone == 'B') {
			tone = 'C';
			sharp = false;
			return;
		}
		sharp = true; 
	}
	int getMidi() { return midi; }
	int getOctave() { return octave; }
	char getTone() { return tone; }
	void changeTone(char c) { this->tone = c; }
	void changeOctaveUp(int o) {
		if (this->octave <= 3 && this->octave + o > 3)  changed = true;
		if (this->octave + o > 6)this->octave = 6;
		else this->octave += o;
	}
	void changeOctaveDown(int o) { 
		if (this->octave > 3 && this->octave - o <= 3)  changed = true; 
		if (this->octave - o < 2)this->octave = 2;
		else this->octave -= o;
	}
	void addSharp() { if (!sharp) sharp = true; }
	void removeSharp() { if (sharp) sharp = false; }
	void changeDuration(Razlomak n) { this->duration = n; }
	int getNumOfNotes() const { return notesInChord.size(); }
	MusicSymbol& getNote(int i) { return *notesInChord[i]; }
	virtual string opis() const = 0;
	virtual MusicSymbol* kopija() const & = 0;
	friend ostream& operator<<(ostream & os, const MusicSymbol & m) { return os << m.opis(); }
	virtual ~MusicSymbol() { }
};


#endif