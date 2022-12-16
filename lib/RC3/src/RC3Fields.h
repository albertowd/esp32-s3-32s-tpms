#ifndef RC3_FIELDS_H
#define RC3_FIELDS_H

#include <math.h>
#include <string>
#include <vector>

namespace RC3 {
	enum AnalogIndexes {
		A1 = 10,
		A2,
		A3,
		A4,
		A5,
		A6,
		A7,
		A8,
		A9,
		A10,
		A11,
		A12,
		A13,
		A14,
		A15,
	};

	enum DigitalIndexes {
		D1_RPM = 8,
		D2
	};

	struct Field {
		const std::string name;
		const double max;
		const double min;
		const unsigned short precision;
	};

	const static std::vector<Field> FIELDS = {
		// Timestamp field should be empty, if your device doesn't have GPS and does not output NMEA 0183 sentences mixed with the $RCx sentences
		{ "time", NAN, NAN, 0 },
		// Count is an overflowing line counter 0-65535, field is empty when mixed output with NMEA 0183 sentences
		{ "count", 65535.0, 0.0, 0 },
		// acc fields: -1.000 = -1G, 1.000 = +1G
		{ "xacc", NAN, NAN, 3 },
		{ "yacc", NAN, NAN, 3 },
		{ "zacc", NAN, NAN, 3 },
		// gyro fields: degrees per second, -1.000 = -1 deg/s, 1.000 = +1 deg/s
		{ "gyrox", NAN, NAN, 3 },
		{ "gyroy", NAN, NAN, 3 },
		{ "gyroz", NAN, NAN, 3 },
		// RPM/digital channel fields, range -2000000.000 to 2000000.000
		{ "d1/RPM", 2000000.0, -2000000.0, 3 },
		{ "d2", 2000000.0, -2000000.0, 3 },
		// analog channel fields, range -2000000.000 to 2000000.000
		{ "a1", 2000000.0, -2000000.0, 3 },
		{ "a2", 2000000.0, -2000000.0, 3 },
		{ "a3", 2000000.0, -2000000.0, 3 },
		{ "a4", 2000000.0, -2000000.0, 3 },
		{ "a5", 2000000.0, -2000000.0, 3 },
		{ "a6", 2000000.0, -2000000.0, 3 },
		{ "a7", 2000000.0, -2000000.0, 3 },
		{ "a8", 2000000.0, -2000000.0, 3 },
		{ "a9", 2000000.0, -2000000.0, 3 },
		{ "a10", 2000000.0, -2000000.0, 3 },
		{ "a11", 2000000.0, -2000000.0, 3 },
		{ "a12", 2000000.0, -2000000.0, 3 },
		{ "a13", 2000000.0, -2000000.0, 3 },
		{ "a14", 2000000.0, -2000000.0, 3 },
		{ "a15", 2000000.0, -2000000.0, 3 }
	};
};

#endif
