#pragma once
#include <type_traits>

template<typename T, typename U = void>
struct is_forward_iterator final : std::false_type {
};

template<typename T>
struct is_forward_iterator<T, std::enable_if_t<std::is_base_of_v<std::forward_iterator_tag, 
	typename std::iterator_traits<T>::iterator_category>>> final : std::true_type {
};

template<typename T, typename U = void>
struct is_sumable final : std::false_type {
};

template<typename T>
struct is_sumable<T, std::enable_if_t<std::is_convertible_v<decltype(std::declval<sumTraits<T>::sumT>() + std::declval<T>()),
	typename sumTraits<T>::sumT>>> final : std::true_type{
};

template<typename T, typename U = void>
struct is_container final : std::false_type {};

template<typename T>
struct is_container<T, std::enable_if_t<(is_forward_iterator<decltype(std::declval<T>().begin())>::value&&
	is_forward_iterator<decltype(std::declval<T>().end())>::value)>> final : std::true_type {
};

template<typename T, typename U = void>
struct is_container_with_sumable_type final : std::false_type {};

template<typename T>
struct is_container_with_sumable_type<T, std::enable_if_t<is_container<T>::value &&
	(is_sumable<typename std::iterator_traits<decltype(std::declval<T>().begin())>::value_type>::value 
		&& (std::is_same_v<T, std::string> == false))>> final : std::true_type {
};