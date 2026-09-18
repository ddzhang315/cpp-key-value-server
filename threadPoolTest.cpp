#include "threadPool.h"
#include <atomic>
#include <cassert>
#include <iostream>
#include <vector>

int main()
{
    constexpr int taskcount = 100;
    std::vector<int> results(taskcount,0);
    std::atomic<int> completed{0};

    {
        ThreadPool pool {4};
        for(int i =0; i<taskcount; ++i)
        {
            pool.enqueue([i,&results,&completed]()
            {
                results[i] = i * i;
                ++completed;
            }
            );

        } 
    }

    for(int i =0; i<taskcount; ++i)
    {
        assert(results[i]== i*i);
    }

    assert(completed.load()==taskcount);

    std::cout <<"Thread pool test passed\n";
    return 0;

}