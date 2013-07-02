#include "DefaultBillingRules.h"

AcademyBilling::DefaultBillingRules::DefaultBillingRules(void)
{
}

AcademyBilling::DefaultBillingRules::~DefaultBillingRules(void)
{
}

int AcademyBilling::DefaultBillingRules::chargeForCall(AcademyBilling::Subscriber &subscriber, const AcademyBilling::Call &call) const
{
    return 0;
}
