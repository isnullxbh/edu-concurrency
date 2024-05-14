/**
 * @file    main.cpp
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    13.05.2024
 */

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

class lock_one
{
public:
    void lock(std::size_t idx)
    {
        flags[idx] = true;
        while (flags[1 - idx]) {}
    }

    void unlock(std::size_t idx)
    {
        flags[idx] = false;
    }

private:
    bool flags[2] = { false, false };
};

constexpr std::size_t n = 1'000'000;

void apply_n_times(std::function<int(int)>&& op, int& value, lock_one& m, std::size_t thread_index)
{
    for (std::size_t i = 0; i < n; ++i)
    {
        m.lock(thread_index);
        value = op(value);
        m.unlock(thread_index);
    }
}

int main()
{
    int      r {};
    lock_one m {};

    std::thread t1 { apply_n_times, [](int value){ return value + 1; }, std::ref(r), std::ref(m), 0 };
    std::this_thread::sleep_for(200us);
    std::thread t2 { apply_n_times, [](int value){ return value - 1; }, std::ref(r), std::ref(m), 1 };

    t1.join();
    t2.join();

    std::cout << "Result: " << r << std::endl;

    return 0;
}
