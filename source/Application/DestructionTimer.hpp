#pragma once

#include <string>
#include <iostream>
#include <utility>
#include "Timer/Timer.hpp"
#include "NotConstructed.hpp"

template<class T>
class DestructionTimer {
    private:
        std::string name;
        NotConstructed<T> object;
    public:
        template<class... Args>
        explicit DestructionTimer(std::string name = "?", Args&& ... args) : name(std::move(name)) {
            object.construct(args...);
        };
        ~DestructionTimer() {
            std::cout << "Destructing " << name << "..." << std::endl;
            Timer timer;
            object.destruct();
            std::cout << name << " destructed in " << timer.getMilliseconds() << "ms" << std::endl;
        }
        T* operator->() {
            return object.operator->();
        }
};
