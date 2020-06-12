#pragma once

#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <chrono>
class Philo {
public:
	Philo(size_t initial_count = 5) {
		count= initial_count;
		for (int i = 0; i < 5; i++) {
			etat[i] = "pense";
		};

	};

	Philo(const Philo& phil) : count(phil.count) {}

	void take(int i) {
		std::cout << "take\n";
		std::unique_lock<std::mutex> lck(mtx);
		etat[i] = "afaim";
		test(i);

		if (etat[i] != "mange") {
			
			
			attente[i].wait(lck);

		}
		else {
			std::cout << "Hello World!\n";
			std::this_thread::sleep_for(std::chrono::minutes(2));
			std::cout << "Hello World!\n";
			etat[i] = "pense";
		}


	}

	void drop(int i) {
		std::cout << "drop\n";
		etat[i] = "pense";
		test(i - 1 % 5);
		test(i + 1 % 5);
	}

	void test(int k) {
		if (etat[k + 1 % 5] != "mange" && etat[k] == "afaim" && etat[k - 1 % 5] != "mange") {
			etat[k] = "mange";
			attente[k].notify_one();
		}
	}
private:
	std::mutex mtx;
	std::condition_variable cv;
	//std::counting_semaphore s;
	size_t count;
	std::condition_variable attente[5];
	std::string etat[5];
}; 
