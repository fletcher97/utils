#include <sstream>
#include <iostream>

#include "Log.hpp"
#include "Timer.hpp"

flt::Timer::Timer(std::string name) {
	this->_name = name;
	clock_gettime(CLOCK_REALTIME, &this->_start);
}

flt::Timer::~Timer() {
	this->log();
}

void
flt::Timer::log() const {
	LOG_INFO("Clock " << this->_name << " ran for " << this->get_elapsed() << " second")
}

std::string
flt::Timer::get_elapsed() const {
	timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	double elapsed = static_cast<double>(now.tv_sec - this->_start.tv_sec) + static_cast<double>(now.tv_nsec - this->_start.tv_nsec) / 1000000000;

	std::ostringstream converter;
	converter.precision(9);
	converter << std::fixed << elapsed;
	return converter.str();
}

void
flt::Timer::reset() {
	clock_gettime(CLOCK_REALTIME, &this->_start);
}
