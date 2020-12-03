#include "MIDIFormatter.h"

void MidiFormatter::createFormat(Composition&c){
	MidiFile outputfile;
	outputfile.absoluteTicks();
	vector<uchar> midievent;
	midievent.resize(3);
	int tpq = 48;
	outputfile.setTicksPerQuarterNote(tpq);
	outputfile.addTrack(1);

	vector<Measure>::iterator ptr;
	int i;
	int actiontime = 0;
	midievent[2] = 64;

	for (i = 0, ptr = c.getLeftPart().begin(); ptr != c.getLeftPart().end(); ++ptr, i++) {
		Measure tmpMeasure = *ptr;
		for (int j = 0; j < tmpMeasure.getSize(); j++) {
			MusicSymbol& tmpSymbol = tmpMeasure.getMusicSymbol(j);
			int x = tmpSymbol.getType();
			if (x!=0) {
				//nota
				if (x == 1) {
					if (tmpSymbol.isDivided()) {
						if (j == (tmpMeasure.getSize() - 1)) {
							midievent[0] = 0x90;
							midievent[1] = tmpSymbol.getMidi();
							outputfile.addEvent(1, actiontime, midievent);
							actiontime += (tpq / 2) * 2;
							midievent[0] = 0x80;
							outputfile.addEvent(1, actiontime, midievent);
						}//znaci da je prvi i da je divided i to preskacemo
					}
					else {
						midievent[0] = 0x90;
						midievent[1] = tmpSymbol.getMidi();
						outputfile.addEvent(1, actiontime, midievent);
						if (tmpSymbol.getDuration().imenilac == 8) actiontime += (tpq / 2) * 1;
						else actiontime += (tpq / 2) * 2;
						midievent[0] = 0x80;
						outputfile.addEvent(1, actiontime, midievent);
					}
				}
				//akord
				if (x == 2) {
					bool changed = false;
					int tmpActionTime = actiontime;
					tmpActionTime += (tpq / 2) * 2;
					if (tmpSymbol.isDivided()) {
						if (j == (tmpMeasure.getSize() - 1)) {
							changed = true;
							for (int cnt = 0; cnt < tmpSymbol.getNumOfNotes(); cnt++) {
								midievent[0] = 0x90;
								midievent[1] = tmpSymbol.getNote(cnt).getMidi();
								outputfile.addEvent(1, actiontime, midievent);
								midievent[0] = 0x80;
								outputfile.addEvent(1, tmpActionTime, midievent);
							}
						}//znaci da je prvi i da je divided i to preskacemo
					}
					else {
						changed = true;
						for (int cnt = 0; cnt < tmpSymbol.getNumOfNotes(); cnt++) {
							midievent[0] = 0x90;
							midievent[1] = tmpSymbol.getNote(cnt).getMidi();
							outputfile.addEvent(1, actiontime, midievent);
							midievent[0] = 0x80;
							outputfile.addEvent(1, tmpActionTime, midievent);
						}
					}
					if (changed) { actiontime = tmpActionTime; changed = false; }
				}
			}
			else {
				if (tmpSymbol.isDivided()) {
					if (j == (tmpMeasure.getSize() - 1)) {
						actiontime += (tpq / 2) * 2;
					}
				}
				else {
					if (tmpSymbol.getDuration().imenilac == 8) actiontime += (tpq / 2) * 1;
					else actiontime += (tpq / 2) * 2;
				}
			}	
			
		}
	}
	actiontime = 0;
	for (i = 0, ptr = c.getRightPart().begin(); ptr != c.getRightPart().end(); ++ptr, i++) {
		Measure tmpMeasure = *ptr;
		for (int j = 0; j < tmpMeasure.getSize(); j++) {
			MusicSymbol& tmpSymbol = tmpMeasure.getMusicSymbol(j);
			int x = tmpSymbol.getType();
			if (x != 0) {
				//nota
				if (x == 1) {
					if (tmpSymbol.isDivided()) {
						if (j == (tmpMeasure.getSize() - 1)) {
							midievent[0] = 0x90;
							midievent[1] = tmpSymbol.getMidi();
							outputfile.addEvent(0, actiontime, midievent);
							actiontime += (tpq / 2) * 2;
							midievent[0] = 0x80;
							outputfile.addEvent(0, actiontime, midievent);
						}//znaci da je prvi i da je divided i to preskacemo
					}
					else {
						midievent[0] = 0x90;
						midievent[1] = tmpSymbol.getMidi();
						outputfile.addEvent(0, actiontime, midievent);
						if (tmpSymbol.getDuration().imenilac == 8) actiontime += (tpq / 2) * 1;
						else actiontime += (tpq / 2) * 2;
						midievent[0] = 0x80;
						outputfile.addEvent(0, actiontime, midievent);
					}
				}
				//akord
				if (x == 2) {
					bool changed = false;
					int tmpActionTime = actiontime;
					tmpActionTime +=(tpq / 2) * 2;
					if (tmpSymbol.isDivided()) {
						if (j == (tmpMeasure.getSize() - 1)) {
							changed = true;
							for (int cnt = 0; cnt < tmpSymbol.getNumOfNotes(); cnt++) {
								midievent[0] = 0x90;
								midievent[1] = tmpSymbol.getNote(cnt).getMidi();
								outputfile.addEvent(0, actiontime, midievent);
								midievent[0] = 0x80;
								outputfile.addEvent(0, tmpActionTime, midievent);
							}
						}//znaci da je prvi i da je divided i to preskacemo
					}
					else {
						changed = true;
						for (int cnt = 0; cnt < tmpSymbol.getNumOfNotes(); cnt++) {
							midievent[0] = 0x90;
							midievent[1] = tmpSymbol.getNote(cnt).getMidi();
							outputfile.addEvent(0, actiontime, midievent);
							midievent[0] = 0x80;
							outputfile.addEvent(0, tmpActionTime, midievent);
						}
					}
					if (changed) {actiontime = tmpActionTime; changed = false;}
				}
			}
			else {
				if (tmpSymbol.isDivided()) {
					if (j == (tmpMeasure.getSize() - 1)) {
						actiontime += (tpq / 2) * 2;
					}
				}
				else {
					if (tmpSymbol.getDuration().imenilac == 8) actiontime += (tpq / 2) * 1;
					else actiontime += (tpq / 2) * 2;
				}
			}

		}
	}

	outputfile.sortTracks();
	outputfile.write(filename);
}

