#pragma once
#include <vector>
#include <string>
#include <fstream>


class Parser final {
public:
	Parser() noexcept = default;

	void read(std::ifstream& is) noexcept;

	std::vector<std::string> getLines() const noexcept;
private:
	std::vector<std::string> lines;
};