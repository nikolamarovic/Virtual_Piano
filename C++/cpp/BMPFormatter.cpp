#include "BMPFormatter.h"

struct Header;
struct NoteInfo;
struct RGBInfo;

void BMPFormatter::createMap() {
	pair<char,bool> info;
	info.first = 'C'; info.second = false;
	mapRGB[info] = RGBInfo(255, 0, 0);

	info.first = 'C'; info.second = true;
	mapRGB[info] = RGBInfo(255,127,0);

	info.first = 'D'; info.second = false;
	mapRGB[info] = RGBInfo(255, 255, 0);

	info.first = 'D'; info.second = true;
	mapRGB[info] = RGBInfo(127, 255, 0);

	info.first = 'E'; info.second = false;
	mapRGB[info] = RGBInfo(0, 255, 0);

	info.first = 'F'; info.second = false;
	mapRGB[info] = RGBInfo(0, 255, 127);

	info.first = 'F'; info.second = true;
	mapRGB[info] = RGBInfo(0, 255, 255);

	info.first = 'G'; info.second = false;
	mapRGB[info] = RGBInfo(0, 127, 255);

	info.first = 'G'; info.second = true;
	mapRGB[info] = RGBInfo(0, 0, 255);

	info.first = 'A'; info.second = false;
	mapRGB[info] = RGBInfo(127, 0, 255);

	info.first = 'A'; info.second = true;
	mapRGB[info] = RGBInfo(255, 0, 255);

	info.first = 'B'; info.second = false;
	mapRGB[info] = RGBInfo(255, 0, 127);
}


void BMPFormatter::getBGR(int &B, int &G, int &R, int oct, char t, bool s) {
	pair<char, bool> info; int x;
	info.first = t; info.second = s;
	if (oct == 2) {
		x = mapRGB[info].blue;
		B = (x - ((x / 8) * 6));
		x = mapRGB[info].green;
		G = (x - ((x / 8) * 6));
		x = mapRGB[info].red;
		R = (x - ((x / 8) * 6));
	}
	if (oct == 3) {
		x = mapRGB[info].blue;
		B = (x - ((x / 8) * 3));
		x = mapRGB[info].green;
		G = (x - ((x / 8) * 3));
		x = mapRGB[info].red;
		R = (x - ((x / 8) * 3));
	}
	if (oct == 5) {
		x = mapRGB[info].blue;
		B = (x + (((255 - x) / 8) * 3));
		x = mapRGB[info].green;
		G = (x + (((255 - x) / 8) * 3));
		x = mapRGB[info].red;
		R = (x + (((255 - x) / 8) * 3));
	}
	if (oct == 6) {
		x = mapRGB[info].blue;
		B = (x - (((255 - x) / 8) * 6));
		x = mapRGB[info].green;
		G = (x - (((255 - x) / 8) * 6));
		x = mapRGB[info].red;
		R = (x - (((255 - x) / 8) * 6));
	}
	if (oct == 4) {
		B = mapRGB[info].blue;
		G = mapRGB[info].green;
		R = mapRGB[info].red;
	}
}

short BM = 0x4d42;

int BMPFormatter::expandTo4(int& x) {
	while (x % 4 != 0) x++;
	return x;
}

