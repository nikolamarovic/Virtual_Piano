#ifndef PART_H
#define PART_H

#include<iostream>
#include<vector>
#include "Measure.h"
#include<iostream>

#include<algorithm>
using namespace std;

class Part {
	vector<Measure> measures;
public:
	Part& add(const Measure& m) { measures.push_back(m); return *this; }
	int getNumOfMeasures() const { return measures.size(); }
	Measure& getMeasure(int i) { return measures[i]; }
	Razlomak getMaxDurration() { return measures[0].getMaxDuration(); }
	auto begin()  { return measures.begin(); }
	auto end()  { return measures.end(); }
	void clear() {
		for (int i = 0; i < measures.size(); i++) { measures[i].clearVector(); }
		measures.clear();
	}
	friend ostream& operator<<(ostream& os, const Part& p) {
		for (int i = 0; i < p.measures.size(); i++)
			os << p.measures[i] << (" | ")<<endl;
		return os;
	}
	~Part() {
		//cout << "Unistava se PART!" << endl;
	}
};

#endif