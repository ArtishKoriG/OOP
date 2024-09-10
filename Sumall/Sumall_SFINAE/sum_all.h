#pragma once
#include <string>
#include <numeric>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <array>
#include <type_traits>
#include "sumAllTraits.h"
#include "Type_traits.h"


template <typename T, std::enable_if<!is_container_with_sumable_type<T>::value, bool>::type = false>
auto sum_all(const T & value) {
	return typename sumTraits<T>::sumT{ value };
}

template<typename T, std::enable_if<is_container_with_sumable_type<T>::value, bool>::type = false>
typename sumTraits<typename std::iterator_traits<decltype(std::declval<T>().begin())>::value_type>::sumT sum_all(const T& cont) {
	if (cont.begin() == cont.end()) {
		return sumTraits<typename std::iterator_traits<decltype(std::declval<T>().begin())>::value_type>::zero();
	}
	auto sum = sumTraits<typename std::iterator_traits<decltype(std::declval<T>().begin())>::value_type>::zero();
	for (const auto& element : cont) {
		sum += element;
	}
	return sum;
}
