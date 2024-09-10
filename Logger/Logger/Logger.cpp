#include "Logger.h"

Logger::Logger(std::shared_ptr<LoggerStrategy> strategy) noexcept : strategy(strategy)
{
}

void Logger::setStrategy(std::shared_ptr<LoggerStrategy> strategy)
{
	this->strategy = strategy;
}

void Logger::logMessage(const std::string& message) const
{
	if (!strategy) {
		return;
	}
	strategy->write(message);
}


