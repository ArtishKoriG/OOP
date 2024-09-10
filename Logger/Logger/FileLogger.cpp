#include "FileLogger.h"

FileLogger::FileLogger(const std::string& filename)
{
	os.open(filename);
}

void FileLogger::write(const std::string& message)
{
	os << message << std::endl;
}


