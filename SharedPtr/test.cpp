#include "pch.h"
#include "SharedPtr.h"
#include <new>
#include <iostream>

class MemoryLeakDetector {
public:


    MemoryLeakDetector() {
        _CrtMemCheckpoint(&memState_);
    }

    ~MemoryLeakDetector() {
        _CrtMemState stateNow, stateDiff;
        _CrtMemCheckpoint(&stateNow);
        int diffResult = _CrtMemDifference(&stateDiff, &memState_, &stateNow);
        if (diffResult)
            reportFailure(stateDiff.lSizes[1]);
    }
private:
    void reportFailure(unsigned int unfreedBytes) {
        FAIL() << "Memory leak of " << unfreedBytes << " byte(s) detected.";
    }
    _CrtMemState memState_;
};

static size_t num_delete = 0;

template<typename Type>
class Deleter final {
public:

    using value_type = std::remove_extent_t<Type>;

    Deleter() = default;

    void operator() (value_type* arr) {
        if (arr == nullptr) {
            return;
        }
        delete[] arr;
        num_delete++;
    }
};

template<typename Type>
class NotDefaultDeleter final {
public:
    using value_type = std::remove_extent_t<Type>;

    NotDefaultDeleter(value_type val) {}
    NotDefaultDeleter() = delete;

    void operator() (value_type* arr) {
        if (arr == nullptr) {
            return;
        }
        delete[] arr;
        value++;
    }

    static int value;
};

int NotDefaultDeleter<int>::value = 0;

template<typename Type>
class DefaultDeleter final {
public:
    using value_type = std::remove_extent_t<Type>;

    DefaultDeleter() = default;

    void operator() (value_type* arr) {
        if (arr == nullptr) {
            return;
        }
        delete[] arr;
        num_delete++;
    }
};

TEST(Constructor, NotDefaultDeleterTEST) {
    MemoryLeakDetector leakDetector;
    {
        int* arr = new int[4];

        NotDefaultDeleter<int> deleter(0);

        SharedPtr<int[], NotDefaultDeleter<int>> ptr(arr, deleter);
    }
    EXPECT_EQ(NotDefaultDeleter<int>::value, 1);
}

TEST(Constructor, DefaultDeleterTEST) {
    MemoryLeakDetector leakDetector;
    {
        int* arr = new int[4];

        SharedPtr<int[], DefaultDeleter<int>> ptr(arr);

    }

    EXPECT_TRUE(num_delete == 1);
}

TEST(DeleterTEST, nullptr) {
    MemoryLeakDetector leakDetector;
    {
        SharedPtr<int, Deleter<int>> ptr{};
    }
}


TEST(Constructor, Default) {
    MemoryLeakDetector leakDetector{};

	SharedPtr<int> ptr{};

	EXPECT_TRUE(ptr.get() == nullptr);
}

TEST(Constructor, Ptr) {
    MemoryLeakDetector leakDetector{};

    int* ptrInt = new int[10];

	SharedPtr<int> ptr(ptrInt);

	EXPECT_TRUE(ptr.get() == ptrInt);
	EXPECT_TRUE(ptr.getCount() == 1);
}

TEST(Constructor, NullPtr) {
    MemoryLeakDetector leakDetector{};

    SharedPtr<int> ptr(nullptr);

    EXPECT_TRUE(ptr.get() == nullptr);
    EXPECT_TRUE(ptr.getCount() == 0);
}

TEST(Constructor, Copy) {
    MemoryLeakDetector leakDetector{};

    int* ptrInt = new int[10];

    SharedPtr<int> ptr1(ptrInt);

    EXPECT_TRUE(ptr1.get() == ptrInt);
    EXPECT_TRUE(ptr1.getCount() == 1);

    {
        SharedPtr ptr2(ptr1);
        EXPECT_TRUE(ptr2.get() == ptrInt);
        EXPECT_TRUE(ptr2.getCount() == 2);
        EXPECT_TRUE(ptr1.getCount() == 2);
    }

    EXPECT_TRUE(ptr1.get() == ptrInt);
    EXPECT_TRUE(ptr1.getCount() == 1);
    int data = *ptrInt;
}

TEST(Constructor, CopyEmpty) {
    MemoryLeakDetector leakDetector{};

    SharedPtr<int> ptr1{};
    SharedPtr<int> ptr2(ptr1);

    EXPECT_TRUE(ptr1.getCount() == 0);
    EXPECT_TRUE(ptr2.getCount() == 0);
}

