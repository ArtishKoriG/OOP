#pragma once

class SequencedPolicy final{
public:
	size_t getThreadsCount() const noexcept {
		return 1;
	}
};

