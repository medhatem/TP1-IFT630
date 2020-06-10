/*
	Par: Daniel-Junior Dubé
	Date: 2020-06-03

	Exemple de base du problème producteur / consommateur sans limite supérieure de production à l'aide d'une
	implémentation personnalisée des sémaphores.

	3 thread :
	- Thread principal (appelant)
	- Thread consommateur
	- Thread producteur
*/

#include <iostream>
#include <chrono>
#include <thread>
#include "semaphore.h"

using namespace std::chrono_literals;

size_t TOTAL_NB_ITEMS = 1000000;
Semaphore items(0);
Semaphore done(0);

void consume() {
	for (size_t i = 0; i < TOTAL_NB_ITEMS; ++i) {
		items.P();
		std::cout << "consuming" << std::endl;
	}
	done.V();
}

void produce() {
	for (size_t i = 0; i < TOTAL_NB_ITEMS; ++i) {
		std::cout << "producing " << std::endl;
		std::this_thread::sleep_for(2s);
		items.V();
	}
}

int main() {
	std::cout << "starting" << std::endl;
	std::thread t2(consume);
	std::thread t3(produce);
	done.P();
	std::cout << "done" << std::endl;
	t2.join();
	t3.join();
	return 0;
}