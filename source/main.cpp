#include <exec/static_thread_pool.hpp>

#include <iostream>
#include <stdexec/execution.hpp>
#include <vector>

int main()
{
    const int N = 24; // 10'000;
    std::vector<double> values(N);

    exec::static_thread_pool pool(8);
    auto sched = pool.get_scheduler();

    auto bulk_work = stdexec::bulk(N,
        [=](std::size_t i, std::vector<double>& values) {
            values[i] = 1;
            // std::cout << i << "\n";
        });

    auto work = stdexec::transfer_just(sched, std::move(values))
        | bulk_work;
    stdexec::this_thread::sync_wait(work);

    // std::cout << std::endl;
}
