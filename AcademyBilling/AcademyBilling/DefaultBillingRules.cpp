#include "DefaultBillingRules.h"


DefaultBillingRules::DefaultBillingRules(void)
{
}


DefaultBillingRules::~DefaultBillingRules(void)
{
}

int DefaultBillingRules::chargeForCall(Subscriber &subscriber, const Call &call) const
{
    return 0;
}
