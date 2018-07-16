#include "thread_pool.h"

int main()
{
   const int NUM_THREADS = 8; 
   const int NUM_TASKS = 16; 

   ThreadPool tp(NUM_THREADS);
   std::vector<std::future<void>> futures;

   for (int i=0; i<NUM_TASKS; ++i) {
       TaskFn task([](){std::this_thread::sleep_for(std::chrono::seconds(1));
                        printf ("task is running\n");});
       futures.emplace_back(task.get_future());
       tp.enqueue_task(move(task));
   }

   for (std::future<void>&f: futures) {
        f.get();
   }

   return 0;
}
