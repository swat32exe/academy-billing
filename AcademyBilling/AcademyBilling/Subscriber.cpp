#include "Subscriber.h"

namespace AcademyBilling
{
	Subscriber::Subscriber(const std::string& s)
	{
	}

	Subscriber::~Subscriber(void)
	{
	}

	int Subscriber::getBalance() const
	{
		return 1;
	}

	std::string Subscriber::getNumber() const
	{
		return "+38(050)123-45-67";
	}

	int Subscriber::charge(const Call& call)
	{
		return 1;
	}

	int Subscriber::addRefill(const Refill& refill)
	{
		return 1;
	}
}