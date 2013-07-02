#include "BillingCalculator.h"

AcademyBilling::BillingCalculator::BillingCalculator(void)
{
}

AcademyBilling::BillingCalculator::~BillingCalculator(void)
{
}

void AcademyBilling::BillingCalculator::setSubscrberStorage(std::shared_ptr<SubscriberStorage> subscriberStorage) const
{
}

void AcademyBilling::BillingCalculator::chargeForSingleCall(const AcademyBilling::Call& call)
{
}

void AcademyBilling::BillingCalculator::chargeForMultipleCalls(std::vector<AcademyBilling::Call>& call)
{
}
