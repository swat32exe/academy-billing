#include "Refill.h"
#include <stdexcept>

namespace AcademyBilling
{
	Refill::Refill(const int& _money,const time_t& _time)
	{
		money=_money;
		setTime(_time);
	}

	Refill::Refill(const Refill& _refill)
	{
		money=_refill.getMoney();
		time=getTime();
	}

	Refill::~Refill(void)
	{
	}

	int Refill::getMoney() const
	{
		return money;
	}

	void Refill::setMoney(const int& _money)
	{
		money=_money;
	}

	time_t Refill::getTime() const
	{
		return time;
	}

	void Refill::setTime(const time_t& _time)
	{
		// Constant magictime is 01.01.2000.
		const time_t magictime=946677600;
		if (_time<magictime || _time>::time(0))
		{
			throw std::invalid_argument("Time is bad.");
		}
		time=_time;
	}

	Refill& Refill::operator=(const Refill& _refill)
	{
		money=_refill.getMoney();
		time=_refill.getTime();
		return *this;
	}
}