#include <iostream>

#include "Log.hpp"

std::ofstream flt::Log::fout;

void
flt::Log::openFile(const std::string& path) {
	if (flt::Log::fout.is_open()) {
		LOG_INFO("Changing log files to " << path)
		flt::Log::fout.close();
	}

	flt::Log::fout.open(path.c_str(), std::ios::out | std::ios::app);
	if (!flt::Log::fout.is_open()) {
		LOG_ERROR("Failed to open file.")
	}
}

void
flt::Log::closeFile(void) {
	if (flt::Log::fout.is_open())
		flt::Log::fout.close();
}

void
flt::Log::trace(const std::stringstream& msg) {
	std::clog << TRACE_COLOR_FG << "[TRACE]" << RESET_COLOR << ": " <<
		msg.str() << RESET_COLOR << std::endl;
	if (flt::Log::fout.is_open()) {
		flt::Log::fout << "[TRACE]: " << msg.str() << std::endl;
		flt::Log::fout.flush();
	}

}

void
flt::Log::debug(const std::stringstream& msg) {
	std::clog << DEBUG_COLOR_FG << "[DEBUG]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
	if (flt::Log::fout.is_open()) {
		flt::Log::fout << "[DEBUG]: " << msg.str() << std::endl;
		flt::Log::fout.flush();
	}
}

void
flt::Log::info(const std::stringstream& msg) {
	std::clog << INFO_COLOR_FG << "[INFO]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
	if (flt::Log::fout.is_open()) {
		flt::Log::fout << "[INFO]: " << msg.str() << std::endl;
		flt::Log::fout.flush();
	}
}

void
flt::Log::warn(const std::stringstream& msg) {
	std::clog << WARN_COLOR_FG << "[WARN]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
	if (flt::Log::fout.is_open()) {
		flt::Log::fout << "[WARN]: " << msg.str() << std::endl;
		flt::Log::fout.flush();
	}
}

void
flt::Log::error(const std::stringstream& msg) {
	std::clog << ERROR_COLOR_FG << "[ERROR]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
	if (flt::Log::fout.is_open()) {
		flt::Log::fout << "[ERROR]: " << msg.str() << std::endl;
		flt::Log::fout.flush();
	}
}

void
flt::Log::fatal(const std::stringstream& msg) {
	std::clog << FATAL_COLOR_FG << "[FATAL]" << RESET_COLOR << ": " <<
		msg.str()  << RESET_COLOR << std::endl;
	if (flt::Log::fout.is_open()) {
		flt::Log::fout << "[FATAL]: " << msg.str() << std::endl;
		flt::Log::fout.flush();
	}
}
