#include "Subscriber.h"
#include <ctype.h>
#include <regex>

namespace AcademyBilling
{
    bool isNumberValid(const std::string&);

    Subscriber::Subscriber(const std::string &number, const int &balance, BillingRules* tariff, const Refill &lastRefill)
        :balance(balance), tariff(tariff), lastRefill(lastRefill)
    {
        setNumber(number);
        if (this->balance < 0) 
            throw BalanceIsEmpty();
    }

    Subscriber::~Subscriber(void)
    {
    }

    int Subscriber::getBalance() const
    {
        return this->balance;
    }

    std::string Subscriber::getNumber() const
    {
        return this->number;
    }

    BillingRules* Subscriber::getTariff() const
    {
        return this->tariff;
    }

    Refill Subscriber::getLastRefill() const
    {
        return this->lastRefill;
    }

    time_t Subscriber::getLastRefillTime() const
    {
        return this->lastRefill.getTime();
    }

    void Subscriber::setNumber(const std::string& number)
    {
        if (isNumberValid(number))
            this->number = number;
        else
            throw std::invalid_argument("Invalid number");            
    }

    int Subscriber::charge(const int& sum)
    {
        balance -= sum;
        if (balance < 0) 
            throw BalanceIsEmpty();
        return balance;
    }

    int Subscriber::addRefill(const Refill& refill)
    {
        lastRefill = refill;
        return balance += refill.getMoney();
    }

    bool isNumberValid(const std::string& str)
    {
        // Regular expression for +**(***)******* when '*' is digit;
        std::regex mask("\\+\\d{2}\\(\\d{3}\\)\\d{7}");
        return std::regex_match(str, mask);
    }
}