TEST(Operators, AssignmentPtr) {
    MemoryLeakDetector leakDetector{};

    int* ptrInt = new int[10];

    SharedPtr<int> ptr{};

    ptr = ptrInt;

    EXPECT_TRUE(ptr.get() == ptrInt);
    EXPECT_TRUE(ptr.getCount() == 1);
}

TEST(Operators, AssignmentNullptr) {
    MemoryLeakDetector leakDetector{};

    SharedPtr<int> ptr{};

    ptr = nullptr;

    EXPECT_TRUE(ptr.get() == nullptr);
    EXPECT_TRUE(ptr.getCount() == 0);
}

TEST(Operators, AssignmentEmptySharedPtr) {
    MemoryLeakDetector leakDetector{};

    SharedPtr<int> ptr{};

    SharedPtr<int> ptr2{};

    ptr2 = ptr;

    EXPECT_TRUE(ptr2.get() == nullptr);
    EXPECT_TRUE(ptr2.getCount() == 0);
}

TEST(Operators, AssignmentSharedPtr) {
    MemoryLeakDetector leakDetector{};

    int* ptrInt = new int[10];

    SharedPtr<int> ptr(ptrInt);

    SharedPtr<int> ptr2{};

    ptr2 = ptr;

    EXPECT_TRUE(ptr2.get() == ptrInt);
    EXPECT_TRUE(ptr2.getCount() == 2);
}

TEST(Operators, AssignmentSharedPtr2) {
    MemoryLeakDetector leakDetector{};

    int* ptrInt = new int[10];
    int* ptrInt2 = new int[10];

    SharedPtr<int> ptr(ptrInt);

    SharedPtr<int> ptr2{};

    ptr2 = ptr;

    EXPECT_TRUE(ptr2.get() == ptrInt);
    EXPECT_TRUE(ptr2.getCount() == 2);

    SharedPtr<int> ptr3(ptr);

    EXPECT_TRUE(ptr.getCount() == 3);
    EXPECT_TRUE(ptr2.getCount() == 3);
    EXPECT_TRUE(ptr3.getCount() == 3);

    SharedPtr<int> ptr4(ptrInt2);

    EXPECT_TRUE(ptr4.getCount() == 1);

    ptr2 = ptr4;

    EXPECT_TRUE(ptr.getCount() == 2);
    EXPECT_TRUE(ptr2.getCount() == 2);
    EXPECT_TRUE(ptr3.getCount() == 2);
    EXPECT_TRUE(ptr4.getCount() == 2);

    EXPECT_TRUE(ptr2 == ptr4);
    EXPECT_TRUE(ptr == ptr3);
}

TEST(Operator, Dereference) {
    MemoryLeakDetector leakDetector;

    int* ptr1 = new int;

    SharedPtr<int> ptr(ptr1);

    EXPECT_TRUE(*ptr == *ptr1);
}

TEST(Operator, DereferenceNullptr) {
    MemoryLeakDetector leakDetector;

    SharedPtr<int> ptr{};

    EXPECT_THROW(*ptr, NullptrDereference);
}

class A final {
public:
    A() = default;
    A(int a) : a(a)
    {
    }
    int getInt() {
        return a;
    }
    ~A() {
        numDelete++;
    }

    static inline int numDelete = 0;
private:
    int a;
};

TEST(Operator, Arrow) {
    int a = 1;
    SharedPtr<A> ptr(new A(a));

    EXPECT_TRUE(1 == ptr->getInt());
}

TEST(Operator, ArrowNullptr) {
    SharedPtr<A> ptr{};

    EXPECT_THROW((ptr)->getInt(), NullptrDereference);
}

TEST(Operator, Array) {
    MemoryLeakDetector leakDetector;

    auto ptr1 = new std::string[4];
    {
        SharedPtr<std::string[]> ptr(ptr1);
    }
}

TEST(DeleterTEST, manyDelete) {
    A::numDelete = 0;
    MemoryLeakDetector leakDetector;
    auto ptr1 = new A[5];
    {
        SharedPtr<A[]> ptr(ptr1);
    }
    EXPECT_EQ(A::numDelete, 5);
}

TEST(Operator, AssignmentInNotEmptyNullptr) {
    MemoryLeakDetector leakDetector;

    int* ptr1 = new int;

    SharedPtr<int> ptr(ptr1);

    EXPECT_TRUE(*ptr == *ptr1);

    ptr = nullptr;

    EXPECT_TRUE(ptr.getCount() == 0);
}

