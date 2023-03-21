#include <iostream>

#include "TestResults.hpp"

void
flt::TestResults::error(flt::AssertError& e) {
	this->_errors.push_back(e);
}

void
flt::TestResults::report(std::ostream& out, const std::string& name) const {
	out << this->_good << "/" << (this->_errors.size() + this->_good) << " tests passed for " << name << "." << std::endl;
	for (std::list<flt::AssertError>::const_iterator it = this->_errors.begin();
			it != this->_errors.end(); it++) {
		it->report(out);
	}
}

void
flt::TestResults::pass(void) {
	this->_good++;
}
