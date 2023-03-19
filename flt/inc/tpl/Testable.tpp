#if !defined(TESTABLE_TPP)
#define TESTABLE_TPP

#include <string>
#include <vector>

#include "TestResults.hpp"
#include "ITestable.hpp"

#define REGISTER(CLS, X) {this->tests.push_back(&CLS::X);}

#define ASSERT(X) {if (!(X)) {\
		this->_batch.error(__LINE__, __FILE__, __func__, #X);\
	} else {\
		this->_batch._good++;}}

namespace flt
{

template<typename T>
class Testable : public ITestable
{
protected:
	const std::string _name;
	TestResults _batch;
	std::vector<void (T::*)(void)> tests;
public:
	Testable(const std::string name);
	virtual ~Testable() {};
	virtual void run(void);
	virtual void report(std::ostream& out) const;
};

} // namespace flt

#include "Testable.ipp"

#endif // TESTABLE_TPP
