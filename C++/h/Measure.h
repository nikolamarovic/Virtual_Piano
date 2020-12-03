#ifndef MEASURE_H
#define MEASURE_H

#include<iostream>
using namespace std;
#include "MusicSymbol.h"
#include "Razlomak.h"
#include<vector>


class Measure {
	vector<MusicSymbol*> symbols;
	Razlomak currDuration, maxDuration;
	bool finished = false;
public:
	Measure(Razlomak r) :maxDuration(r), currDuration(0) { }
	Measure& add(const MusicSymbol& t);
	Razlomak getCurrDuration() { return currDuration; }
	Razlomak getMaxDuration() { return maxDuration; }
	Measure& finish() { finished = true; return *this; }
	int getSize() const { return symbols.size(); }
	MusicSymbol& getMusicSymbol(int i) const {return *symbols[i];}
	void clearVector();
	bool isFinished() { return finished; }
	bool isFull() { return currDuration >= maxDuration; }
	friend ostream& operator<<(ostream& os, const Measure& m) {
		for (int i = 0; i < m.symbols.size(); i++) {
			if (i != m.symbols.size() - 1) os << *m.symbols[i] << ", ";
			else os << (*m.symbols[i]);
		}
		return os;
	}
	~Measure() {
		//cout << "Brisem measure!" << endl;
		//for (auto s : symbols)	cout << *s;
	}
};



#endif