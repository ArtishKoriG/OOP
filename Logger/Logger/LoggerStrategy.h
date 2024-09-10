#pragma once
#include <string>

class LoggerStrategy {
public:
	virtual ~LoggerStrategy() = default;
	virtual void write(const std::string& message) = 0;
};
