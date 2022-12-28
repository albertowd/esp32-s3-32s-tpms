#ifndef RC3_CONV_H
#define RC3_CONV_H

#include <string>

namespace RC3
{
	std::string toFixed(const double value, const unsigned short precision);
	std::string toHex(const char value);
}

#endif
