#pragma once


template<typename T>
class Comparator final {
public:
	bool operator()(T el1, T el2) const noexcept {
		return el1 - el2 < 0;
	}
private:
};