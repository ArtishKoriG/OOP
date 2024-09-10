#pragma once
#include "Traits.h"

template<class Predicate, class Iterator, class T = void>
class RangeFilterIterator final {
	RangeFilterIterator() = delete;
};

template<class Predicate, class Iterator>
class RangeFilterIterator<Predicate, Iterator, typename std::enable_if<have_operator_breckets<Predicate, Iterator>::value
	&& have_operator_equal<Predicate>::value&& iterable_and_dereferenced<Iterator>::value>::type> final {
public:
	template<typename U1 = Predicate, typename U2 = Iterator>
	RangeFilterIterator(Predicate pred, Iterator begin, Iterator end, std::enable_if_t < std::is_default_constructible_v<U1>&& std::is_default_constructible_v<U2>
		&& !std::is_function_v<U1>, bool> = false) : pred(pred), begin_(begin), end_(end) {}

	filter_iterator<Predicate, Iterator> begin() const {
		filter_iterator<Predicate, Iterator> it(pred, begin_, end_);
		return it;
	}

	filter_iterator<Predicate, Iterator> end() const {
		filter_iterator<Predicate, Iterator> it(pred, end_, end_);
		return it;
	}
private:
	Predicate pred;
	Iterator begin_;
	Iterator end_;
};