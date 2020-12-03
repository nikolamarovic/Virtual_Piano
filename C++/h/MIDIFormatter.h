#ifndef MIDI_FORMATTER
#define MIDI_FORMATTER

#include "Formatter.h"

class MidiFormatter : public Formatter {
	string filename;
public:
	MidiFormatter() { }
	MidiFormatter(const string name) {this->filename = name;}
	void createFormat(Composition&) override;
};

#endif