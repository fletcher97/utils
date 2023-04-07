#if !defined(TIMER_HPP)
#define TIMER_HPP

#include <string>

namespace flt
{

#define FLT_TIME(name)
#define FLT_TIME_RESET
#define FLT_TIME_LOG
#define FLT_TIME_GET

#if defined(FLT_TIMER)

	#undef FLT_TIME
	#define FLT_TIME(name) flt::Timer flt_timer = flt::Timer(name);

	#undef FLT_TIME_LOG
	#define FLT_TIME_LOG flt_timer.log();

	#undef FLT_TIME_GET
	#define FLT_TIME_GET flt_timer.get_elapsed();

	#undef FLT_TIME_RESET
	#define FLT_TIME_RESET flt_timer.reset();

#endif // FLT_TIMER


class Timer
{
private:
	std::string _name;
	timespec _start;
public:
	Timer(std::string name);
	~Timer();

	void log() const;
	std::string get_elapsed() const;

	void reset();
};

} // namespace flt


#endif // TIMER_HPP
