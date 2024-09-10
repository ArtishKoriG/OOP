#pragma once
#include <string>

template <typename T>
class sumTraits {
public:
	using sumT = T;
	static sumT zero() { return T{}; }
};

template<>
class sumTraits<char> {
public:
	using sumT = std::string;
	static sumT zero() { return ""; }
};

template<>
class sumTraits<unsigned char> {
public:
	using sumT = unsigned int;
	static sumT zero() { return 0; }
};

template<>
class sumTraits<std::string> {
public:
	using sumT = std::string;
	static sumT zero() { return ""; }
};

template<>
class sumTraits<int> {
public:
	using sumT = long;
	static sumT zero() { return 0; }
};

template<>
class sumTraits<unsigned int> {
public:
	using sumT = unsigned long long;
	static sumT zero() { return 0; }
};

template<>
class sumTraits<short> {
public:
	using sumT = int;
	static sumT zero() { return 0; }
};

template<>
class sumTraits<unsigned short> {
public:
	using sumT = unsigned int;
	static sumT zero() { return 0; }
};

template<>
class sumTraits<float> {
public:
	using sumT = double;
	static sumT zero() { return 0.0; }
};

template<>
class sumTraits<double> {
public:
	using sumT = long double;
	static sumT zero() { return 0.0; }
};