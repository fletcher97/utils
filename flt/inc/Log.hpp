#if !defined(LOG_HPP)
#define LOG_HPP

#include <string>
#include <fstream>
#include <sstream>

namespace flt
{

#define TRACE 0
#define DEBUG 1
#define INFO 2
#define WARN 3
#define ERROR 4
#define FATAL 5

#define RESET_COLOR "\033[0m"
#define TRACE_COLOR_FG "\033[38;5;238m"
#define DEBUG_COLOR_FG "\033[38;5;243m"
#define INFO_COLOR_FG "\033[38;5;255m"
#define WARN_COLOR_FG "\033[38;5;11m"
#define ERROR_COLOR_FG "\033[38;5;160m"
#define FATAL_COLOR_FG "\033[38;5;0m\033[48;5;160m"

#define LOG_OPEN_FILE(path)
#define LOG_CLOSE_FILE(path)

#define LOG_TRACE(msg)
#define LOG_DEBUG(msg)
#define LOG_INFO(msg)
#define LOG_WARN(msg)
#define LOG_ERROR(msg)
#define LOG_FATAL(msg)

#if defined(DEBUG_LVL)

	#undef LOG_OPEN_FILE
	#define LOG_OPEN_FILE(path) flt::Log::openFile(path);

	#undef LOG_CLOSE_FILE
	#define LOG_CLOSE_FILE(path) flt::Log::closeFile(path);

	#if (DEBUG_LVL <= TRACE)
		#undef LOG_TRACE
		#define LOG_TRACE(msg) {std::stringstream ss; ss<<msg; flt::Log::trace(ss);}
	#endif // TRACE lvl

	#if (DEBUG_LVL <= DEBUG)
		#undef LOG_DEBUG
		#define LOG_DEBUG(msg) {std::stringstream ss; ss<<msg; flt::Log::debug(ss);}
	#endif // DEBUG lvl

	#if (DEBUG_LVL <= INFO)
		#undef LOG_INFO
		#define LOG_INFO(msg) {std::stringstream ss; ss<<msg; flt::Log::info(ss);}
	#endif // INFO lvl

	#if (DEBUG_LVL <= WARN)
		#undef LOG_WARN
		#define LOG_WARN(msg) {std::stringstream ss; ss<<msg; flt::Log::warn(ss);}
	#endif // WARN lvl

	#if (DEBUG_LVL <= ERROR)
		#undef LOG_ERROR
		#define LOG_ERROR(msg) {std::stringstream ss; ss<<msg; flt::Log::error(ss);}
	#endif // ERROR lvl

	#if (DEBUG_LVL <= FATAL)
		#undef LOG_FATAL
		#define LOG_FATAL(msg) {std::stringstream ss; ss<<msg; flt::Log::fatal(ss);}
	#endif // FATAL lvl

#endif // DEBUG_LVL

class Log
{
private:
	static std::ofstream fout;
public:
	static void openFile(const std::string& path);
	static void closeFile(void);

	static void trace(const std::stringstream& msg);
	static void debug(const std::stringstream& msg);
	static void info(const std::stringstream& msg);
	static void warn(const std::stringstream& msg);
	static void error(const std::stringstream& msg);
	static void fatal(const std::stringstream& msg);
};

} // namespace flt

#endif // LOG_HPP
