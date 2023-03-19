#include <iostream>

#include "TestResults.hpp"

flt::TestResults::Result::Result(unsigned long line, const std::string& file,
		const std::string& func, const std::string& code) {
	this->_line = line;
	this->_code = code;
	this->_file = file;
	this->_func = func;
}

void
flt::TestResults::Result::report(std::ostream& out) const {
	out << this->_file << ":" << this->_line << ": failed: "
		<< this->_func << std::endl;
	out << "\t" << this->_code << std::endl;
}

void
flt::TestResults::error(unsigned long line, const std::string& file,
		const std::string& func, const std::string& code) {
	this->_results.push_back(Result(line, file, func, code));
}

void
flt::TestResults::report(std::ostream& out, const std::string& name) const {
	out << this->_good << "/" << (this->_results.size() + this->_good) << " tests passed for " << name << "." << std::endl;
	for (std::list<Result>::const_iterator it = this->_results.begin();
			it != this->_results.end(); it++) {
		it->report(out);
	}
}
