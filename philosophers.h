#ifndef TP1_IFT630_PHILOSOPHERS_H
#define TP1_IFT630_PHILOSOPHERS_H


#include "semaphore.h"

struct Chopstick{

    Chopstick(int id, int owner);

    Semaphore lock;
    int id;
    int owner;
    bool dirty;

    public:
        void pickUP(int id);
        void release();
};



#endif //TP1_IFT630_PHILOSOPHERS_H
