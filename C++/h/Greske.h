#ifndef GRESKE_H
#define GRESKE_H

#include<exception>

class GTaktZavrsen : public exception {
	string r = "Takt je zavrsen.";
public:
	GTaktZavrsen(string raz) :r(raz) { }
	GTaktZavrsen() = default;
	const char* what() const override { return r.c_str(); }
};

class GPartZavrsen : public exception {
	string r = "Part je zavrsen.";
public:
	GPartZavrsen(string raz) :r(raz) {}
	GPartZavrsen() = default;
	const char* what() const override { return r.c_str(); }
};

class GTrajanje :public exception {
public:
	const char* what() const override {
		return "Prekoracenje trajanja takta.";
	}
};
#endif