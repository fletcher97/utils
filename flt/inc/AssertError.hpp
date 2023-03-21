#if !defined(ASSERTERROR_HPP)
#define ASSERTERROR_HPP

#include <stdexcept>
#include <string>

#define ASSERT(X) {if (!(X)) {\
		throw flt::AssertError(__LINE__, __FILE__, __func__, "Assert failed: "#X);\
	}}

#define ASSERT_EQ(X,E) {if (!(X == E)) {\
		throw flt::AssertError(__LINE__, __FILE__, __func__, "Equality check failed: "#X" differs from "#E);\
	}}

#define ASSERT_NEQ(X,E) {if (!(X != E)) {\
		throw flt::AssertError(__LINE__, __FILE__, __func__, "Inequality check failed: "#X" is the same as "#E);\
	}}

#define ASSERT_THROW(X,E) {try{\
		X;\
		throw flt::AssertError(__LINE__, __FILE__, __func__, "Throw check failed: "#X" didn't throw");\
	}catch(E e){} catch (...){\
		throw flt::AssertError(__LINE__, __FILE__, __func__, "Throw check failed: "#X" didn't trhow the expected "#E" type");}}

namespace flt
{

class AssertError : public std::exception
{
private:
	unsigned long _line;
	std::string _file;
	std::string _func;
	std::string _code;
public:
	AssertError(unsigned long line, const std::string& file,
			const std::string& func, const std::string& code);
	virtual ~AssertError() throw();
	void report(std::ostream& out) const;
};

} // namespace flt

#endif // ASSERTERROR_HPP
