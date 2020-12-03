#include "Composition.h"


void Composition::deleteComposition() {
	filename.clear();
	duzinaTakta.imenilac = 0; duzinaTakta.brojilac = 0;
	m.clear();
	leftPart.clear();
	rightPart.clear();
}

void Composition::iterationThroughTheMeasures() {
	vector<Measure>::iterator ptr1, ptr2;
	int i;
	for (i = 1, ptr1 = getLeftPart().begin(), ptr2 = getRightPart().begin(); ptr1 != getLeftPart().end(), ptr2 != getRightPart().end(); ++ptr1, ++ptr2, i++) {
		Measure tmpMeasureLeft = *ptr1;
		Measure tmpMeasureRight = *ptr2;
		cout << i <<". "<< "Levi: " << tmpMeasureLeft << endl;
		cout << i << ". " << "Desni:" << tmpMeasureRight << endl;
		cout << "===================================================" << endl;
	}
}

void Composition::loadMap(string filename)
{
	ifstream datCsv(filename);
	if (!datCsv.is_open()) { cout << "Greska sa datotekom." << endl; return; }

	string lineText;
	regex rx("([^,]+),([A-Z])(#?)([0-9]+),([0-9]+)");

	while (getline(datCsv, lineText)) {
		smatch result;
		MapStruct data;
		if (regex_match(lineText, result, rx)) {
			data.sharp = result.str(3) == "#";
			data.octave = stoi(result.str(4));
			string tmp = result.str(2);
			data.tone = tmp[0];
			data.midi = stoi(result.str(5));
			tmp = result.str(0);
			m[tmp[0]] = data;
		}
		else cout << "dont match" << endl;
	}
	datCsv.close();
}

void Composition::fillWithPauses(Measure& leftMeasure, Measure& rightMeasure) {
	bool full = false;
	if (!leftMeasure.isFull()) {
		while (!leftMeasure.isFull() && !full) {
			Pause p1 = Pause(Razlomak(1, 4), 0);
			if (leftMeasure.getCurrDuration() + p1.getDuration() <= leftMeasure.getMaxDuration()) {
				if ((leftMeasure.getCurrDuration() + p1.getDuration()).isEqual(leftMeasure.getMaxDuration())) {
					leftMeasure.add(p1);
					full = true;
					leftPart.add(leftMeasure);
					leftMeasure.clearVector();
					leftMeasure.finish();
				}
				else leftMeasure.add(p1);
			}
			else {
				Pause p2 = Pause(Razlomak(1, 8), 0);
				leftMeasure.add(p2);
				full = true;
				leftPart.add(leftMeasure);
				leftMeasure.clearVector();
				leftMeasure.finish();
			}
		}
	}
	else {
		leftPart.add(leftMeasure);
		leftMeasure.clearVector();
		leftMeasure.finish();
	}

	full = false;
	if (!rightMeasure.isFull()) {
		while (!rightMeasure.isFull() && !full) {
			Pause p1 = Pause(Razlomak(1, 4), 0);
			if (rightMeasure.getCurrDuration() + p1.getDuration() <= rightMeasure.getMaxDuration()) {
				if ((rightMeasure.getCurrDuration() + p1.getDuration()).isEqual(rightMeasure.getMaxDuration())) {
					rightMeasure.add(p1);
					full = true;
					rightPart.add(rightMeasure);
					rightMeasure.clearVector();
					rightMeasure.finish();
				}
				else rightMeasure.add(p1);
			}
			else {
				Pause p2 = Pause(Razlomak(1, 8), 0);
				rightMeasure.add(p2);
				full = true;
				rightPart.add(rightMeasure);
				rightMeasure.clearVector();
				rightMeasure.finish();
			}
		}
	}
	else {
		rightPart.add(rightMeasure);
		rightMeasure.clearVector();
		rightMeasure.finish();
	}
}

void Composition::changeDuration(Razlomak n) {
	duzinaTakta = n;
	leftPart.clear();
	rightPart.clear();
	loadComposition();
}

