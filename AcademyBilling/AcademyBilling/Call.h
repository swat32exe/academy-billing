#ifndef _CALL_H
#define _CALL_H

#include <string>
#include <time.h>

namespace AcademyBilling
{
    class Call
    {
    private:
        std::string callerNumber;
        std::string calleeNumber;
        time_t time;
        unsigned int duration;
    public:
        Call(const std::string&, const std::string&, const time_t&, const unsigned int&);
        ~Call(void);
        std::string getCallerNumber() const;
        void setCallerNumber(const std::string&);
        std::string getCalleeNumber() const;
        void setCalleeNumber(const std::string&);
        time_t getTime() const;
        void setTime(const time_t&);
        unsigned int getDuration() const;
        void setDuration(const unsigned int&);
    };
}

#endif