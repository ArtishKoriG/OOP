#pragma once
#include <fstream>
#include <ctime>
#include <string>
#include "LoggerStrategy.h"
#include "FileLogger.h"

class TimedFileLogger final : public FileLogger
{
public:
	TimedFileLogger(const std::string& filename);

	void write(const std::string& message) override;
protected:
	
	std::string getTime() const;
};

