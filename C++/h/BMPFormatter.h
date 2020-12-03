#ifndef BMP_FORMATTER_H
#define BMP_FORMATTER_H

#include "Formatter.h"


struct BMPHeader{
	long size_of_file;
	long reserve;
	long offset_of_pixle_data;
	long size_of_header;
	long width;
	long hight;
	short num_of_colour_plane;
	short num_of_bit_per_pix;
	long compression;
	long size_of_bitmap;
	long h_resolution;
	long v_resolution;
	long num_of_colour_in_palette;
	long important_colours;
};

struct RGBInfo {
	int red;
	int green;
	int blue;
	RGBInfo() { }
	RGBInfo(int r, int g, int b) :red(r), green(g), blue(b) { }
	void setRed(int r) { this->red = r; }
	void setGreen(int g) { this->green = g; }
	void setBlue(int b) { this->blue = b; }
	int getRed() const { return red; }
	int getGreen() const { return green; }
	int getBlue() const { return blue; }
};


class BMPFormatter : public Formatter {
	string filename;
	int width;
	BMPHeader header;
	map<pair<char, bool>,RGBInfo> mapRGB;
public:
	BMPFormatter() { }
	BMPFormatter(const string name) { this->filename = name; }
	void createFormat(Composition&) override;
	void setWidth(int w) { this->width = w; }
	int expandTo4(int&);
	void getBGR(int&, int&, int&,int,char,bool);
	void createMap();
};

#endif