#pragma once
#include <iostream>
#include <pthread.h>
#include <cstring>
#include <functional>
namespace ThreadMoudle
{
    int cnt = 0;

    using threadfunc_t = std::function<void()>;

    enum class TSTATUS
    {
        THREAD_NEW,
        THREAD_RUNNING,
        THREAD_STOP
    };

    class Thread
    {
    public:
        static void *run(void *obj)
        {
            Thread *Self = (Thread *)obj;
            Self->_stu = TSTATUS::THREAD_RUNNING;
            if (!Self->joinable)
            {
                pthread_detach(Self->id);
            }
            Self->_fun();
            return nullptr;
        }
        std::string SetName()
        {
            return "Thread-t" + std::to_string(cnt++);
        }
        Thread(threadfunc_t fun)
            : _fun(fun), joinable(true), _stu(TSTATUS::THREAD_NEW)
        {
            _name = SetName();
        }
        bool Start()
        {
            if (_stu == TSTATUS::THREAD_RUNNING)
            {
                return true;
            }
            else
            {
                int n = pthread_create(&id, NULL, run, this);
                if (n != 0)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
        }
        void EnableDetach()
        {
            if (_stu == TSTATUS::THREAD_NEW)
            {
                joinable = false;
            }
        }
        void EnableJoin()
        {
            if (_stu == TSTATUS::THREAD_NEW)
            {
                joinable = true;
            }
        }
        bool Join()
        {
            if (joinable == false)                       
            {
                return true;
            }
            else
            {
                int n = pthread_join(id, nullptr);
                if (n == 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        ~Thread()
        {
        }

    private:
        pthread_t id;
        threadfunc_t _fun;
        TSTATUS _stu;
        std::string _name;
        bool joinable;
    };
}
