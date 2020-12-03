#include "MusicXMLFormatter.h"

void MusicXMLFormatter::createFormat(Composition &c){
	ofstream file;
	file.open(filename);
	file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
	file << "<!DOCTYPE score-partwise PUBLIC" << endl;
	file << "\"-//Recordare//DTD MusicXML 3.1 Partwise//EN\"" << endl;
	file << "\"http://www.musicxml.org/dtds/partwise.dtd\">" << endl;
	file << "<score-partwise version=\"3.1\">" << endl;
	file << "<part-list>" << endl;
	file << "<score-part id=\"Right\"></score-part>"<<endl;
	file << "<score-part id=\"Left\"></score-part>"<<endl;
	file << "</part-list>" << endl;

	file << "<part id=\"Right\">" << endl;
	file << "<measure>" << endl;
	file << "<attributes>" << endl;
	file << "<divisions>2</divisions>" << endl;
	file << "<time>" << endl;
	file << "<beats>"; file << c.getLeftPart().getMaxDurration().brojilac; file<<"</beats>" << endl;
	file << "<beat-type>"; file << c.getLeftPart().getMaxDurration().imenilac; file << "</beat-type>" << endl;
	file << "</time>" << endl;
	file << "<clef>" << endl;
	file << "<sign>G</sign>" << endl;
	file << "<line>2</line>" << endl;
	file << "</clef>" << endl;
	file << "</attributes>" << endl;

	vector<Measure>::iterator ptr;
	int i;
	for (i = 0, ptr = c.getRightPart().begin(); ptr != c.getRightPart().end(); ++ptr, i++) {
		Measure tmpMeasure = *ptr;
		if (ptr != c.getRightPart().begin()) file << "<measure>" << endl;
		for (int j = 0; j < tmpMeasure.getSize(); j++) {
			MusicSymbol& tmpSymbol = tmpMeasure.getMusicSymbol(j);
			int x = tmpSymbol.getType();
			if (x != 0) {
				//nota
				if (x == 1) {
					file << "<note>" << endl;
					file << "<pitch>" << endl;
					file << "<step>" << tmpSymbol.getTone() << "</step>" << endl;
					file << "<octave>" << tmpSymbol.getOctave() << "</octave>" << endl;
					if (tmpSymbol.getSharp()) file << "<alter>1</alter>" << endl;
					file << "</pitch>" << endl;
					file << "<duration>" << (tmpSymbol.getDuration().imenilac == 8 ? 1 : 2) << "</duration>" << endl;
					if (tmpSymbol.isDivided()) {
						if (j == 0) file << "<tie type=\"end\"/>" << endl;
						else if (j == tmpMeasure.getSize() - 1) file << "<tie type=\"start\"/>" << endl;
					}
					file << "</note>" << endl;
				}
				//akord
				if (x == 2) {
					for (int cnt = 0; cnt < tmpSymbol.getNumOfNotes(); cnt++) {
						file << "<note>" << endl;
						if (cnt != 0) file << "<chord/>" << endl;
						file << "<pitch>" << endl;
						file << "<step>" << tmpSymbol.getNote(cnt).getTone() << "</step>" << endl;
						file << "<octave>" << tmpSymbol.getNote(cnt).getOctave() << "</octave>" << endl;
						if (tmpSymbol.getNote(cnt).getSharp()) file << "<alter>1</alter>" << endl;
						file << "</pitch>" << endl;
						file << "<duration>" << (tmpSymbol.getDuration().imenilac == 8 ? 1 : 2) << "</duration>" << endl;
						if (tmpSymbol.isDivided()) {
							if (j == 0) file << "<tie type=\"end\"/>" << endl;
							else if (j == tmpMeasure.getSize() - 1) file << "<tie type=\"start\"/>" << endl;
						}
						file << "</note>" << endl;
					}
				}
			}
			else {
				file << "<note>" << endl;
				file << "<rest/>" << endl;
				file << "<duration>" << (tmpSymbol.getDuration().imenilac == 8 ? 1 : 2) << "</duration>" << endl;
				file << "</note>" << endl;
			}
		}
		file << "</measure>" << endl;
	}
	file << "</part>" << endl;

	file << "<part id=\"Left\">" << endl;
	file << "<measure>" << endl;
	file << "<attributes>" << endl;
	file << "<divisions>2</divisions>" << endl;
	file << "<time>" << endl;
	file << "<beats>"; file << c.getLeftPart().getMaxDurration().brojilac; file << "</beats>" << endl;
	file << "<beat-type>"; file << c.getLeftPart().getMaxDurration().imenilac; file << "</beat-type>" << endl;
	file << "</time>" << endl;
	file << "<clef>" << endl;
	file << "<sign>F</sign>" << endl;
	file << "<line>4</line>" << endl;
	file << "</clef>" << endl;
	file << "</attributes>" << endl;
	for (i = 0, ptr = c.getLeftPart().begin(); ptr != c.getLeftPart().end(); ++ptr, i++) {
		Measure tmpMeasure = *ptr;
		if (ptr != c.getLeftPart().begin()) file << "<measure>" << endl;
		for (int j = 0; j < tmpMeasure.getSize() && j < tmpMeasure.getSize(); j++) {
			MusicSymbol& tmpSymbol = tmpMeasure.getMusicSymbol(j);
			int x = tmpSymbol.getType();
			if (x != 0) {
				if (x == 1) {
					file << "<note>" << endl;
					file << "<pitch>" << endl;
					file << "<step>" << tmpSymbol.getTone() << "</step>" << endl;
					file << "<octave>" << tmpSymbol.getOctave() << "</octave>" << endl;
					if (tmpSymbol.getSharp()) file << "<alter>1</alter>" << endl;
					file << "</pitch>" << endl;
					file << "<duration>" << (tmpSymbol.getDuration().imenilac == 8 ? 1 : 2) << "</duration>" << endl;
					if (tmpSymbol.isDivided()) {
						if (j == 0) file << "<tie type=\"end\"/>" << endl;
						else if (j == tmpMeasure.getSize() - 1) file << "<tie type=\"start\"/>" << endl;
					}
					file << "</note>" << endl;
				}
				if (x == 2) {
					for (int cnt = 0; cnt < tmpSymbol.getNumOfNotes(); cnt++) {
						file << "<note>" << endl;
						if (cnt != 0) file << "<chord/>" << endl;
						file << "<pitch>" << endl;
						file << "<step>" << tmpSymbol.getNote(cnt).getTone() << "</step>" << endl;
						file << "<octave>" << tmpSymbol.getNote(cnt).getOctave() << "</octave>" << endl;
						if (tmpSymbol.getNote(cnt).getSharp()) file << "<alter>1</alter>" << endl;
						file << "</pitch>" << endl;
						file << "<duration>" << (tmpSymbol.getDuration().imenilac == 8 ? 1 : 2) << "</duration>" << endl;
						if (tmpSymbol.isDivided()) {
							if (j == 0) file << "<tie type=\"end\"/>" << endl;
							else if (j == tmpMeasure.getSize() - 1) file << "<tie type=\"start\"/>" << endl;
						}
						file << "</note>" << endl;
					}
				}
			}
			else {
				file << "<note>" << endl;
				file << "<rest/>" << endl;
				file << "<duration>" << (tmpSymbol.getDuration().imenilac == 8 ? 1 : 2) << "</duration>" << endl;
				file << "</note>" << endl;
			}
		}
		file << "</measure>" << endl;
	}
	file << "</part>" << endl;

	file << "</score-partwise>";
	file.close();
}
