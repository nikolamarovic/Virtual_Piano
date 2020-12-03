#ifndef PAUSE_H
#define PAUSE_H
#include "MusicSymbol.h"


class Pause :public MusicSymbol {
public:
	Pause(Razlomak d, int t) :MusicSymbol(d, t) { }
	bool isDivided() { return divided; }
	void setDivided() { divided = true; }
	Pause* kopija() const & override { return new Pause(*this); }
	string opis()const override { 
		string s = ""; 
		s += (string)(getDuration().opis()) ;  
		return s; 
	}
};
#endif