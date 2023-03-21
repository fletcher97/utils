#if !defined(TESTABLE_TPP)
#define TESTABLE_TPP

#include <string>
#include <vector>
#include <stdexcept>

#include "TestResults.hpp"
#include "ITestable.hpp"

#define REGISTER(CLS, X) {this->tests.push_back(&CLS::X);}

#define ASSERT(X) {if (!(X)) {\
		this->_batch.error(__LINE__, __FILE__, __func__, "Assert failed: "#X);\
	} else {\
		this->_batch._good++;}}

#define ASSERT_EQ(X,E) {if (!(X == E)) {\
		this->_batch.error(__LINE__, __FILE__, __func__, "Equality check failed: "#X" differs from "#E);\
	} else {\
		this->_batch._good++;}}

#define ASSERT_NEQ(X,E) {if (!(X != E)) {\
		this->_batch.error(__LINE__, __FILE__, __func__, "Inequality check failed: "#X" is the same as "#E);\
	} else {\
		this->_batch._good++;}}

#define ASSERT_THROW(X,E) {try{\
		X;\
		this->_batch.error(__LINE__, __FILE__, __func__, "Throw check failed: "#X" didn't throw");\
	}catch(E e){\
		this->_batch._good++;\
	}catch (...){\
		this->_batch.error(__LINE__, __FILE__, __func__, "Throw check failed: "#X" didn't trhow the expected "#E" type");}}

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
