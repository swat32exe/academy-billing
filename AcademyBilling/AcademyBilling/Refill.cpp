#include "Refill.h"
#include <stdexcept>

namespace AcademyBilling
{
    Refill::Refill(const int &money, const time_t &time)
        :money(money), time(time)
    {
    }

    Refill::Refill(const Refill& refill)
        :money(refill.getMoney()), time(refill.getTime())
    {
    }

    Refill::~Refill(void)
    {
    }

    int Refill::getMoney() const
    {
        return this->money;
    }

    void Refill::setMoney(const int &money)
    {
        this->money = money;
    }

    time_t Refill::getTime() const
    {
        return this->time;
    }

    void Refill::setTime(const time_t &aTime)
    {
        this->time = time;
    }

    Refill& Refill::operator= (const Refill &refill)
    {
        this->money = refill.getMoney();
        this->time = refill.getTime();
        return *this;
    }
}