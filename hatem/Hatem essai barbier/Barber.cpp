#pragma once
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include "semaphore.h"
#include <string>


class Barber {
public:
	Barber():barberReady(1), barberThread(&Barber::WakeUp, this) {
		
	}
	Barber(const Barber& Barber){}

	std::string WakeUp() {

		std::string message = "Le coiffeur se reveille";
		barberReady.P();
		return message;
		

	}
	std::string Sleep() {

		std::string message = "Le coiffeur va dormir";

		barberReady.V();
		return message;
	}

	void Cut() {

	}



private:
	Semaphore barberReady;
	std::thread barberThread;
};

class Customer {
public:
	Customer():customerReady(1), custumerThread(&Customer::Entrer, this) {
	
	}
	Customer(const Customer& Customer){
	
	}

	std::string Entrer() {

		std::string message = "Client entre";
		customerReady.P();
		return message;
	}
	std::string Partir() {
		std::string message = "Client sort";
		customerReady.V();
		return message;
	}



private:
	Semaphore customerReady;
	std::thread custumerThread;
};





class BarberShop {
	public:
		BarberShop(Barber b): barber(b),salleAttente(4), chaise(1), mainThread(&BarberShop::open, this) {
		
		}
		BarberShop(const BarberShop& BarberShop):barber(BarberShop.barber), custumerFIFO(BarberShop.custumerFIFO) {
		}

		

		bool addCustumer(Customer Custome) {
			bool success;
			fifo.P();
			if (numberOfFreeWRSeats >0) {
				if (numberOfFreeWRSeats == max) {
					barber.WakeUp();
				}
				numberOfFreeWRSeats -= 1;
				std::string s=Custome.Entrer();
				print(s);
				custumerFIFO.push(Custome);
				salleAttente.P();
				success = true;
			}
			else {
				success = false;

			}
			
			fifo.V();
			return success;
		}

		void deleteCustumer() {
			fifo.P();
			custumerFIFO.pop();
			numberOfFreeWRSeats +=1;
			fifo.V();
		}

		
		void print(const std::string& s) {
			coutSem.P();
			std::cout << s << std::endl;
			coutSem.V();
		}

	private:
		Semaphore coutSem;
		const int max = 4;
		int numberOfFreeWRSeats=4;
		Barber barber;
		Semaphore fifo;
		std::queue<Customer> custumerFIFO;
		Semaphore chaise;
		Semaphore salleAttente;
		std::thread mainThread;

		void open() {

			while (1) {
				if (!custumerFIFO.empty()) {
					Customer custumer = custumerFIFO.front();
					deleteCustumer();
					chaise.P();
					print("Le barbier coupe les cheuveux du client");
					salleAttente.V();
					std::string ss = custumer.Partir();
					print("Le barbier a fini de coupe les cheuveux");
					print(ss);
					chaise.V();
				}
				else {
					std::string s = barber.Sleep();
					print(s);
				}

			}
		}
	

};