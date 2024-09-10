#include "pch.h"
#include <forward_list>
#include "pminmax.h"
#include "SequencedPolicy.h"
#include "OwnQuantityPolicy.h"
#include "PerfectQuantityPolicy.h"
#include "Comparator.h"

TEST(Simple, MinEmpty) {
	std::vector<int> v{};

	std::vector<int>::iterator result = minElement(v.begin(), v.end());

	EXPECT_EQ(result, v.begin());
}

TEST(Simple, MinOneElement) {
	std::vector<int> v{ 1 };

	std::vector<int>::iterator result = minElement(v.begin(), v.end());

	EXPECT_EQ(*result, 1);
}

TEST(Simple, Min1) {
	std::forward_list<double> list{ 1.0, -19.5, 10.7 };

	std::forward_list<double>::iterator result = minElement(list.begin(), list.end());

	EXPECT_EQ(*result, -19.5);
}

TEST(Simple, Min2) {
	std::forward_list<double> list{ -19.5, 10.7, 101.03 };

	std::forward_list<double>::iterator result = minElement(list.begin(), list.end());

	EXPECT_EQ(*result, -19.5);
}

TEST(Simple, Min3) {
	std::vector<int> v{ 12, 32, 1 };

	std::vector<int>::iterator result = minElement(v.begin(), v.end());

	EXPECT_EQ(*result, 1);
}

TEST(Simple, MaxEmpty) {
	std::vector<int> v{};

	std::vector<int>::iterator result = maxElement(v.begin(), v.end());

	EXPECT_EQ(result, v.begin());
}

TEST(Simple, MaxOneElement) {
	std::vector<int> v{ 1 };

	std::vector<int>::iterator result = maxElement(v.begin(), v.end());

	EXPECT_EQ(*result, 1);
}

TEST(Simple, Max1) {
	std::forward_list<double> list{ 1.0, -19.5, 10.7 };

	std::forward_list<double>::iterator result = maxElement(list.begin(), list.end());

	EXPECT_EQ(*result, 10.7);
}

TEST(Simple, Max2) {
	std::forward_list<double> list{ -19.5, 101.03, 10.7,};

	std::forward_list<double>::iterator result = maxElement(list.begin(), list.end());

	EXPECT_EQ(*result, 101.03);
}

TEST(Simple, Max3) {
	std::vector<int> v{ 120, 32, 1 };

	std::vector<int>::iterator result = maxElement(v.begin(), v.end());

	EXPECT_EQ(*result, 120);
}

TEST(Seq, Min1) {
	std::vector<int> v{};
	for (int i = 0; i < 100; i++) {
		v.push_back(i);
	}
	v[0] = -10;

	SequencedPolicy seq{};

	std::vector<int>::iterator result = pmin_element(seq, v.begin(), v.end());

	EXPECT_EQ(*result, -10);
}

TEST(Seq, Min2) {
	std::vector<int> v(100, 2);
	v[51] = -10;

	SequencedPolicy seq{};

	std::vector<int>::iterator result = pmin_element(seq, v.begin(), v.end());

	EXPECT_EQ(*result, -10);
}

TEST(Seq, Min3) {
	std::vector<int> v(100, 2);
	v[98] = -10;

	SequencedPolicy seq{};

	std::vector<int>::iterator result = pmin_element(seq, v.begin(), v.end());

	EXPECT_EQ(*result, -10);
}

TEST(Seq, Max1) {
	std::vector<int> v{};
	for (int i = 0; i < 100; i++) {
		v.push_back(i);
	}
	v[0] = 200;

	SequencedPolicy seq{};

	std::vector<int>::iterator result = pmax_element(seq, v.begin(), v.end());

	EXPECT_EQ(*result, 200);
}

TEST(Seq, Max2) {
	std::vector<int> v(100, 2);
	v[51] = 10;

	SequencedPolicy seq{};

	std::vector<int>::iterator result = pmax_element(seq, v.begin(), v.end());

	EXPECT_EQ(*result, 10);
}

TEST(Seq, Max3) {
	std::vector<int> v(100, 2);
	v[98] = 10;

	SequencedPolicy seq{};

	std::vector<int>::iterator result = pmax_element(seq, v.begin(), v.end());

	EXPECT_EQ(*result, 10);
}

TEST(OwnQuantity, Min1) {
	std::vector<int> v{};
	for (int i = 0; i < 100; i++) {
		v.push_back(i);
	}
	v[0] = -10;

	OwnQuantityPolicy policy(2);

	std::vector<int>::iterator result = pmin_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, -10);
}

