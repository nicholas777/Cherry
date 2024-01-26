#pragma once

#include <utility>

// Custom smart pointers
// TODO: Change pointers to Scoped and Shared
namespace Cherry {
    template<typename T>
    class Scoped
    {
        typedef T value_type;
    public:
        Scoped(): _Value(nullptr) {}

        Scoped(T*&& v)
            : _Value(v){

              };

        Scoped(T*& other) {
            _Value = other;
            other = nullptr;
        }

        Scoped([[maybe_unused]] std::nullptr_t ptr): _Value(nullptr) {}

        Scoped(const Scoped& scoped) = delete;

        Scoped(Scoped&& right) {
            _Value = right._Value;
            right._Value = nullptr;
        }

        ~Scoped() { delete _Value; }

        T* Get() const { return _Value; }

        void Reset(T*& other = nullptr) {
            delete _Value;
            _Value = other;
            other = nullptr;
        }

        void Reset(T*&& other = nullptr) {
            delete _Value;
            _Value = other;
            other = nullptr;
        }

        void Free() {
            delete _Value;
            _Value = nullptr;
        }

        bool IsAlive() { return _Value != nullptr; }

        void operator=(const Scoped&) = delete;

        void operator=(Scoped&& right) noexcept {
            _Value = right._Value;
            right._Value = nullptr;
        };

        void operator=(std::nullptr_t) {
            delete _Value;
            _Value = nullptr;
        }

        T* operator->() const { return _Value; }

        T operator*() const { return *_Value; }

        operator bool() { return _Value != nullptr; }

        bool operator==(Scoped<T> right) { return _Value == right._Value; }

        bool operator!=(Scoped<T> right) { return _Value != right._Value; }

        template<typename T2, typename... Args>
        static Scoped<T2> Create(Args&&... args) {
            return Scoped<T2>(new T2(std::forward<Args>(args)...));
        }
    private:
        T* _Value;
    };

    template<typename T>
    class Shared
    {
    public:
        Shared(): _Value(new PtrValue(nullptr)) {}

        Shared(T*&& v) { _Value = new PtrValue(v); };

        Shared(const Shared& right) {
            if (right._Value != nullptr) {
                _Value = right._Value;
                _Value->RepCount++;
                return;
            }

            _Value = nullptr;
        }

        Shared(Shared&& shared) {
            _Value = shared._Value;
            _Value->RepCount++;
        }

        ~Shared() {
            if (_Value == nullptr)
                return;

            if (_Value->RepCount == 1)
                delete _Value;
            else
                _Value->RepCount--;
        }

        T* Get() const { return _Value->ptr; }

        void Reset(T*&& other) {
            if (_Value->RepCount == 1)
                delete _Value;
            else
                _Value->RepCount--;

            _Value = new PtrValue(other);
            _Value->RepCount++;
        }

        void Free() { delete _Value; }

        int GetRepCount() {
            if (_Value)
                return _Value->RepCount;

            return -1;
        }

        bool IsAlive() {
            if (_Value->ptr == nullptr)
                return false;

            return true;
        }

        void operator=(const Shared& shared) {
            if (_Value != shared._Value) {
                _Value = shared._Value;
                _Value->RepCount++;
            }
        };

        void operator=(Shared&& right) noexcept {
            _Value = right._Value;
            right._Value = nullptr;
        };

        void operator=(std::nullptr_t) {
            if (_Value->RepCount == 1) {
                delete _Value;
            } else {
                _Value->RepCount--;
                _Value = nullptr;
            }
        }

        T* operator->() { return _Value->ptr; }

        T operator*() { return *_Value->ptr; }

        operator bool() { return _Value->ptr != nullptr; }

        bool operator==(Scoped<T> right) { return _Value == right._Value; }

        bool operator!=(Scoped<T> right) { return _Value != right._Value; }

        template<typename T2, typename... Args>
        static Shared<T> Create(Args&&... args) {
            return Shared<T>(new T2(std::forward<Args>(args)...));
        }
    private:
        struct PtrValue {
            T* ptr;
            int RepCount;

            PtrValue(T* value): ptr(value), RepCount(1){};
        };

        PtrValue* _Value;
    };

}
