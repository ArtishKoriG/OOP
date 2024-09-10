#pragma once
#include <iterator>
#include <type_traits>
#include <algorithm>
#include "filter_iterator_exceptions.h"
#include "traits.h"


template <class Predicate, class Iterator>
    requires (iterable_and_dereferenced<Iterator>&& have_operator_breckets<Predicate, Iterator>&& have_operator_equal<Predicate>)
class filter_iterator final
{
public:
    using value_type = std::iterator_traits<Iterator>::value_type;
    using reference = std::iterator_traits<Iterator>::reference;
    using pointer = std::iterator_traits<Iterator>::pointer;
    using difference_type = std::iterator_traits<Iterator>::difference_type;
    using iterator_category = std::forward_iterator_tag;

    filter_iterator() requires is_default_constructable_and_no_function<Iterator, Predicate> = default;

    filter_iterator(Predicate f, Iterator x, Iterator end = Iterator()) : m_pred(f), m_iter(x), m_end(end) {
        m_iter = std::find_if(m_iter, m_end, m_pred);
    }

    filter_iterator(Iterator x, Iterator end = Iterator()) requires is_default_constructable_and_no_function<Iterator, Predicate> : m_iter(x), m_end(end) {
        m_iter = std::find_if(m_iter, m_end, m_pred);
    }

    Predicate predicate() const {
        return m_pred;
    }

    Iterator end() const {
        return m_end;
    }

    Iterator const& base() const {
        return m_iter;
    }

    reference operator*() const {
        if (m_iter == m_end) {
            throw Out_of_range_exception();
        }
        return *m_iter;
    }

    pointer operator->() const {
        if (m_iter == m_end) {
            throw Out_of_range_exception();
        }
        return m_iter.operator->();
    }

    filter_iterator& operator++() {
        if (m_iter == m_end) {
            throw Out_of_range_exception();
        }
        ++m_iter;
        m_iter = std::find_if(m_iter, m_end, m_pred);
        return *this;
    }

    filter_iterator operator++(int) {
        filter_iterator res = *this;
        ++*this;
        return res;
    }

    bool operator!=(const filter_iterator& other) const {
        return !(*this == other);
    }

    bool operator== (const filter_iterator& other) const {
        return m_iter == other.m_iter && m_end == other.m_end && m_pred == other.m_pred;
    }

private:
    Predicate m_pred;
    Iterator m_iter;
    Iterator m_end;
};

