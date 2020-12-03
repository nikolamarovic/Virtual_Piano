#ifndef RAZLOMAK_H
#define RAZLOMAK_H

class Razlomak {
public:
	long long imenilac;
	long long brojilac;
	Razlomak() { this->imenilac = 0; this->brojilac = 0; }
	Razlomak(int a, int b=1) :imenilac(b), brojilac(a) { }
	Razlomak& operator+=(Razlomak t) {
		if (this->brojilac == 0 && this->imenilac == 0) {
			this->brojilac = t.brojilac;
			this->imenilac = t.imenilac;
		}
		this->brojilac = this->brojilac * t.imenilac + this->imenilac * t.brojilac;
		this->imenilac *= t.imenilac;
		return *this;
	}
	bool isEqual(const Razlomak& r2) {
		return this->brojilac*r2.imenilac == this->imenilac*r2.brojilac;
	}
	string opis() const { string s = ""; s +=to_string(brojilac); s += "/"; s +=to_string(imenilac); return s; }
	friend Razlomak operator+(const Razlomak& r1, const Razlomak& r2) {
		return Razlomak(r1.brojilac * r2.imenilac + r2.brojilac * r1.imenilac, r1.imenilac * r2.imenilac);
	}
	friend bool operator>(const Razlomak& r1, const Razlomak& r2) {
		return r1.brojilac*r2.imenilac > r1.imenilac*r2.brojilac;
	}
	friend bool operator>=(const Razlomak& r1, const Razlomak& r2) {
		return r1.brojilac* r2.imenilac >= r1.imenilac* r2.brojilac;
	}
	friend bool operator<=(const Razlomak& r1, const Razlomak& r2) {
		return r1.brojilac* r2.imenilac <= r1.imenilac* r2.brojilac;
	}
	friend ostream& operator<<(ostream& it, const Razlomak& r) {
		return it << r.brojilac << "/" << r.imenilac;
	}
};

#endif