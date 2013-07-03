#pragma once
#include <string>
#include <vector>
#include "Refill.h"
#include "Call.h"
#include "BillingRules.h"

namespace AcademyBilling
{
	class Subscriber
	{
	private: 
		int balance;
		std::string number;
		BillingRules* tariff;
		std::vector<Refill> refills;
	public:
		Subscriber(const std::string&);
		~Subscriber();
		int getBalance() const;
		std::string getNumber() const;
		void setNumber(const std::string&);
		int charge(const Call&);
		int addRefill(const Refill&);
	};
}
