#include "Measure.h"
#include "Greske.h"

Measure& Measure::add(const MusicSymbol& t) {
	symbols.push_back(t.kopija());
	currDuration = currDuration + t;
	return *this;
}

void Measure::clearVector() {
	symbols.clear();
	finished = false;
	currDuration = Razlomak(0);
}
