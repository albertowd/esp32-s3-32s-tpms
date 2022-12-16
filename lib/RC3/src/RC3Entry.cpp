#include "RC3Entry.h"

#include <math.h>
#include <iostream>

#include "RC3Conv.h"

unsigned short RC3::Entry::idCounter(1);

RC3::Entry::Entry(const std::vector<double>& values) : values(values) {
	this->values.at(1) = RC3::Entry::incrementId();
}

RC3::Entry::Entry() : values(RC3::FIELDS.size(), NAN) {
	this->values.at(1) = RC3::Entry::incrementId();
}

RC3::Entry::Entry(const Entry& copy) : RC3::Entry::Entry(copy.values) {}

RC3::Entry::~Entry() {
	this->values.clear();
}

bool RC3::Entry::validate() const {
	std::string errors;
	for (size_t index(0); index < this->values.size(); index++) {
		const double value(this->values.at(index));
		if (!isnan(value)) {
			const Field field(RC3::FIELDS.at(index));
			if (!isnan(field.max) && value > field.max) {
				errors.append(field.name).append(" above maximum value: ").append(std::to_string(value)).append(" > ").append(std::to_string(field.max)).append("\n");
			}
			else if (!isnan(field.min) && value < field.min) {
				errors.append(field.name).append(" bellow minimun value: ").append(std::to_string(value)).append(" < ").append(std::to_string(field.min)).append("\n");
			}
		}
	}

	if (0 < errors.length()) {
		std::cout << "Erros validating entry : \n" << errors << std::endl;
		return false;
	}
	else {
		return true;
	}
}

char RC3::Entry::checkSum(const std::string buffer) {
	char sum(0);
	for (const char byte : buffer) {
		sum ^= byte;
	}
	return sum;
}

std::string RC3::Entry::pack() const {
	std::string package;
	if (this->validate()) {
		package += "RC3,";
		for (size_t index(0); index < this->values.size(); index++) {
			const double value(this->values.at(index));
			if (!isnan(value)) {
				const RC3::Field field(RC3::FIELDS.at(index));
				package += RC3::toFixed(value, field.precision);
			}
			package += ",";
		}
		package.pop_back();
		package += '*' + RC3::toHex(RC3::Entry::checkSum(package)) + "\r\n";
	}
	package.insert(package.begin(), '$');
	return package;
}

unsigned short RC3::Entry::incrementId() {
	const unsigned short newId(RC3::Entry::idCounter++);
	if (0 == RC3::Entry::idCounter) {
		RC3::Entry::idCounter++;
	}
	return newId;
}

void RC3::Entry::setAnalog(const RC3::AnalogIndexes index, const double value) {
	this->values.at(index) = value;
}

void RC3::Entry::setDigital(const RC3::DigitalIndexes index, const double value) {
	this->values.at(index) = value;
}

void RC3::Entry::clear() {
	for (size_t index(2); index < this->values.size(); index++) {
		this->values.at(index) = NAN;
	}
}

void RC3::Entry::updateId() {
	this->values.at(1) = RC3::Entry::incrementId();
}
