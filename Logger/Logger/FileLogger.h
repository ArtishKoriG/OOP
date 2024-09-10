#pragma once
#include <fstream>
#include "LoggerStrategy.h"


class FileLogger : public LoggerStrategy
{
public:
	FileLogger(const std::string& filename);
	virtual ~FileLogger() = default;

	void write(const std::string& message) override;
protected:
	std::ofstream os;
};

