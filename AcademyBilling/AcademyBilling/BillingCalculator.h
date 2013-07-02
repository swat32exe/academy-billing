#pragma once
#include "Subscriber.h"
#include "Call.h"
#include<vector>

class BillingCalculator
{
public:
    BillingCalculator(void);
    ~BillingCalculator(void);

    //Updates subscribers, according to calls
    void calculateBills(std::vector<Subscriber> & subscribers, const std::vector<Call> &calls) const;
};

