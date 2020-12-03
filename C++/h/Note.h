#ifndef NOTE_H
#define NOTE_H

#include "MusicSymbol.h"
#include<string>

class Note :public MusicSymbol {

public:
	Note(bool s, int m, int o, char t, Razlomak d, int ty) : MusicSymbol(s, m, o, t, d, ty) { }

	Note* kopija()const & override { return new Note(*this); }
	string opis() const override {
		string s = "";
		if (getDuration().isEqual(Razlomak(1 / 4))) {
			if ((int)tone > 97) s += tone - 32;
			else s += tone;
		}
		else {
			if ((int)tone < 97) s += tone + 32;
			else s += tone;
		}
		 if (sharp) s += '#'; s += (octave + '0');
		return s;
	}
};

#endif