#ifndef TP1_IFT630_PHILOSOPHERS_H
#define TP1_IFT630_PHILOSOPHERS_H

#include <thread>
#include "semaphore.h"

struct Chopstick{

    private:
        Semaphore lock;
        const int id;
        int owner;
        bool dirty;

    public:
        void pickUP(const int id);
        void release();
        Chopstick(int id, int owner);
};

    struct Philosopher{
    private :
        const std::string name;
        const int id;
        Chopstick& leftChop;
        Chopstick& rightChop;
        std::thread thread;
        bool dining;
        Semaphore done;
    public:
        Philosopher(const std::string &name, int id, Chopstick &chopstick1, Chopstick &chopstick2);
        void dine();
        void eat();
        void think();
        void leaveTable();
};

#endif //TP1_IFT630_PHILOSOPHERS_H
