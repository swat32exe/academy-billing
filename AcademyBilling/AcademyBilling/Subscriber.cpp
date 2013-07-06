#include "Subscriber.h"
#include <stdexcept>
#include <ctype.h>

namespace AcademyBilling
{
	const std::string Subscriber::mask="+3(***)*******";

	Subscriber::Subscriber(const std::string& _number, const int& _balance, BillingRules* _tariff, const Refill _lastRefill)
		:lastRefill(_lastRefill)
	{
		setNumber(_number);
		balance=_balance;
		tariff=_tariff;
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

	bool Subscriber::isNumberValid(const std::string& str)
	{
		if (str.length()!=mask.length())
		{
			return false;
		}
		for (size_t i=0;i<mask.length();++i)
		{
			if (!(mask[i]=='*' && isdigit(str[i]) || mask[i]!='*' && mask[i]==str[i]))
			{
				return false;
			}
		}
		return true;
	}
}