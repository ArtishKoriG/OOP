#define _CRT_SECURE_NO_WARNINGS
#include "TimedFileLogger.h"

TimedFileLogger::TimedFileLogger(const std::string& filename) : FileLogger(filename)
{
}

void TimedFileLogger::write(const std::string& message)
{
	os << getTime() << " " << message << std::endl;
}

std::string TimedFileLogger::getTime() const
{

	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);

	char buffer[128];
	strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", now);
	return buffer;
}
