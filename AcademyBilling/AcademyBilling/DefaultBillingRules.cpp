#include "DefaultBillingRules.h"

#include "Subscriber.h"
#include "Utility.h"

namespace AcademyBilling
{
    DefaultBillingRules::DefaultBillingRules(void)
        :freeMinutesSinceLastCredit(freeMinutesSinceCreditAmount)
        ,lastCreditTime(0)
    {
    }

    DefaultBillingRules::~DefaultBillingRules(void)
    {
    }

    DefaultBillingRulesRuleset DefaultBillingRules::defaultBillingRulesRuleset;

    int DefaultBillingRules::chargeForCall(const Call &call, Subscriber &subscriber)
    {
        if (lastCreditTime != subscriber.getLastRefillTime()) {
            lastCreditTime = subscriber.getLastRefillTime();
            freeMinutesSinceLastCredit = freeMinutesSinceCreditAmount;
        }
        return defaultBillingRulesRuleset.chargeForCall(call, subscriber);
    }

    int DefaultBillingRulesRuleset::chargeForCall(Call call, Subscriber &subscriber)
    {
        return firstRuleBlock->chargeForCall(call,subscriber);
    }

    DefaultBillingRulesRuleset::DefaultBillingRulesRuleset()
    {
        firstRuleBlock =  std::auto_ptr<DefaultBillingRuleBlock>(
                            new DefaultBillingRuleBlockConnectionFee(
                            new DefaultBillingRuleBlockWeekendFreeMinutes(
                            new DefaultBillingRuleBlockFreeMinutesAfterCredit(
                            new DefaultBillingRuleBlockChargeFixedMinuteFee(NULL)))));
    }
}
