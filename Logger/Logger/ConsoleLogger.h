#pragma once
#include <iostream>
#include "LoggerStrategy.h"

class ConsoleLogger final : public LoggerStrategy{
public:
	void write(const std::string& message) override;
};