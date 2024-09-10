#pragma once
#include <type_traits>

template<typename Predicate, typename It>
struct have_operator_breckets final {
    static constexpr bool value = std::is_same_v<decltype(std::declval<Predicate>()(*std::declval<It>())), bool>;
};

template<typename Predicate>
struct have_operator_equal final {
    static constexpr bool value = std::is_same_v<decltype(std::declval<Predicate>() == std::declval<Predicate>()), bool>;
};

template<typename It>
struct have_increment final{
    static constexpr bool value = std::is_same_v<decltype(std::declval<It>()++), It>&&
        std::is_same_v<decltype(++std::declval<It>()), It&>;
};

template<typename It>
struct have_dereference final{
    static constexpr bool value = std::is_same_v<decltype(*std::declval<It>()), std::iterator_traits<It>::reference>;
};

template<typename It>
struct iterable_and_dereferenced final{
    static constexpr bool value = have_increment<It>::value && have_dereference<It>::value;
};

template<typename Iterator, typename Predicate>
struct is_default_constructable_and_no_function final{
    static constexpr bool value = std::is_default_constructible_v<Predicate> && std::is_default_constructible_v<Iterator>
        && !std::is_function_v<Predicate>;
};