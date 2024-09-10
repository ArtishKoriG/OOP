#pragma once
#include <memory>
#include "LoggerStrategy.h"
#include "LoggerExceptions.h"


class Logger final{
public:
	Logger(std::shared_ptr<LoggerStrategy> strategy) noexcept;

	void setStrategy(std::shared_ptr<LoggerStrategy> strategy);
	void logMessage(const std::string& message) const;
private:
	std::shared_ptr<LoggerStrategy> strategy;
};