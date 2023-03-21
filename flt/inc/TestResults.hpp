#if !defined(TESTRESULTS_HPP)
#define TESTRESULTS_HPP

#include <string>
#include <list>

#include "AssertError.hpp"

namespace flt
{

class TestResults
{
private:
	std::list<AssertError> _errors;
public:
	unsigned long _good;
public:
	TestResults(void) : _good(0) {};

	void error(flt::AssertError& e);
	void report(std::ostream& out, const std::string& name) const;
	void pass(void);
};

} // namespace flt


#endif // TESTRESULTS_HPP
