#include "pch.h"
#include "Parser.h"

void Parser::read(std::ifstream& is) noexcept
{
	if (!is) {
		return;
	}
	std::string line{};
	while (std::getline(is, line)) {
		lines.push_back(line);
	}
}

std::vector<std::string> Parser::getLines() const noexcept
{
	return lines;
}
