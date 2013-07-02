#include "Call.h"

namespace AcademyBilling
{
	Call::Call(void)
	{
	}

	Call::~Call(void)
	{
	}

	std::string Call::getFrom() const
	{
		return "+38(050)123-45-67";
	}

	std::string Call::getTo() const
	{
		return "+38(050)123-45-68";
	}

	time_t Call::getTime() const
	{
		return 414086872;
	}

	unsigned int Call::getDuration() const
	{
		return 1;
	}
}