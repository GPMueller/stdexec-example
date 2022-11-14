#include <exec/static_thread_pool.hpp>

#include <iostream>
#include <stdexec/execution.hpp>
#include <vector>

#ifdef STDEXEC_EXAMPLE_USE_CUDA
#include <nvexec/stream_context.cuh>
class compute_resource
{
  public:
    compute_resource() :
        stream_context()
    { }

    stdexec::scheduler auto get_scheduler()
    {
        return stream_context.get_scheduler();
    }

  private:
    nvexec::stream_context stream_context;
};
#else
class compute_resource
{
  public:
    compute_resource() :
        pool(exec::static_thread_pool(8))
    { }

    stdexec::scheduler auto get_scheduler()
    {
        return pool.get_scheduler();
    }

  private:
    exec::static_thread_pool pool;
};
#endif

int main()
{
    const int N = 24; // 10'000;
    std::vector<double> values(N);
    compute_resource resource;
    stdexec::scheduler auto sched = resource.get_scheduler();

    auto bulk_work = stdexec::bulk(N,
        [=](std::size_t i, std::vector<double>& values) {
            values[i] = 1;
            // std::cout << i << "\n";
        });

    stdexec::sender auto work = stdexec::transfer_just(sched, std::move(values))
        | bulk_work;

    stdexec::this_thread::sync_wait(work);

    // std::cout << std::endl;
}
