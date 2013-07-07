#include "Refill.h"
#include <stdexcept>

namespace AcademyBilling
{
    Refill::Refill(const int& aMoney,const time_t& aTime)
		:money(aMoney),time(aTime)
	{
    }

    Refill::Refill(const Refill& aRefill)
		:money(aRefill.getMoney()),time(aRefill.getTime())
    {
    }

    Refill::~Refill(void)
    {
    }

    int Refill::getMoney() const
    {
        return money;
    }

    void Refill::setMoney(const int& aMoney)
    {
        money = aMoney;
    }

    time_t Refill::getTime() const
    {
        return time;
    }

    void Refill::setTime(const time_t& aTime)
    {
        time = aTime;
    }

    Refill& Refill::operator=(const Refill& aRefill)
    {
        money = aRefill.getMoney();
        time = aRefill.getTime();
        return *this;
    }
}