void Composition::moveCompositionUp(int x){
	vector<Measure>::iterator ptr;
	int i;
	for (i = 0, ptr = getLeftPart().begin(); ptr != getLeftPart().end(); ++ptr, i++) {
		Measure tmpMeasure = *ptr;
		for (int j = 0; j < tmpMeasure.getSize(); j++) {
			MusicSymbol& tmpSymbol = tmpMeasure.getMusicSymbol(j);
			int tp = tmpSymbol.getType();
			if (tp != 0) {
				if (tp == 1) {
					if (tmpSymbol.getOctave() + x <= 6) {
						tmpSymbol.changeOctaveUp(x);
					}
				}
				if (tp == 2) {
					for (int cnt = 0; cnt < tmpSymbol.getNumOfNotes(); cnt++) {
						if (tmpSymbol.getNote(cnt).getOctave() + x <= 6) tmpSymbol.getNote(cnt).changeOctaveUp(x);
					}
				}
			}
		}
	}
}

void Composition::moveCompositionDown(int x)
{
	vector<Measure>::iterator ptr;
	int i;
	for (i = 0, ptr = getLeftPart().begin(); ptr != getLeftPart().end(); ++ptr, i++) {
		Measure tmpMeasure = *ptr;
		for (int j = 0; j < tmpMeasure.getSize(); j++) {
			MusicSymbol& tmpSymbol = tmpMeasure.getMusicSymbol(j);
			int tp = tmpSymbol.getType();
			if (tp != 0) {
				if (tp == 1) {
					if (tmpSymbol.getOctave() - x >= 2) {
						tmpSymbol.changeOctaveDown(x);
					}
				}
				if (tp == 2) {
					for (int cnt = 0; cnt < tmpSymbol.getNumOfNotes(); cnt++) {
						if (tmpSymbol.getNote(cnt).getOctave() - x >= 2) tmpSymbol.getNote(cnt).changeOctaveDown(x);
					}
				}
			}
		}
	}
}

void Composition::addPauseBoth(Measure& leftMeasure, Measure& rightMeasure, Pause& p) {

	if (rightMeasure.isFull()) {
		rightPart.add(rightMeasure);
		rightMeasure.clearVector();
		rightMeasure.add(p);
	}
	else {
		if (p.getDuration() + rightMeasure.getCurrDuration() > rightMeasure.getMaxDuration()) {
			Pause p1 = Pause(Razlomak(1, 8), 0);
			p1.setDivided();
			rightMeasure.add(p1);
			rightPart.add(rightMeasure);
			rightMeasure.clearVector();
			rightMeasure.add(p1);
		}
		else rightMeasure.add(p);
	}

	if (leftMeasure.isFull()) {
		leftPart.add(leftMeasure);
		leftMeasure.clearVector();
		leftMeasure.add(p);
	}
	else {
		if (p.getDuration() + leftMeasure.getCurrDuration() > leftMeasure.getMaxDuration()) {
			Pause p1 = Pause(Razlomak(1, 8), 0);
			p1.setDivided();
			leftMeasure.add(p1);
			leftPart.add(leftMeasure);
			leftMeasure.clearVector();
			leftMeasure.add(p1);
		}
		else leftMeasure.add(p);
	}
}

void Composition::addPauseSingle(Measure& measure, Pause& p, int i) {
	if (measure.isFull()) {
		if (i == 1) leftPart.add(measure);
		else rightPart.add(measure);
		measure.clearVector();
		measure.add(p);
	}
	else {
		if (p.getDuration() + measure.getCurrDuration() > measure.getMaxDuration()) {
			Pause p1 = Pause(Razlomak(1, 8), 0);
			p1.setDivided();
			measure.add(p1);
			if (i == 1) leftPart.add(measure);
			else rightPart.add(measure);
			measure.clearVector();
			measure.add(p1);
		}
		else measure.add(p);
	}
}

void Composition::addChord(Measure & measure, Chord & chord, int i) {
	if (measure.isFull()) {
		if (i == 1) leftPart.add(measure);
		else rightPart.add(measure);
		measure.clearVector();
		measure.add(chord);
	}
	else {
		if (chord.getDuration() + measure.getCurrDuration() > measure.getMaxDuration()) {
			Chord c1 = Chord(chord, Razlomak(1, 8), 2);
			c1.setDivided();
			measure.add(c1);
			if (i == 1) leftPart.add(measure);
			else rightPart.add(measure);
			measure.clearVector();
			measure.add(c1);
		}
		else measure.add(chord);
	}
}
//nota u m1, pauza u m2
void Composition::addNote(Measure & m1, Measure & m2, Note & n, Pause & p, int i) {
	int tmp;
	if (i == 2) tmp = 1;
	else tmp = 2;
	addPauseSingle(m2, p, tmp);
	if (m1.isFull()) {
		if (i == 1) leftPart.add(m1);
		else rightPart.add(m1);
		m1.clearVector();
		m1.add(n);
	}
	else {
		if (n.getDuration() + m1.getCurrDuration() > m1.getMaxDuration()) {
			Note n1 = Note(n.getSharp(), n.getMidi(), n.getOctave(), n.getTone(), Razlomak(1, 8), 1);
			n1.setDivided();
			m1.add(n1);
			if (i == 1) leftPart.add(m1);
			else rightPart.add(m1);
			m1.clearVector();
			m1.add(n1);
		}
		else m1.add(n);
	}
}

