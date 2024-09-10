#pragma once
#include <type_traits>

template<typename T, typename It>
concept have_operator_breckets = requires (T pred, It it) {
    {pred(*it)} -> std::same_as<bool>;
};

template<typename Predicate>
concept have_operator_equal = requires(Predicate pred1, Predicate pred2) {
    {pred1 == pred2} -> std::same_as<bool>;
};

template<typename It>
concept have_increment = requires(It it) {
    it++;
    ++it;
    {it++} -> std::same_as<It>;
};

template<typename It>
concept have_dereference = requires(It it) {
    *it;
};

template<typename It>
concept iterable_and_dereferenced = (have_increment<It> && have_dereference<It>);

template<typename Iterator, typename Predicate>
concept is_default_constructable_and_no_function = std::is_default_constructible_v<Predicate> && std::is_default_constructible_v<Iterator>
    && !std::is_function_v<Predicate>;
