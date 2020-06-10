#include "philosophers.h"
#include <iostream>
#include <chrono>
#include "utils.h"
#include "semaphore.h"
#include <thread>

// Implémentation de la solution de Chandy/Misra avec des sémaphores

using namespace std::chrono_literals;
using namespace cppUtils;
using std::chrono::milliseconds;
using std::string;


bool dining = true;
Semaphore coutSem(1);

void print(string s){
    coutSem.P();
    std::cout << s << std::endl;
    coutSem.V();
}


struct Philosopher{

    const string name;
    const int id;
    Chopstick& leftChop;
    Chopstick& rightChop;
    std::thread lifethread;

    Philosopher(const string &name, int id, Chopstick &chopstick1, Chopstick &chopstick2) :
            name(name), id(id), leftChop(chopstick1), rightChop(chopstick2), lifethread(&Philosopher::dine, this) {}
    void think(){
        print(name + " is thinking... ") ;
        // Think for
        std::this_thread::sleep_for(milliseconds(random<uint16_t>(400, 600)));
    }

    void eat(){
        print (name + " is hungry");

        // On demande les deux baguettes
        leftChop.pickUP(id);
        print(name + " picked up left chopstick");
        rightChop.pickUP(id);
        print(name + " picked up right chopstick");

        std::this_thread::sleep_for(milliseconds(400));
        print(name + " is eating");

        // On les dépose
        leftChop.release();
        rightChop.release();
    }

    void dine()
    {
        do
        {
            think();
            eat();
        } while (dining);
        lifethread.join();
    }

};


void Chopstick::pickUP(int id){
    // Si la demande est faite par qqun d'autre
    while(owner != id){
        // Si le chopstick est sale, c'est que le philosophe l'a déjà utilisé.
        // Il doit donc le céder
        if(dirty){
            lock.P();
            dirty = false;
            owner = id;
        }
        // S'il est propre c'est que le philosophe qui l'a présentement n'a pas encore
        // mangé donc on doit attendre qu'il appelle release
        else{
            lock.P();
        }
    }
    // Si le philosophe a déjà la possession de la baguette,
    // pas besoin d'attendre
}

void Chopstick::release(){
    dirty = true;
    lock.V();
}

Chopstick::Chopstick(int id, int owner) :
    lock(1), id(id), owner(owner),dirty(true) {}
    Semaphore sem(0);


int main(){

    Chopstick chopstick1(1, 1);
    Chopstick chopstick2(2,2);
    Chopstick chopstick3(3,3);
    Chopstick chopstick4(4,4);
    Chopstick chopstick5(5,1);

    Philosopher phil1("1", 1, chopstick1, chopstick2);
    Philosopher phil2("2", 2, chopstick2, chopstick3);
    Philosopher phil3("3", 3, chopstick3, chopstick4);
    Philosopher phil4("4", 4, chopstick4, chopstick5);
    Philosopher phil5("5", 5, chopstick5, chopstick1);

    std::this_thread::sleep_for(std::chrono::seconds(10));
    dining = false;
    print("Fini");

    return 0;


}
