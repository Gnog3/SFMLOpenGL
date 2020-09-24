#pragma once

template<class T, bool Destruct = false>
class NotConstructed {
    private:
        union {
            T member;
        };
    public:
        NotConstructed() noexcept {};
        template<class... Args>
        void construct(Args&& ... args) {
            new(&this->member) T(args...);
        }
        void destruct() {
            member.~T();
        }
        
        T* operator->() {
            return &member;
        }
        
        ~NotConstructed() {
            if constexpr (Destruct) {
                member.~T();
            }
        }
};