bool Composition::loadComposition() {
	if (duzinaTakta.imenilac != 4 && duzinaTakta.imenilac != 8) cout << "Greska! Imenilac razlomka mora da bude 4 ili 8." << endl;
	ifstream input_file(filename);
	if (!input_file.is_open()) { cout << "Greska sa otvaranjem datoteke." << endl; return false; }

	string lineText;
	Measure leftMeasure(duzinaTakta), rightMeasure(duzinaTakta);
	regex rg("([^\\[])?(\\[[^\\]]*\\])?");
	while (getline(input_file, lineText)) {
		sregex_iterator currentMatch(lineText.begin(), lineText.end(), rg);
		sregex_iterator lastMatch;
		while (currentMatch != lastMatch) {
			string tmp;
			smatch result = *currentMatch;
			if (result.str(1).length() > 0) {
				tmp = result.str(1);

				if (tmp[0] == ' ') {
					Pause p = Pause(Razlomak(1, 8), 0);
					addPauseBoth(leftMeasure, rightMeasure, p);
				}

				if (tmp[0] == '|') {
					Pause p = Pause(Razlomak(1, 4), 0);
					addPauseBoth(leftMeasure, rightMeasure, p);
				}

				if (tmp[0] != ' ' && tmp[0] != '|') {
					bool s = m[tmp[0]].sharp;
					int midi = m[tmp[0]].midi;
					int octave = m[tmp[0]].octave;
					char tone = m[tmp[0]].tone;
					Note n = Note(s, midi, octave, tone, Razlomak(1, 4), 1);
					Pause p = Pause(Razlomak(1, 4), 0);
					if (n.getOctave() > 3) addNote(rightMeasure, leftMeasure, n, p, 2);
					else addNote(leftMeasure, rightMeasure, n, p, 1);
				}
			}

			if (result.str(2).length() > 0) {
				tmp = result.str(2);
				bool hasSpace = false;
				for (int i = 1; i < tmp.length() - 1; i++) {
					if (tmp[i] == ' ') { hasSpace = true; break; }
				}
				if (hasSpace) {
					for (int i = 1; i < tmp.length() - 1; i++) {
						if (tmp[i] != ' ') {
							bool s = m[tmp[i]].sharp;
							int midi = m[tmp[i]].midi;
							int octave = m[tmp[i]].octave;
							char tone = m[tmp[i]].tone;
							Note n = Note(s, midi, octave, tone, Razlomak(1, 8), 1);
							Pause p = Pause(Razlomak(1, 8), 0);
							if (n.getOctave() > 3) addNote(rightMeasure, leftMeasure, n, p, 2);
							else addNote(leftMeasure, rightMeasure, n, p, 1);
						}
					}
				}
				else {
					Chord leftChord = Chord(Razlomak(1, 4), 2), rightChord = Chord(Razlomak(1, 4), 2);
					for (int i = 1; i < tmp.length() - 1; i++) {
						bool s = m[tmp[i]].sharp;
						int midi = m[tmp[i]].midi;
						int octave = m[tmp[i]].octave;
						char tone = m[tmp[i]].tone;
						Note n = Note(s, midi, octave, tone, Razlomak(1, 4), 1);
						if (n.getOctave() > 3) rightChord.add(n);
						else leftChord.add(n);
					}
					Pause p = Pause(Razlomak(1, 4), 0);
					if (leftChord.getNumOfNotes() == 0) addPauseSingle(leftMeasure, p, 1);
					else addChord(leftMeasure, leftChord, 1);
					if (rightChord.getNumOfNotes() == 0) addPauseSingle(rightMeasure, p, 2);
					else addChord(rightMeasure, rightChord, 2);
				}
			}
			currentMatch++;
		}

	}
	fillWithPauses(leftMeasure, rightMeasure);
	leftMeasure.clearVector();
	rightMeasure.clearVector();
	input_file.close();
	return true;
}

