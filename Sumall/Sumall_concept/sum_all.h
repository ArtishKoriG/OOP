#pragma once
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <array>
#include <string>
#include <numeric>
#include <type_traits>
#include <iterator>
#include <functional>
#include <algorithm>
#include "sumAllTraits.h"

template<typename T>
using containerValueType = typename std::iterator_traits<decltype(std::declval<T>().begin())>::value_type;

template<typename T>
concept is_sumable = requires(T val1, typename sumTraits<T>::sumT val2) {
	val2 + val1;
	{val2 + val1} -> std::same_as<typename sumTraits<T>::sumT>;
};

template<typename T>
concept is_container_with_sumable_type = (
	(is_sumable<containerValueType<T>> && !std::is_same_v<T, std::string>)) && requires(T val) {
	typename containerValueType<T>;
	{val.begin()} -> std::forward_iterator;
	{val.end()} -> std::forward_iterator;
};

template<typename T>
	requires (!is_container_with_sumable_type<T>)
auto sum_all(const T& value) {
	return typename sumTraits<T>::sumT{ value };
}

template<typename T>
	requires is_container_with_sumable_type<T>
typename sumTraits<containerValueType<T>>::sumT sum_all(const T& cont) {
	if (cont.empty()) {
		return sumTraits<containerValueType<T>>::zero();
	}
	auto sum = sumTraits<containerValueType<T>>::zero();
	for (const auto& element : cont) {
		sum = sum + element;
	}
	return sum;
}