#ifndef RC3_H
#define RC3_H

#include <string>
#include <vector>

#include "RC3Fields.h"

namespace RC3 {
	class Entry
	{
	private:
		static unsigned short idCounter;
		std::vector<double> values;

	public:
		Entry();
		Entry(const std::vector<double>& values);
		Entry(const Entry& copy);
		~Entry();

		static char checkSum(const std::string buffer);
		static unsigned short incrementId();

		bool validate() const;
		std::string pack() const;
		void setAnalog(const RC3::AnalogIndexes index, const double value);
		void setDigital(const RC3::DigitalIndexes index, const double value);
		void clear();
		void updateId();
	};
}

#endif
