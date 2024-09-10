#pragma once

class OwnQuantityPolicy final{
public:
	OwnQuantityPolicy(const size_t& count) noexcept : count(count) {
		if (count == 0) {
			this->count = 1;
		}
	}

	size_t getThreadsCount() const noexcept{
		return count;
	}
private:
	size_t count;
};