#pragma once

#include "Core.h"
#include <memory>

// Custom smart pointers
// TODO: Change pointers to Scoped and Shared
namespace Cherry
{
	template <typename T>
	class Scoped
	{
		typedef T value_type;
	public:
		Scoped()
			: _Value(nullptr) {}

		Scoped(T*&& v)
			: _Value(v) {};

		Scoped(std::nullptr_t)
			: _Value(nullptr) {}

		Scoped(const Scoped& scoped) = delete;

		Scoped(Scoped&& right)
		{
			_Value = right._Value;
			right._Value = nullptr;
		}

		~Scoped()
		{
			delete _Value;
		}

		T* Get()
		{
			return _Value;
		}

		void Reset(T*&& other)
		{
			delete _Value;
			_Value = other;
		}

		void Free()
		{
			delete _Value;
			_Value = nullptr;
		}

		bool IsAlive() { return _Value != nullptr; }

		void operator=(const Scoped&) = delete;

		void operator=(Scoped&& right)
		{
			delete _Value;
			_Value = right._Value;

			right._Value = nullptr;
		};

		void operator=(std::nullptr_t)
		{
			delete _Value;
			_Value = nullptr;
		}

		T* operator->()
		{
			return _Value;
		}

		T operator*()
		{
			return *_Value;
		}

		template <typename T, typename... Args>
		static Scoped<T> Create(Args&&... args)
		{
			return Scoped<T>(new T(std::forward<Args>(args)...));
		}
	private:
		T* _Value;
	};

	template <typename T>
	class Shared
	{
	public:
		Shared()
			: _Value(nullptr) {}

		Shared(T*&& v)
		{
			_Value = new PtrValue<T>(v);
		};

		Shared(const Shared& right)
		{
			if (right._Value != nullptr)
			{
				_Value = right._Value;
				_Value->RepCount++;
				return;
			}
		}

		Shared(Shared&& shared)
		{
			_Value = shared._Value;
			_Value->RepCount++;
		}

		~Shared()
		{
			if (_Value == nullptr)
				return;

			if (_Value->RepCount == 1)
				delete _Value;
			else
				_Value->RepCount--;
		}

		T* Get()
		{
			return _Value->ptr;
		}

		void Reset(T*&& other)
		{
			if (_Value->RepCount == 1)
				delete _Value;
			else
				_Value->RepCount--;

			_Value = new PtrValue<T>(other);
			_Value->RepCount++;
		}

		void Free()
		{
			delete _Value;
		}

		bool IsAlive()
		{
			if (_Value == nullptr)
				return false;

			return true;
		}

		void operator=(const Shared& shared)
		{
			if (_Value != shared._Value)
			{
				_Value = shared._Value;
				_Value->RepCount++;
			}
		};

		void operator=(Shared&& right)
		{
			_Value = right._Value;
			right._Value = nullptr;
		};

		void operator=(std::nullptr_t)
		{
			if (_Value->RepCount == 1)
			{
				delete _Value;
			}
			else
			{
				_Value->RepCount--;
				_Value = nullptr;
			}
		}

		T* operator->()
		{
			return _Value->ptr;
		}

		T operator*()
		{
			return *_Value->ptr;
		}

		template <typename T, typename... Args>
		static Shared<T> Create(Args&&... args)
		{
			return Shared<T>(new T(std::forward<Args>(args)...));
		}
	private:
		template <typename T>
		struct PtrValue
		{
			T* ptr;
			int RepCount;

			PtrValue(T* value)
				: ptr(value), RepCount(1) {};
		};

		PtrValue<T>* _Value;
	};

}
