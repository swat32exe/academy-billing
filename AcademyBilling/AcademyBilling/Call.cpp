#include "Call.h"
#include "Subscriber.h"
#include <stdexcept>

namespace AcademyBilling
{
    bool isNumberValid(const std::string&);

    Call::Call(const std::string& aCaller,const std::string& aCallee,const time_t& aTime,const unsigned int& aDuration)
    {
        setCallerNumber(aCaller);
        setCalleeNumber(aCallee);
        setTime(aTime);
        setDuration(aDuration);
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
        if (isNumberValid(str)) 
        {
            calleeNumber = str;
        }
        else
        {
            throw std::invalid_argument("Callee number is bad");
        }
    }

    void Call::setCallerNumber(const std::string& str)
    {
        if (isNumberValid(str)) 
        {
            callerNumber = str;
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

    void Call::setTime(const time_t& aTime)
    {
        time = aTime;
    }

    unsigned int Call::getDuration() const
    {
        return duration;
    }

    void Call::setDuration(const unsigned int& aDuration)
    {
        duration = aDuration;
    }
   
}