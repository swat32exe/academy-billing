#ifndef _REFILL_H
#define _REFILL_H

#include <time.h>

namespace AcademyBilling
{
    class Refill
    {
    private:    
        int money;
        time_t time;
    public:    
        Refill(const int&, const time_t&);
        Refill(const Refill&);
        ~Refill(void);
        int getMoney() const;
        void setMoney(const int&);
        time_t getTime() const;
        void setTime(const time_t&);
        Refill& operator=(const Refill&);
    };
}

#endif