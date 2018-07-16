#include <chrono> 
#include <future> 
#include <mutex>
#include <string> 
#include <vector> 

#include "thread_pool.h"

ThreadPool::ThreadPool(int size) 
{
    // all threads run worker_loop which waits for tasks to be in the queue
    // and then dequeue them
    for (int i=0; i<size; ++i) { 
        m_workers.emplace_back([this](){worker_loop();}); 
    }
}

ThreadPool::~ThreadPool()
{
    // abort all threads, wake them up and wait to join as worker_loop() exits.
    {
        std::lock_guard<std::mutex>(m_state.mtx); 
        m_state.aborting = true;
    }

    m_cv.notify_all(); 

    for (std::thread& t: m_workers) { 
        t.join(); 
    }
}

void ThreadPool::enqueue_task(TaskFn task) 
{
    // add task to queue and notify one of the worker threads to wake up if available 
    {
        std::lock_guard<std::mutex> lg(m_state.mtx); 
        m_state.work_queue.push(move(task)); 
    } 

    m_cv.notify_one();
    printf("enqueue task\n"); 
}

void ThreadPool::worker_loop() 
{
    while (1) {
        // acquire the lock 
        std::unique_lock<std::mutex> lk(m_state.mtx); 

        // wait to be woken up if queue is empty 
        while (m_state.work_queue.empty() && !m_state.aborting) { 
            m_cv.wait(lk); 
        }

        if (m_state.aborting) 
            break; 
 
        TaskFn tf = std::move(m_state.work_queue.front()); 
        m_state.work_queue.pop();

        // unlock and then run the task 
        lk.unlock();
        tf(); 
    }  
}

