#pragma once
#include <cmath>
#include <thread>

class PerfectQuantityPolicy final {
public:
	PerfectQuantityPolicy(const size_t& size) : size(size) {}

	size_t getThreadsCount() const noexcept{
		const size_t minChunkSize = 1000000;
		size_t const maxThreads = (size / minChunkSize) + 1;
		size_t const threadCounts = std::min(maxThreads, std::max<size_t>(1, std::thread::hardware_concurrency()));
		return threadCounts;
	}
private:
	size_t size;
};