TEST(OwnQuantity, Min2) {
	std::vector<int> v(100, 2);
	v[51] = -10;

	OwnQuantityPolicy policy(2);

	std::vector<int>::iterator result = pmin_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, -10);
}

TEST(OwnQuantity, Min3) {
	std::vector<int> v(100, 2);
	v[98] = -10;

	OwnQuantityPolicy policy(2);

	std::vector<int>::iterator result = pmin_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, -10);
}

TEST(OwnQuantity, Max1) {
	std::vector<int> v{};
	for (int i = 0; i < 100; i++) {
		v.push_back(i);
	}
	v[0] = 200;

	OwnQuantityPolicy policy(5);

	std::vector<int>::iterator result = pmax_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, 200);
}

TEST(OwnQuantity, Max2) {
	std::vector<int> v(100, 2);
	v[51] = 10;

	OwnQuantityPolicy policy(2);

	std::vector<int>::iterator result = pmax_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, 10);
}

TEST(OwnQuantity, Max3) {
	std::vector<int> v(100, 2);
	v[98] = 10;

	OwnQuantityPolicy policy(2);

	std::vector<int>::iterator result = pmax_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, 10);
}

TEST(PerfectQuantity, Min1) {
	std::vector<int> v{};
	for (int i = 0; i < 100; i++) {
		v.push_back(i);
	}
	v[0] = -10;

	PerfectQuantityPolicy policy(std::distance(v.begin(), v.end()));

	std::vector<int>::iterator result = pmin_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, -10);
}

TEST(PerfectQuantity, Min2) {
	std::vector<int> v(100, 2);
	v[51] = -10;

	PerfectQuantityPolicy policy(std::distance(v.begin(), v.end()));

	std::vector<int>::iterator result = pmin_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, -10);
}

TEST(PerfectQuantity, Min3) {
	std::vector<int> v(100, 2);
	v[98] = -10;

	PerfectQuantityPolicy policy(std::distance(v.begin(), v.end()));

	std::vector<int>::iterator result = pmin_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, -10);
}

TEST(PerfectQuantity, Max1) {
	std::vector<int> v{};
	for (int i = 0; i < 100; i++) {
		v.push_back(i);
	}
	v[0] = 200;

	PerfectQuantityPolicy policy(std::distance(v.begin(), v.end()));

	std::vector<int>::iterator result = pmax_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, 200);
}

TEST(PerfectQuantity, Max2) {
	std::vector<int> v(100, 2);
	v[51] = 10;

	PerfectQuantityPolicy policy(std::distance(v.begin(), v.end()));

	std::vector<int>::iterator result = pmax_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, 10);
}

TEST(PerfectQuantity, Max3) {
	std::vector<int> v(100, 2);
	v[98] = 10;

	PerfectQuantityPolicy policy(std::distance(v.begin(), v.end()));

	std::vector<int>::iterator result = pmax_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, 10);
}

TEST(Compare, Seq) {
	std::vector<int> v(100, 2);
	v[98] = 10;

	Comparator<int> comp{};

	SequencedPolicy policy{};

	std::vector<int>::iterator result = pmax_element(policy, v.begin(), v.end(), comp);

	EXPECT_EQ(*result, 10);
}

TEST(Compare, Own) {
	std::vector<int> v(100, 2);
	v[98] = -10;

	Comparator<int> comp{};

	OwnQuantityPolicy policy(0);

	std::vector<int>::iterator result = pmin_element(policy, v.begin(), v.end(), comp);

	EXPECT_EQ(*result, -10);
}

TEST(Compare, Perfect) {
	std::vector<int> v(100, 2);
	v[98] = 10;

	Comparator<int> comp{};

	PerfectQuantityPolicy policy(std::distance(v.begin(), v.end()));

	std::vector<int>::iterator result = pmax_element(policy, v.begin(), v.end(), comp);

	EXPECT_EQ(*result, 10);
}

TEST(MinChunck, Seq) {
	std::vector<int> v(50000000, 2);
	v[98] = 10;

	SequencedPolicy policy{};

	std::vector<int>::iterator result = pmax_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, 10);
}

TEST(MinChunck, Own) {
	std::vector<int> v(50000000, 2);
	v[98] = 10;

	OwnQuantityPolicy policy(2);

	std::vector<int>::iterator result = pmax_element(policy, v.begin(), v.end());

	EXPECT_EQ(*result, 10);
}