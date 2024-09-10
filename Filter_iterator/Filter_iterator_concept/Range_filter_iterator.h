#pragma once
#include "traits.h"

template<class Predicate, class Iterator>
	requires (iterable_and_dereferenced<Iterator>&& have_operator_breckets<Predicate, Iterator>&& have_operator_equal<Predicate>)
class RangeFilterIterator final {
public:
	RangeFilterIterator(Predicate pred, Iterator begin, Iterator end) : pred(pred), begin_(begin), end_(end) {}

	filter_iterator<Predicate, Iterator> begin() const {
		filter_iterator<Predicate, Iterator> it(pred, begin_, end_);
		return it;
	}

	filter_iterator<Predicate, Iterator> end() const {
		filter_iterator<Predicate, Iterator> it(pred, end_, end_);
		return it;
	}

	filter_iterator<Predicate, Iterator> begin() {
		filter_iterator<Predicate, Iterator> it(pred, begin_, end_);
		return it;
	}

	filter_iterator<Predicate, Iterator> end() {
		filter_iterator<Predicate, Iterator> it(pred, end_, end_);
		return it;
	}
private:
	Predicate pred;
	Iterator begin_;
	Iterator end_;
};