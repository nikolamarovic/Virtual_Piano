#ifndef FORMATTER
#define FORMATTER

#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<regex>
#include<vector>
#include<utility>
#include "MidiFile.h"
#include "Composition.h"
using namespace std;
using namespace smf;


class Formatter {
public:
	Formatter() { }
	virtual void createFormat(Composition& c) = 0;
};
#endif