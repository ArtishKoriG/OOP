#pragma once
#include <functional>
#include <iterator>
#include <future>
#include "Traits.h"

template<class ForwardIt, class Compare = std::less<>>
	requires (std::is_base_of_v<typename std::forward_iterator_tag,
typename std::iterator_traits<ForwardIt>::iterator_category> && have_operator_brackets<ForwardIt, Compare>)
ForwardIt minElement(ForwardIt first, ForwardIt last, Compare comp = Compare{}) {
	if (first == last) {
		return last;
	}

	ForwardIt current = first;
	ForwardIt smallest = first;
	++current;
	for (; current != last; ++current) {
		if (comp(*current, *smallest)) {
			smallest = current;
		}
	}
	return smallest;
}

template<class ForwardIt, class Compare = std::less<>>
	requires (std::is_base_of_v<typename std::forward_iterator_tag,
typename std::iterator_traits<ForwardIt>::iterator_category>&& have_operator_brackets<ForwardIt, Compare>)
ForwardIt maxElement(ForwardIt first, ForwardIt last, Compare comp = Compare{}) {
	if (first == last) {
		return last;
	}

	ForwardIt current = first;
	ForwardIt largest = first;
	++current;
	for (; current != last; ++current) {
		if (comp(*largest, *current)) {
			largest = current;
		}
	}
	return largest;
}


template< class ExecutionPolicy, class ForwardIt, class Compare>
	requires (std::is_base_of_v<typename std::forward_iterator_tag,
typename std::iterator_traits<ForwardIt>::iterator_category>&& have_operator_brackets<ForwardIt, Compare>)
ForwardIt pmin_element(ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, Compare comp) {

	if (first == last) {
		return last;
	}

	size_t size = std::distance(first, last);
	const size_t threadsCount = policy.getThreadsCount();

	if (threadsCount == 1) {
		return minElement(first, last, comp);
	}

	const size_t blockSize = (size + threadsCount + 1) / threadsCount;
	std::vector<std::future<ForwardIt>> futures(threadsCount);
	ForwardIt curFirst = first;
	ForwardIt curLast = first + blockSize;

	size_t i = 0;
	for (; i < threadsCount - 1; i++) {
		futures[i] = std::async(std::launch::async,
			[=] { return minElement<ForwardIt>(curFirst, curLast, comp); });
		curFirst = curLast;
		if (i != threadsCount - 2) {
			curLast += blockSize;
		}
	}
	futures[i] = std::async(std::launch::async,
		[=] { return minElement<ForwardIt>(curFirst, last, comp); });

	std::vector<ForwardIt> results{};

	for (size_t j = 0; j < futures.size(); ++j) {
		results.push_back(futures[j].get());
	}

	return *minElement(results.begin(), results.end(), [=](ForwardIt v1, ForwardIt v2) {return comp(*v1, *v2); });
}


template< class ExecutionPolicy, class ForwardIt >
	requires (std::is_base_of_v<typename std::forward_iterator_tag,
typename std::iterator_traits<ForwardIt>::iterator_category> && have_get_threads<ExecutionPolicy>)
ForwardIt pmin_element(ExecutionPolicy&& policy, ForwardIt first, ForwardIt last) {

	return pmin_element(policy, first, last, std::less<>{});
}

template< class ExecutionPolicy, class ForwardIt, class Compare >
	requires (std::is_base_of_v<typename std::forward_iterator_tag,
typename std::iterator_traits<ForwardIt>::iterator_category>&& have_operator_brackets<ForwardIt, Compare>)
ForwardIt pmax_element(ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, Compare comp) {

	if (first == last) {
		return last;
	}

	size_t size = std::distance(first, last);
	const size_t threadsCount = policy.getThreadsCount();

	if (threadsCount == 1) {
		return maxElement(first, last, comp);
	}

	const size_t blockSize = (size + threadsCount + 1) / threadsCount;
	std::vector<std::future<ForwardIt>> futures(threadsCount);
	ForwardIt curFirst = first;
	ForwardIt curLast = first + blockSize;

	size_t i = 0;
	for (; i < threadsCount - 1; i++) {
		futures[i] = std::async(std::launch::async,
			[curFirst, curLast] { return maxElement<ForwardIt>(curFirst, curLast); });
		curFirst = curLast;
		if (i != threadsCount - 2) {
			curLast += blockSize;
		}
	}
	futures[i] = std::async(std::launch::async,
		[curFirst, last] { return maxElement<ForwardIt>(curFirst, last); });

	std::vector<ForwardIt> results{};

	for (size_t j = 0; j < futures.size(); ++j) {
		results.push_back(futures[j].get());
	}

	return *maxElement(results.begin(), results.end(), [=](ForwardIt v1, ForwardIt v2) {return comp(*v1, *v2); });
}


template< class ExecutionPolicy, class ForwardIt >
	requires (std::is_base_of_v<typename std::forward_iterator_tag,
typename std::iterator_traits<ForwardIt>::iterator_category>&& have_get_threads<ExecutionPolicy>)
ForwardIt pmax_element(ExecutionPolicy&& policy, ForwardIt first, ForwardIt last) {
	return pmax_element(policy, first, last, std::less<>{});
}