#include <future>
#include <queue> 
#include <thread> 
#include <vector> 

#pragma once

// implementation is taken from Mastering C++17 stl library (Arthur O'Dwyer).

using TaskFn = std::packaged_task<void()>; 

class ThreadPool 
{
    public: 
       ThreadPool(int size); 
      ~ThreadPool();
      void enqueue_task(TaskFn tf); 

    private: 
       // associate mutex with the queue and aborting since they are shared
       // across worker threads. 
       struct {
            std::mutex mtx; 
            std::queue<TaskFn> work_queue; 
            bool aborting = false; 
       } m_state; 

       std::vector<std::thread> m_workers; 
       // conditional variable is used to wait and notify when tasks in queue are available.
       std::condition_variable m_cv; 
       // worker_loop is the primary loop which checks for available tasks in the worker 
       // thread. 
       void worker_loop(); 
}; 
