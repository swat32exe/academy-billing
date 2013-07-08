#include "Call.h"
#include "Subscriber.h"

#include <stdexcept>

namespace AcademyBilling
{
    bool isNumberValid(const std::string&);

    Call::Call(const std::string &callerNumber, const std::string &calleeNumber, const time_t &time, const unsigned int &duration)
        :time(time)
        ,duration(duration)
    {
        setCallerNumber(callerNumber);
        setCalleeNumber(calleeNumber);
    }

    Call::~Call(void)
    {
    }

    std::string Call::getCallerNumber() const
    {
        return this->callerNumber;
    }

    std::string Call::getCalleeNumber() const
    {
        return this->calleeNumber;
    }

    void Call::setCalleeNumber(const std::string &calleeNumber)
    {
        if (isNumberValid(calleeNumber)) 
            this->calleeNumber = calleeNumber;
        else
            throw std::invalid_argument("Caller number is bad");
    }

    void Call::setCallerNumber(const std::string &callerNumber)
    {
        if (isNumberValid(callerNumber)) 
            this->callerNumber = callerNumber;
        else
            throw std::invalid_argument("Caller number is bad");
    }

    time_t Call::getTime() const
    {
        return this->time;
    }

    void Call::setTime(const time_t &time)
    {
        this->time = time;
    }

    unsigned int Call::getDuration() const
    {
        return this->duration;
    }

    void Call::setDuration(const unsigned int &duration)
    {
        this->duration = duration;
    }
   
}