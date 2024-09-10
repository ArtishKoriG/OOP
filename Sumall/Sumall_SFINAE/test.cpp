#include "pch.h"
#include "sum_all.h"

class TestClass final {
public:
	TestClass() = default;
	TestClass(const std::vector<int>& v) {
		data = v;
	}

	auto begin() const noexcept { return data.begin(); }
	auto end() const noexcept { return data.end(); }

	bool empty() const noexcept {
		return data.size() == 0;
	}
private:
	std::vector<int> data;
};

class TestType final {
public:
	TestType(const int& num) : data(num) {}

	int operator+(TestType other) const {
		return data + other.data;
	}

	bool operator==(TestType other) const {
		return data == other.data;
	}
private:
	int data;
};


TEST(Class, Cont) {
	std::vector<int> v = { 1, 2, 3 };
	TestClass con(v);

	EXPECT_EQ(6, sum_all(con));
}

TEST(Class, Type) {
	TestType num1(1);
	TestType num2(2);
	std::vector<TestType> v = { num1, num2};

	TestType resSum(3);

	EXPECT_EQ(resSum, sum_all(v));
}

TEST(simple, Int) {
	{
		int num1 = 0;
		EXPECT_EQ(0, sum_all(num1));
	}
	{
		int num2 = 1;
		EXPECT_EQ(1, sum_all(num2));
	}
	{
		int num3 = -1;
		EXPECT_EQ(-1, sum_all(num3));
	}
}

TEST(simple, Short) {
	{
		short num1 = 0;
		EXPECT_EQ(0, sum_all(num1));
	}
	{
		short num2 = 1;
		EXPECT_EQ(1, sum_all(num2));
	}
	{
		short num3 = -1;
		EXPECT_EQ(-1, sum_all(num3));
	}
}

TEST(simple, Float) {
	{
		float num1 = 0.0;
		EXPECT_EQ(0.0, sum_all(num1));
	}
	{
		float num2 = 1.0;
		EXPECT_EQ(1.0, sum_all(num2));
	}
	{
		float num3 = -1.0;
		EXPECT_EQ(-1.0, sum_all(num3));
	}
}

TEST(simple, String) {
	std::string str1 = "ab";
	EXPECT_EQ("ab", sum_all(str1));
}

TEST(Vector, Int) {
	{
		std::vector<int> v0 = {};
		EXPECT_TRUE(0 == sum_all(v0));
	}
	{
		std::vector<int> v1 = { 1 };
		EXPECT_EQ(1, sum_all(v1));
	}
	{
		std::vector<int> v2 = { 1, 3 };
		EXPECT_EQ(4, sum_all(v2));
	}
	{
		std::vector<int> v3 = { -1, 3 };
		EXPECT_EQ(2, sum_all(v3));
	}
	{
		std::vector<int> v4 = { -1, -3 };
		EXPECT_EQ(-4, sum_all(v4));
	}
	{
		std::vector<unsigned int> v5 = {};
		EXPECT_EQ(0, sum_all(v5));
	}
	{
		std::vector<unsigned int> v6 = { 1 };
		EXPECT_EQ(1, sum_all(v6));
	}
	{
		std::vector<unsigned int> v7 = { 1, 3 };
		EXPECT_EQ(4, sum_all(v7));
	}
}

TEST(List, Float) {

	const double epsilon = 0.00001;
	{
		std::list<float> list0{};
		EXPECT_EQ(0.0, sum_all(list0));
	}
	{
		std::list<float> list1 = { 1.0 };
		EXPECT_EQ(1.0, sum_all(list1));
	}
	{
		std::list<float> list2 = { 1.0, 5.4 };
		EXPECT_TRUE(abs(6.4 - sum_all(list2)) < epsilon);
	}
	{
		std::list<float> list3 = { 1.0, -5.4 };
		EXPECT_TRUE(abs(-4.4 - sum_all(list3)) < epsilon);
	}
}

TEST(F_List, String) {
	{
		std::forward_list<std::string> f_list0 = {};
		EXPECT_EQ("", sum_all(f_list0));
	}
	{
		std::forward_list<std::string> f_list1 = { "ab" };
		EXPECT_EQ("ab", sum_all(f_list1));
	}
	{
		std::forward_list<std::string> f_list2 = { "ab", "ba" };
		EXPECT_EQ("abba", sum_all(f_list2));
	}
	{
		std::forward_list<std::string> f_list3 = { "ab", "Ba" };
		EXPECT_EQ("abBa", sum_all(f_list3));
	}
}

TEST(Set, Char) {
	{
		std::set<char> set0 = {};
		EXPECT_EQ("", sum_all(set0));
	}
	{
		std::set<char> set1 = { 'a' };
		EXPECT_EQ("a", sum_all(set1));
	}
	{
		std::set<char> set2 = { 'a', 'b' };
		EXPECT_EQ("ab", sum_all(set2));
	}
	{
		std::set<char> set3 = { 'a', 'B' };
		EXPECT_EQ("Ba", sum_all(set3));
	}
}

TEST(U_Set, Short) {
	{
		std::unordered_set<short> u_set0 = {};
		EXPECT_EQ(0, sum_all(u_set0));
	}
	{
		std::unordered_set<short> u_set1 = { 1 };
		EXPECT_EQ(1, sum_all(u_set1));
	}
	{
		std::unordered_set<short> u_set2 = { 1, 3 };
		EXPECT_EQ(4, sum_all(u_set2));
	}
	{
		std::unordered_set<short> u_set3 = { -1, 3 };
		EXPECT_EQ(2, sum_all(u_set3));
	}
	{
		std::unordered_set<short> u_set4 = { -1, -3 };
		EXPECT_EQ(-4, sum_all(u_set4));
	}
	{
		std::unordered_set<unsigned short> u_set5 = {};
		EXPECT_EQ(0, sum_all(u_set5));
	}
	{
		std::unordered_set<unsigned short> u_set6 = { 1 };
		EXPECT_EQ(1, sum_all(u_set6));
	}
	{
		std::unordered_set<unsigned short> u_set7 = { 1, 3 };
		EXPECT_EQ(4, sum_all(u_set7));
	}
}

TEST(Array, Int) {
	std::array<int, 3> array = { 1, 3, 4 };
	EXPECT_EQ(8, sum_all(array));
}