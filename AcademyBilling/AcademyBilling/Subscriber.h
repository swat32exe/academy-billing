#ifndef _SUBSCRIBER_H
#define _SUBSCRIBER_H

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
        BillingRules *tariff;
        Refill lastRefill;
        const static std::string mask;
    public:
        Subscriber(const std::string&, const int&, BillingRules*, const Refill);
        Subscriber(const Subscriber&);
        ~Subscriber();
        int getBalance() const;
        std::string getNumber() const;
        BillingRules* getTariff() const;
        Refill getLastRefill() const;
        time_t getLastRefillTime() const;
        void setNumber(const std::string&);
        int charge(const int&);
        int addRefill(const Refill&);
        static bool isNumberValid(const std::string&);
    };
}

#endif