#include <iostream>

#include "TestCollection.hpp"

flt::TestCollection::TestCollection() {}
flt::TestCollection::~TestCollection() {}

flt::TestCollection&
flt::TestCollection::instance(void) {
	static flt::TestCollection instance;
	return instance;
}

void
flt::TestCollection::addTest(flt::ITestable& t) {
	this->_tests.push_back(&t);
}

void
flt::TestCollection::test(void) {
	for (std::list<flt::ITestable*>::iterator it = this->_tests.begin(); it != this->_tests.end(); it++) {
		(*it)->run();
		this->_count++;
	}
}

void
flt::TestCollection::report(std::ostream& out) const {
	std::cout << "Ran " << this->_count << " groups." << std::endl;
	for (std::list<flt::ITestable*>::const_iterator it = this->_tests.begin(); it != this->_tests.end(); it++) {
		(*it)->report(out);
	}
}
