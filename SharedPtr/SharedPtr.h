#pragma once
#include <type_traits>
#include <memory>
#include "SharedPtrExceptions.h"

template<typename TDeleter, typename Type>
concept is_deleter_correct = requires(TDeleter deleter, Type * T) {
	deleter(T);
};

template<class Type, class TDeleter = std::default_delete<Type>>
requires is_deleter_correct<TDeleter, std::remove_extent_t<Type>>
class SharedPtr final {
public:
	using tSharedPtr = SharedPtr<Type, TDeleter>;
	using valueType = std::remove_extent_t<Type>;

	SharedPtr() noexcept requires std::is_default_constructible_v<TDeleter> = default;
	SharedPtr(valueType* pObj) requires std::is_default_constructible_v<TDeleter> : SharedPtr(pObj, TDeleter{}) {}
	SharedPtr(valueType* pObj, const TDeleter& deleter) : ptr(pObj), deleter(deleter){
		if (pObj == nullptr) {
			counter = nullptr;
		}
		else {
			counter = new size_t(1);
		}
	}
	SharedPtr(tSharedPtr&& otherSharedPtr) noexcept {
		ptr = otherSharedPtr.ptr;
		counter = otherSharedPtr.counter;
		deleter = otherSharedPtr.deleter;

		otherSharedPtr.ptr = nullptr;
		otherSharedPtr.counter = nullptr;
	} 
	SharedPtr(const tSharedPtr& otherSharedPtr) noexcept {
		ptr = otherSharedPtr.ptr;
		counter = otherSharedPtr.counter;
		deleter = otherSharedPtr.deleter;
		if (ptr != nullptr) {
			*counter += 1;
		}
	}

	~SharedPtr() noexcept {
		decreaseRefCount();
	}

	tSharedPtr& operator=(tSharedPtr&& otherSharedPtr) noexcept{
		if (this == &otherSharedPtr) {
			return *this;
		}
		decreaseRefCount();
		ptr = otherSharedPtr.ptr;
		otherSharedPtr.ptr = nullptr;
		counter = otherSharedPtr.counter;
		otherSharedPtr.counter = nullptr;
		deleter = otherSharedPtr.deleter;
		return *this;
	}
	tSharedPtr& operator=(valueType* pObj) noexcept {
		if (ptr == pObj) {
			return *this;
		}
		decreaseRefCount();

		*this = SharedPtr(pObj);
		return *this;
	}
	tSharedPtr& operator=(const tSharedPtr& otherSharedPtr) noexcept {
		if (this == &otherSharedPtr) {
			return *this;
		}

		*this = SharedPtr(otherSharedPtr);
		return *this;
	}

	valueType& operator*() const requires (!(std::is_array_v<Type>)) {
		if (!ptr) {
			throw NullptrDereference();
		}
		return *ptr;
	}

	valueType* operator->() const requires (!(std::is_array_v<Type>)) {
		if (!ptr) {
			throw NullptrDereference();
		}
		return ptr;
	}

	valueType* get() const noexcept {
		return ptr;
	}

	TDeleter& getDeleter() const noexcept {
		return deleter;
	}

	operator bool() const noexcept {
		return ptr != nullptr;
	}

	size_t getCount() const noexcept {
		return counter == nullptr ? 0 : *counter;
	}

	valueType& operator[](size_t indx) const requires (std::is_array_v<Type>) {
		return ptr[indx];
	}
private:
	valueType* ptr;
	TDeleter deleter;
	size_t* counter;

	void decreaseRefCount() noexcept {
		if (counter == nullptr) {
			return;
		}
		if (*counter > 1) {
			*counter -= 1;
			return;
		}
		deleter(ptr);
		ptr = nullptr;
		delete counter;
		counter = nullptr;
	}
};