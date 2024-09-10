#pragma once
#include<exception>
#include<string>

class LoggerException : public std::exception {};

class NullptrStrategy : public LoggerException {
	const char* what() const noexcept override {
		return "Strategy is nullptr";
	}
};