#include "pch.h"
#include "Filter_iterator.h"
#include <vector>
#include <forward_list>
#include "Range_filter_iterator.h"

struct is_positive_number {
	is_positive_number() = default;
	bool operator()(int x) { return 0 < x; }

	bool operator==(const is_positive_number& other) const = default;
	bool operator!=(const is_positive_number& other) const = default;
};

struct is_even_number {
	is_even_number() = default;
	bool operator()(int x) { return x % 2 == 0; }

	bool operator==(const is_even_number& other) const = default;
	bool operator!=(const is_even_number& other) const = default;
};

class pseudo_iterator final {
public:
	pseudo_iterator(int* pointer) : ptr(pointer) {}

	int operator*() const {
		return *ptr;
	}

	int* begin() const {
		return ptr;
	}

	int* end() const {
		return ptr + 2;
	}

	pseudo_iterator& operator++() = delete;
private:
	int* ptr;
};

TEST(Constructor, WithPred1) {
	std::vector<int> arr;
	is_positive_number pred{};

	filter_iterator it(pred, arr.begin(), arr.end());
};

TEST(Constructor, WithPred2) {
	std::forward_list<int> list;
	is_even_number pred{};

	list.push_front(1);
	list.push_front(2);
	list.push_front(4);

	filter_iterator it(pred, list.begin(), list.end());
};

TEST(Constructor, WithoutPred) {
	std::vector<int> arr;

	filter_iterator<is_positive_number, std::vector<int>::iterator> it(arr.begin(), arr.end());
};

TEST(Constructor, WithFilterIterator) {
	std::vector<int> arr{ 6, 4, 3, 2, -6 };
	is_positive_number pred1{};
	is_even_number pred2{};

	RangeFilterIterator range(pred1, arr.begin(), arr.end());

	filter_iterator iterator = range.begin();
	filter_iterator iterator_end = range.end();

	RangeFilterIterator range2(pred2, iterator, iterator_end);

	filter_iterator iterator2 = range2.begin();
	filter_iterator iterator2_end = range2.end();

	size_t count = 0;
	int el = 6;
	for (auto& it = iterator2; it != iterator2_end; ++it) {
		count++;
		EXPECT_EQ(el, *it);
		el -= 2;
	};
	EXPECT_TRUE(count == 3);
}

TEST(Method, Increment) {
	std::vector<int> arr{ 6, 5, 4, 3, -6 };
	is_positive_number pred{};

	RangeFilterIterator range(pred, arr.begin(), arr.end());

	size_t count = 0;
	int el = 6;
	for (auto it = range.begin(); it != range.end(); ++it) {
		count++;
		EXPECT_EQ(el, *it);
		el -= 1;
	};
	EXPECT_TRUE(count == 4);
};

TEST(Method, Increment2) {
	std::vector<int> arr{ -2, 6, -10, 5, 4, 3, -6 };
	is_positive_number pred{};

	RangeFilterIterator range(pred, arr.begin(), arr.end());

	size_t count = 0;
	int el = 6;
	for (auto it = range.begin(); it != range.end(); ++it) {
		count++;
		EXPECT_EQ(el, *it);
		el -= 1;
	};
	EXPECT_TRUE(count == 4);
};

TEST(Range, Empty) {
	std::vector<int> arr{};
	is_positive_number pred{};

	RangeFilterIterator range(pred, arr.begin(), arr.end());
	size_t count = 0;
	for (auto it = range.begin(); it != range.end(); ++it) {
		count++;
	};
	EXPECT_TRUE(count == 0);
}

TEST(Range, WithoutTrueEl) {
	std::vector<int> arr{1, 3, 5, 9, 13};
	is_even_number pred{};

	RangeFilterIterator range(pred, arr.begin(), arr.end());
	size_t count = 0;
	for (auto it = range.begin(); it != range.end(); ++it) {
		count++;
	};
	EXPECT_TRUE(count == 0);
}
