#if !defined(TESTCOLLECTION_HPP)
#define TESTCOLLECTION_HPP

#include <list>
#include <ostream>

#include "ITestable.hpp"

#define ADD_TEST(X) X x##X;

namespace flt
{

class TestCollection
{
private:
	std::list<flt::ITestable*> _tests;
	unsigned long _count;
private:
	TestCollection(void);
public:
	~TestCollection(void);
	static TestCollection& instance(void);
	void addTest(flt::ITestable& t);
	void test(void);
	void report(std::ostream& out) const;
};

} // namespace flt


#endif // TESTCOLLECTION_HPP
