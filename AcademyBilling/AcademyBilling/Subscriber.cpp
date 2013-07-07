#include "Subscriber.h"
#include <stdexcept>
#include <ctype.h>
#include <regex>

namespace AcademyBilling
{
    bool isNumberValid(const std::string&);

    const std::string Subscriber::mask = "+**(***)*******";

    Subscriber::Subscriber(const std::string& aNumber, const int& aBalance, BillingRules* aTariff, const Refill aLastRefill)
        :balance(aBalance),tariff(aTariff),lastRefill(aLastRefill)
    {
        setNumber(aNumber);
    }

    Subscriber::~Subscriber(void)
    {
    }

    int Subscriber::getBalance() const
    {
        return balance;
    }

    std::string Subscriber::getNumber() const
    {
        return number;
    }

    BillingRules* Subscriber::getTariff() const
    {
        return tariff;
    }

    Refill Subscriber::getLastRefill() const
    {
        return lastRefill;
    }

    time_t Subscriber::getLastRefillTime() const
    {
        return lastRefill.getTime();
    }

    void Subscriber::setNumber(const std::string& str)
    {
        if(isNumberValid(str))
        {
            number = str;
        }
        else
        {
            throw std::invalid_argument("Invalid number");            
        }
    }

    int Subscriber::charge(const int& sum)
    {
        return balance -= sum;
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
		return std::regex_match(str,mask);
    }
}