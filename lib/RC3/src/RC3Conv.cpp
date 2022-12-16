#include "RC3Conv.h"

#include <iomanip>
#include <sstream>

std::string RC3::toFixed(const double value, const unsigned short precision) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << value;
	return stream.str();
}

std::string RC3::toHex(const char value) {
	std::stringstream stream;
	stream << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (int)value;
	return stream.str();
}