void BMPFormatter::createFormat(Composition &c) {
	ofstream file;
	file.open(filename, ios::out | ios::binary);
	int expandedWidth = width * 3;
	expandTo4(expandedWidth);

	vector<string> queues;
	string s;

	vector<Measure>::iterator ptr1, ptr2;
	int i; bool wasChordInLeft = false, wasChordInRight = false, wasPauseInLeft = false, wasPauseInRight = false;
	int tmpBlueLeft, tmpGreenLeft, tmpRedLeft, tmpBlueRight, tmpGreenRight, tmpRedRight;
	char tmpTone; bool tmpSharp; int tmpOctave;
	int arithMeanBlueLeft = 0, arithMeanGreenLeft = 0, arithMeanRedLeft = 0;
	int arithMeanBlueRight = 0, arithMeanGreenRight = 0, arithMeanRedRight = 0;

	for (i = 0, ptr1 = c.getLeftPart().begin(), ptr2 = c.getRightPart().begin(); ptr1 != c.getLeftPart().end(), ptr2 != c.getRightPart().end(); ++ptr1, ++ptr2, i++) {
		Measure tmpMeasureLeft = *ptr1;
		Measure tmpMeasureRight = *ptr2;
		for (int j = 0; j < tmpMeasureLeft.getSize(); j++) {
			MusicSymbol& tmpSymbolLeft = tmpMeasureLeft.getMusicSymbol(j);
			MusicSymbol& tmpSymbolRight = tmpMeasureRight.getMusicSymbol(j);
			int typeLeft = tmpSymbolLeft.getType();
			int typeRight = tmpSymbolRight.getType();

			if (typeLeft != 0) {
				//nota
				if (typeLeft == 1) {
					if (tmpSymbolLeft.getDuration().imenilac == 8) {
						if ((s.length() + 3) > expandedWidth) {
							for (int cnt = s.length(); cnt < expandedWidth; cnt++) s += (char)255;
							queues.push_back(s);
							s.clear();
						}
						tmpTone = tmpSymbolLeft.getTone(); tmpSharp = tmpSymbolLeft.getSharp(); tmpOctave = tmpSymbolLeft.getOctave();
						getBGR(tmpBlueLeft, tmpGreenLeft, tmpRedLeft, tmpOctave, tmpTone, tmpSharp);
						s += (char)tmpBlueLeft; s += (char)tmpGreenLeft; s += (char)tmpRedLeft;
					}
					else {
						int z = expandedWidth - s.length();
						if (z <= 6) {
							if (z == 6) {
								tmpTone = tmpSymbolLeft.getTone(); tmpSharp = tmpSymbolLeft.getSharp(); tmpOctave = tmpSymbolLeft.getOctave();
								getBGR(tmpBlueLeft, tmpGreenLeft, tmpRedLeft, tmpOctave, tmpTone, tmpSharp);
								s += (char)tmpBlueLeft; s += (char)tmpGreenLeft; s += (char)tmpRedLeft;
								s += (char)tmpBlueLeft; s += (char)tmpGreenLeft; s += (char)tmpRedLeft;
								queues.push_back(s); s.clear();
							}
							else {
								if (z >= 3) {
									//popunimo pola, pola u sledeci s;
									tmpTone = tmpSymbolLeft.getTone(); tmpSharp = tmpSymbolLeft.getSharp(); tmpOctave = tmpSymbolLeft.getOctave();
									getBGR(tmpBlueLeft, tmpGreenLeft, tmpRedLeft, tmpOctave, tmpTone, tmpSharp);
									s += (char)tmpBlueLeft; s += (char)tmpGreenLeft; s += (char)tmpRedLeft;
									if (z > 0) while (s.length() < expandedWidth) s += (char)255;
									queues.push_back(s);
									s.clear();
									s += (char)tmpBlueLeft; s += (char)tmpGreenLeft; s += (char)tmpRedLeft;
								}
								else {
									while (s.length() < expandedWidth) s += (char)255;
									queues.push_back(s);
									s.clear();
									tmpTone = tmpSymbolLeft.getTone(); tmpSharp = tmpSymbolLeft.getSharp(); tmpOctave = tmpSymbolLeft.getOctave();
									getBGR(tmpBlueLeft, tmpGreenLeft, tmpRedLeft, tmpOctave, tmpTone, tmpSharp);
									s += (char)tmpBlueLeft; s += (char)tmpGreenLeft; s += (char)tmpRedLeft;
									s += (char)tmpBlueLeft; s += (char)tmpGreenLeft; s += (char)tmpRedLeft;
								}
							}
						}
						else {							
							tmpTone = tmpSymbolLeft.getTone(); tmpSharp = tmpSymbolLeft.getSharp(); tmpOctave = tmpSymbolLeft.getOctave();
							getBGR(tmpBlueLeft, tmpGreenLeft, tmpRedLeft, tmpOctave, tmpTone, tmpSharp);
							s += (char)tmpBlueLeft; s += (char)tmpGreenLeft; s += (char)tmpRedLeft;
							s += (char)tmpBlueLeft; s += (char)tmpGreenLeft; s += (char)tmpRedLeft;
						}
					}
				}
				//akord
				if (typeLeft == 2) {
					wasChordInLeft = true;
					arithMeanBlueLeft = 0, arithMeanGreenLeft = 0, arithMeanRedLeft = 0;
					for (int cnt = 0; cnt < tmpSymbolLeft.getNumOfNotes(); cnt++) {
						tmpTone = tmpSymbolLeft.getNote(cnt).getTone(); tmpSharp = tmpSymbolLeft.getNote(cnt).getSharp(); tmpOctave = tmpSymbolLeft.getNote(cnt).getOctave();
						getBGR(tmpBlueLeft, tmpGreenLeft, tmpRedLeft, tmpOctave, tmpTone, tmpSharp);
						arithMeanBlueLeft += tmpBlueLeft; arithMeanGreenLeft += tmpGreenLeft; arithMeanRedLeft += tmpRedLeft;
					}
					arithMeanBlueLeft /= tmpSymbolLeft.getNumOfNotes();
					arithMeanGreenLeft /= tmpSymbolLeft.getNumOfNotes();
					arithMeanRedLeft /= tmpSymbolLeft.getNumOfNotes();
				}
			}
			else wasPauseInLeft = true;

			if (typeRight != 0) {
				//nota
				if (typeRight == 1) {
					if (tmpSymbolRight.getDuration().imenilac == 8) {
						//padding do kraja reda
						if ((s.length() + 3) > expandedWidth) {
							while(s.length()<expandedWidth) s += (char)255;
							//dodamo napunjen
							queues.push_back(s);
							s.clear();
						}
						//dodajem redosledom 1.BLUE 2.GREEN 3.RED
						tmpTone = tmpSymbolRight.getTone(); tmpSharp = tmpSymbolRight.getSharp(); tmpOctave = tmpSymbolRight.getOctave();
						getBGR(tmpBlueRight, tmpGreenRight, tmpRedRight, tmpOctave, tmpTone, tmpSharp);
						s += (char)tmpBlueRight; s += (char)tmpGreenRight; s += (char)tmpRedRight;
					}
					else {
						int z = expandedWidth - s.length();
						if (z < 6) {
							if (z == 6) {
								tmpTone = tmpSymbolRight.getTone(); tmpSharp = tmpSymbolRight.getSharp(); tmpOctave = tmpSymbolRight.getOctave();
								getBGR(tmpBlueRight, tmpGreenRight, tmpRedRight, tmpOctave, tmpTone, tmpSharp);
								s += (char)tmpBlueRight; s += (char)tmpGreenRight; s += (char)tmpRedRight;
								s += (char)tmpBlueRight; s += (char)tmpGreenRight; s += (char)tmpRedRight;
								queues.push_back(s);
								s.clear();
							}else{
								if (z >= 3) {
									//popunimo pola, pola u sledeci s;
									tmpTone = tmpSymbolRight.getTone(); tmpSharp = tmpSymbolRight.getSharp(); tmpOctave = tmpSymbolRight.getOctave();
									getBGR(tmpBlueRight, tmpGreenRight, tmpRedRight, tmpOctave, tmpTone, tmpSharp);
									s += (char)tmpBlueRight; s += (char)tmpGreenRight; s += (char)tmpRedRight;
									if (z > 0) while (s.length() < expandedWidth) s += (char)255;
									queues.push_back(s);
									s.clear();
									s += (char)tmpBlueRight; s += (char)tmpGreenRight; s += (char)tmpRedRight;
								}
								else {
									while (s.length() < expandedWidth) s += (char)255;
									queues.push_back(s);
									s.clear();
									tmpTone = tmpSymbolRight.getTone(); tmpSharp = tmpSymbolRight.getSharp(); tmpOctave = tmpSymbolRight.getOctave();
									getBGR(tmpBlueRight, tmpGreenRight, tmpRedRight, tmpOctave, tmpTone, tmpSharp);
									s += (char)tmpBlueRight; s += (char)tmpGreenRight; s += (char)tmpRedRight;
									s += (char)tmpBlueRight; s += (char)tmpGreenRight; s += (char)tmpRedRight;
								}
							}
						}
						else {
							tmpTone = tmpSymbolRight.getTone(); tmpSharp = tmpSymbolRight.getSharp(); tmpOctave = tmpSymbolRight.getOctave();
							getBGR(tmpBlueRight, tmpGreenRight, tmpRedRight, tmpOctave, tmpTone, tmpSharp);
							s += (char)tmpBlueRight; s += (char)tmpGreenRight; s += (char)tmpRedRight;
							s += (char)tmpBlueRight; s += (char)tmpGreenRight; s += (char)tmpRedRight;
						}
					}
				}
				//akord
				if (typeRight == 2) {
					wasChordInRight = true;
					arithMeanBlueRight = 0, arithMeanGreenRight = 0, arithMeanRedRight = 0;
					for (int cnt = 0; cnt < tmpSymbolRight.getNumOfNotes(); cnt++) {
						tmpTone = tmpSymbolRight.getNote(cnt).getTone(); tmpSharp = tmpSymbolRight.getNote(cnt).getSharp(); tmpOctave = tmpSymbolRight.getNote(cnt).getOctave();
						getBGR(tmpBlueRight, tmpGreenRight, tmpRedRight, tmpOctave, tmpTone, tmpSharp);
						arithMeanBlueRight += tmpBlueRight; arithMeanGreenRight += tmpGreenRight; arithMeanRedRight += tmpRedRight;
					}
					arithMeanBlueRight /= tmpSymbolRight.getNumOfNotes();
					arithMeanGreenRight /= tmpSymbolRight.getNumOfNotes();
					arithMeanRedRight /= tmpSymbolRight.getNumOfNotes();
				}
			}
			else wasPauseInRight = true;
			
			//ako je bio akord u obe ruke
			if (wasChordInLeft && wasChordInRight) {
				if (tmpSymbolRight.getDuration().imenilac == 8) {
					if ((s.length() + 3) > expandedWidth) {
						while (s.length() < expandedWidth) s += (char)255;
						queues.push_back(s);
						s.clear();
					}
					s += (char)((arithMeanBlueRight + arithMeanBlueLeft) / 2); s += (char)((arithMeanGreenRight + arithMeanGreenLeft) / 2); s += (char)((arithMeanRedRight + arithMeanRedLeft) / 2);
				}
				else {
					int z = expandedWidth - s.length();
					if (z < 6) {
						if (z == 6) {
							s += (char)((arithMeanBlueRight + arithMeanBlueLeft) / 2); s += (char)((arithMeanGreenRight + arithMeanGreenLeft) / 2); s += (char)((arithMeanRedRight + arithMeanRedLeft) / 2);
							s += (char)((arithMeanBlueRight + arithMeanBlueLeft) / 2); s += (char)((arithMeanGreenRight + arithMeanGreenLeft) / 2); s += (char)((arithMeanRedRight + arithMeanRedLeft) / 2);
							queues.push_back(s);
							s.clear();
						}
						else {
							if (z >= 3) {
								//popunimo pola, pola u sledeci s;
								s += (char)((arithMeanBlueRight + arithMeanBlueLeft) / 2); s += (char)((arithMeanGreenRight + arithMeanGreenLeft) / 2); s += (char)((arithMeanRedRight + arithMeanRedLeft) / 2);
								if (z > 0) while (s.length() < expandedWidth) s += (char)255;
								queues.push_back(s);
								s.clear();
								s += (char)((arithMeanBlueRight + arithMeanBlueLeft) / 2); s += (char)((arithMeanGreenRight + arithMeanGreenLeft) / 2); s += (char)((arithMeanRedRight + arithMeanRedLeft) / 2);
							}
							else {
								while (s.length() < expandedWidth) s += (char)255;
								queues.push_back(s);
								s.clear();
								s += (char)((arithMeanBlueRight + arithMeanBlueLeft) / 2); s += (char)((arithMeanGreenRight + arithMeanGreenLeft) / 2); s += (char)((arithMeanRedRight + arithMeanRedLeft) / 2);
								s += (char)((arithMeanBlueRight + arithMeanBlueLeft) / 2); s += (char)((arithMeanGreenRight + arithMeanGreenLeft) / 2); s += (char)((arithMeanRedRight + arithMeanRedLeft) / 2);
							}
						}
					}
					else {
						s += (char)((arithMeanBlueRight + arithMeanBlueLeft) / 2); s += (char)((arithMeanGreenRight + arithMeanGreenLeft) / 2); s += (char)((arithMeanRedRight + arithMeanRedLeft) / 2);
						s += (char)((arithMeanBlueRight + arithMeanBlueLeft) / 2); s += (char)((arithMeanGreenRight + arithMeanGreenLeft) / 2); s += (char)((arithMeanRedRight + arithMeanRedLeft) / 2);
					}
				}
			}

			//ako je akord bio samo u levoj
			if (wasChordInLeft && !wasChordInRight) {
				if (tmpSymbolRight.getDuration().imenilac == 8) {
					if ((s.length() + 3) > expandedWidth) {
						while (s.length() < expandedWidth) s += (char)255;
						queues.push_back(s);
						s.clear();
					}
					s += (char)(arithMeanBlueLeft); s += (char)(arithMeanGreenLeft); s += (char)(arithMeanRedLeft);
				}
				else {
					int z = expandedWidth - s.length();
					if (z < 6) {
						if (z == 6) {
							s += (char)(arithMeanBlueLeft); s += (char)(arithMeanGreenLeft); s += (char)(arithMeanRedLeft);
							s += (char)(arithMeanBlueLeft); s += (char)(arithMeanGreenLeft); s += (char)(arithMeanRedLeft);
							queues.push_back(s);
							s.clear();
						}
						else {
							if (z >= 3) {
								//popunimo pola, pola u sledeci s;
								s += (char)(arithMeanBlueLeft); s += (char)(arithMeanGreenLeft); s += (char)(arithMeanRedLeft);
								if (z > 0) while (s.length() < expandedWidth) s += (char)255;
								queues.push_back(s);
								s.clear();
								s += (char)(arithMeanBlueLeft); s += (char)(arithMeanGreenLeft); s += (char)(arithMeanRedLeft);
							}
							else {
								while (s.length() < expandedWidth) s += (char)255;
								queues.push_back(s);
								s.clear();
								s += (char)(arithMeanBlueLeft); s += (char)(arithMeanGreenLeft); s += (char)(arithMeanRedLeft);
								s += (char)(arithMeanBlueLeft); s += (char)(arithMeanGreenLeft); s += (char)(arithMeanRedLeft);
							}
						}
					}
					else {
						s += (char)(arithMeanBlueLeft); s += (char)(arithMeanGreenLeft); s += (char)(arithMeanRedLeft);
						s += (char)(arithMeanBlueLeft); s += (char)(arithMeanGreenLeft); s += (char)(arithMeanRedLeft);
					}
				}
			}

			//ako je akord samo u desnoj
			if (!wasChordInLeft && wasChordInRight) {
				if (tmpSymbolRight.getDuration().imenilac == 8) {
					if ((s.length() + 3) > expandedWidth) {
						while (s.length() < expandedWidth) s += (char)255;
						queues.push_back(s);
						s.clear();
					}
					s += (char)(arithMeanBlueRight); s += (char)(arithMeanGreenRight); s += (char)(arithMeanRedRight);
				}
				else {
					int z = expandedWidth - s.length();
					if (z < 6) {
						if (z == 6) {
							s += (char)(arithMeanBlueRight); s += (char)(arithMeanGreenRight); s += (char)(arithMeanRedRight);
							s += (char)(arithMeanBlueRight); s += (char)(arithMeanGreenRight); s += (char)(arithMeanRedRight);
							queues.push_back(s);
							s.clear();
						}
						else {
							if (z >= 3) {
								//popunimo pola, pola u sledeci s;
								s += (char)(arithMeanBlueRight); s += (char)(arithMeanGreenRight); s += (char)(arithMeanRedRight);
								if (z > 0) while (s.length() < expandedWidth) s += (char)255;
								queues.push_back(s);
								s.clear();
								s += (char)(arithMeanBlueRight); s += (char)(arithMeanGreenRight); s += (char)(arithMeanRedRight);
							}
							else {
								while (s.length() < expandedWidth) s += (char)255;
								queues.push_back(s);
								s.clear();
								s += (char)(arithMeanBlueRight); s += (char)(arithMeanGreenRight); s += (char)(arithMeanRedRight);
								s += (char)(arithMeanBlueRight); s += (char)(arithMeanGreenRight); s += (char)(arithMeanRedRight);
							}
						}
					}
					else {
						s += (char)(arithMeanBlueRight); s += (char)(arithMeanGreenRight); s += (char)(arithMeanRedRight); 
						s += (char)(arithMeanBlueRight); s += (char)(arithMeanGreenRight); s += (char)(arithMeanRedRight);
					}
				}
			}
			
			if (wasPauseInLeft && wasPauseInRight) {
				if (tmpSymbolLeft.getDuration().imenilac == 8) {
					if ((s.length() + 3) > expandedWidth) {
						for (int cnt = s.length(); cnt < expandedWidth; cnt++) s +=(char)255;
						queues.push_back(s);
						s.clear();
					}
					s +=(char)255; s +=(char)255; s +=(char)255;
				}
				else {
					if ((s.length() + 6) > expandedWidth) {
						for (int cnt = s.length(); cnt < expandedWidth; cnt++) s +=(char)255;
						queues.push_back(s);
						s.clear();
					}
					s += (char)255; s += (char)255; s += (char)255;
					s += (char)255; s += (char)255; s += (char)255;
				}
			}
			wasChordInLeft = wasChordInRight = false;
			wasPauseInLeft = wasPauseInRight = false;
		}
	}



	if (s.length() <= expandedWidth) {
		while (s.size() < expandedWidth) s += (char)255;
		queues.push_back(s);
		s.clear();
	}

	header.size_of_file = 54 + queues.size()*expandedWidth;//ili sizeof(header) + header.size_of_bitmap;
	header.reserve = 0000;
	header.offset_of_pixle_data = 54;
	header.size_of_header = 40;
	header.width = width;//korisnik unosi
	header.hight = queues.size();//mi dobijamo posle
	header.num_of_colour_plane = 1;
	header.num_of_bit_per_pix = 24;
	header.compression = 0; 
	header.size_of_bitmap = expandedWidth * queues.size();//velicina bitmape
	header.h_resolution = 2835;
	header.v_resolution = 2835;
	header.num_of_colour_in_palette = 0;
	header.important_colours = 0;

	file.write((char*)(&BM), 2);
	file.write((char*)(&header), sizeof(header));

	cout << "Vector size is:" << queues.size() << endl;
	//for (int i = queues.size() - 1; i >= 0; i--) file.write((char*)&queues[i], expandedWidth);
	for (int i = queues.size()-1; i >= 0; i--) file << queues[i];

	file.close();
}

