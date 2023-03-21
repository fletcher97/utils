#include <iostream>

#include "AssertError.hpp"

flt::AssertError::AssertError(unsigned long line, const std::string& file,
		const std::string& func, const std::string& code) {
	this->_line = line;
	this->_code = code;
	this->_file = file;
	this->_func = func;
}

flt::AssertError::~AssertError() throw() {}

void
flt::AssertError::report(std::ostream& out) const {
	out << this->_file << ":" << this->_line << ": failed: "
		<< this->_func << std::endl;
	out << "\t" << this->_code << std::endl;
}
