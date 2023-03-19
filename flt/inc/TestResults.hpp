#if !defined(TESTRESULTS_HPP)
#define TESTRESULTS_HPP

#include <string>
#include <list>

namespace flt
{

class TestResults
{
private:
	class Result {
	private:
		unsigned long _line;
		std::string _file;
		std::string _func;
		std::string _code;
	public:
		explicit Result(unsigned long line, const std::string& file,
			const std::string& func, const std::string& code);
		void report(std::ostream& out) const;
	};

private:
	std::list<Result> _results;
public:
	unsigned long _good;
public:
	TestResults(void) : _good(0) {};
	void error(unsigned long line, const std::string& file,
		const std::string& func, const std::string& code);
	void report(std::ostream& out, const std::string& name) const;
};

} // namespace flt


#endif // TESTRESULTS_HPP
