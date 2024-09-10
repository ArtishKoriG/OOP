#pragma once
#include<exception>
#include<string>

class SharedPtrExceptions : public std::exception {};

class NullptrDereference : public SharedPtrExceptions {
	const char* what() const noexcept override {
		return "Nullptr dereferense";
	}
};