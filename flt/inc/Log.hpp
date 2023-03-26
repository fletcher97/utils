#if !defined(LOG_HPP)
#define LOG_HPP

#include <string>
#include <fstream>
#include <sstream>

namespace flt
{

#define FLT_LOG_TRACE_LVL 0
#define FLT_LOG_DEBUG_LVL 1
#define FLT_LOG_INFO_LVL 2
#define FLT_LOG_WARN_LVL 3
#define FLT_LOG_ERROR_LVL 4
#define FLT_LOG_FATAL_LVL 5

#define FLT_LOG_RESET_COLOR "\033[0m"
#define FLT_LOG_TRACE_COLOR_FG "\033[38;5;238m"
#define FLT_LOG_DEBUG_COLOR_FG "\033[38;5;243m"
#define FLT_LOG_INFO_COLOR_FG "\033[38;5;255m"
#define FLT_LOG_WARN_COLOR_FG "\033[38;5;11m"
#define FLT_LOG_ERROR_COLOR_FG "\033[38;5;160m"
#define FLT_LOG_FATAL_COLOR_FG "\033[38;5;0m\033[48;5;160m"

#define LOG_OPEN_FILE(path)
#define LOG_CLOSE_FILE(path)

#define LOG_TRACE(msg)
#define LOG_DEBUG(msg)
#define LOG_INFO(msg)
#define LOG_WARN(msg)
#define LOG_ERROR(msg)
#define LOG_FATAL(msg)

#if defined(LOG_LVL)

	#undef LOG_OPEN_FILE
	#define LOG_OPEN_FILE(path) flt::Log::openFile(path);

	#undef LOG_CLOSE_FILE
	#define LOG_CLOSE_FILE(path) flt::Log::closeFile(path);

	#if (LOG_LVL <= FLT_LOG_TRACE_LVL)
		#undef LOG_TRACE
		#define LOG_TRACE(msg) {std::stringstream ss; ss<<msg; flt::Log::trace(ss);}
	#endif // FLT_LOG_TRACE_LVL lvl

	#if (LOG_LVL <= FLT_LOG_DEBUG_LVL)
		#undef LOG_DEBUG
		#define LOG_DEBUG(msg) {std::stringstream ss; ss<<msg; flt::Log::debug(ss);}
	#endif // FLT_LOG_DEBUG_LVL lvl

	#if (LOG_LVL <= FLT_LOG_INFO_LVL)
		#undef LOG_INFO
		#define LOG_INFO(msg) {std::stringstream ss; ss<<msg; flt::Log::info(ss);}
	#endif // FLT_LOG_INFO_LVL lvl

	#if (LOG_LVL <= FLT_LOG_WARN_LVL)
		#undef LOG_WARN
		#define LOG_WARN(msg) {std::stringstream ss; ss<<msg; flt::Log::warn(ss);}
	#endif // FLT_LOG_WARN_LVL lvl

	#if (LOG_LVL <= FLT_LOG_ERROR_LVL)
		#undef LOG_ERROR
		#define LOG_ERROR(msg) {std::stringstream ss; ss<<msg; flt::Log::error(ss);}
	#endif // FLT_LOG_ERROR_LVL lvl

	#if (LOG_LVL <= FLT_LOG_FATAL_LVL)
		#undef LOG_FATAL
		#define LOG_FATAL(msg) {std::stringstream ss; ss<<msg; flt::Log::fatal(ss);}
	#endif // FLT_LOG_FATAL_LVL lvl

#endif // LOG_LVL

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

#undef FLT_LOG_TRACE_LVL
#undef FLT_LOG_DEBUG_LVL
#undef FLT_LOG_INFO_LVL
#undef FLT_LOG_WARN_LVL
#undef FLT_LOG_ERROR_LVL
#undef FLT_LOG_FATAL_LVL

} // namespace flt

#endif // LOG_HPP
