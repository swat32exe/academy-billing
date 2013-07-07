#include "Subscriber.h"
#include <stdexcept>
#include <ctype.h>

namespace AcademyBilling
{
    bool isNumberValid(const std::string&);

    const std::string Subscriber::mask="+**(***)*******";

    Subscriber::Subscriber(const std::string& aNumber, const int& aBalance, BillingRules* aTariff, const Refill aLastRefill)
        :lastRefill(aLastRefill)
    {
        setNumber(aNumber);
        balance=aBalance;
        tariff=aTariff;
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
            number=str;
        }
        else
        {
            throw std::invalid_argument("Invalid number");            
        }
    }

    int Subscriber::charge(const int& sum)
    {
        return balance-=sum;
    }

    int Subscriber::addRefill(const Refill& refill)
    {
        lastRefill=refill;
        return balance+=refill.getMoney();
    }

    bool isNumberValid(const std::string& str)
    {
        if (str.length()!=Subscriber::mask.length())
        {
            return false;
        }
        for (size_t i=0;i<Subscriber::mask.length();++i)
        {
            if (!(Subscriber::mask[i]=='*' && isdigit(str[i]) || Subscriber::mask[i]!='*' && Subscriber::mask[i]==str[i]))
            {
                return false;
            }
        }
        return true;
    }
}