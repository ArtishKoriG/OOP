#pragma once
#include<exception>
#include<string>

class filter_iterator_exception : public std::exception {};

class Out_of_range_exception : public filter_iterator_exception {
	const char* what() const noexcept override {
		return "Out of range position";
	}
};