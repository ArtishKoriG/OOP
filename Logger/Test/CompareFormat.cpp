#include "pch.h"
#include "CompareFormat.h"

bool compareFormat(const std::string& line) noexcept
{
	std::vector<std::string> words = getWords(line, ' ');

	const std::string date1 = "11-11-2023";
	const std::string date2 = "11:11:23";

	if (date1.size() != words[0].size() && date2.size() != words[1].size()) {
		return false;
	}
	if ((words[0][2] != date1[2] && date1[2] != words[0][5]) && (words[1][2] != date2[2] && date2[2] != words[1][5])) {
		return false;
	}
	std::vector<std::string> date1Words = getWords(words[0], '-');
	std::vector<std::string> date2Words = getWords(words[1], ':');
	if (std::stoi(date1Words[0]) < 1 && std::stoi(date1Words[0]) > 12) {
		return false;
	}
	if (std::stoi(date1Words[1]) < 1 && std::stoi(date1Words[1]) > 31) {
		return false;
	}
	if (checkTime(date2Words[0]) && checkTime(date2Words[1])) {
		return false;
	}
	return true;
}

bool checkTime(const std::string& time) noexcept
{
	return std::stoi(time) < 1 && std::stoi(time) > 60;
}
