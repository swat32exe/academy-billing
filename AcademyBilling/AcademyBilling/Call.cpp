#include "Call.h"
#include "Subscriber.h"
#include <stdexcept>

namespace AcademyBilling
{
	Call::Call(const std::string& _caller,const std::string& _callee,const time_t& _time,const unsigned int& _duration)
	{
		setCallerNumber(_caller);
		setCalleeNumber(_callee);
		setTime(_time);
		duration=_duration;
	}

	Call::~Call(void)
	{
	}

	std::string Call::getCallerNumber() const
	{
		return callerNumber;
	}

	std::string Call::getCalleeNumber() const
	{
		return calleeNumber;
	}

	void Call::setCalleeNumber(const std::string& str)
	{
		if (Subscriber::isNumberValid(str)) 
		{
			calleeNumber=str;
		}
		else
		{
			throw std::invalid_argument("Callee number is bad");
		}
	}

	void Call::setCallerNumber(const std::string& str)
	{
		if (Subscriber::isNumberValid(str)) 
		{
			callerNumber=str;
		}
		else
		{
			throw std::invalid_argument("Caller number is bad");
		}
	}

	time_t Call::getTime() const
	{
		return time;
	}

	void Call::setTime(const time_t& _time)
	{
		// Constant magictime initialization in Refill::setTime();
		extern const time_t magictime;
		if (_time<magictime || _time>::time(0))
		{
			throw std::invalid_argument("Time is bad.");
		}
		time=_time;
	}

	unsigned int Call::getDuration() const
	{
		return duration;
	}

	
}