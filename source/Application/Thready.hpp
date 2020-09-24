#pragma once
#include <thread>
#include <optional>
#include <condition_variable>
class Thready {
    private:
        
        std::optional<std::thread> thread;
        std::condition_variable inited_cond;
        std::mutex mutex;
        volatile bool inited = false;
        volatile bool on = true;
    protected:
        template<class T>
        void start_thread(void (T::*func)(), T* instance) {
            thread.emplace(func, instance);
        }
        void set_inited() {
            inited = true;
            inited_cond.notify_all();
        }
        bool isOn() {
            return on;
        }
    public:
        void wait_init() {
            std::unique_lock<std::mutex> lock(mutex);
            while (!inited) {
                inited_cond.wait(lock);
            }
        }
        virtual void require_stop() {
            on = false;
        }
        void wait_stop() {
            require_stop();
            if (thread) {
                thread->join();
            }
        }
};
