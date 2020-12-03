#ifndef XML_FORMATTER
#define XML_FORMATTER

#include "Formatter.h"

class MusicXMLFormatter : public Formatter {
	string filename;
public:
	MusicXMLFormatter() { }
	MusicXMLFormatter(const string name) { this->filename = name; }
	void createFormat(Composition&) override;
	
};


#endif