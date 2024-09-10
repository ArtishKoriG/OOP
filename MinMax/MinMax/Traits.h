#pragma once
#include <concepts>


template<typename Iterator, typename Compare>
concept have_operator_brackets = requires(Iterator el1, Iterator el2, Compare comp) {
	{comp(*el1, *el2)} -> std::same_as<bool>;
};

template<typename Policy>
concept have_get_threads = requires(Policy policy, size_t size) {
	{policy.getThreadsCount()} -> std::same_as<size_t>;
};