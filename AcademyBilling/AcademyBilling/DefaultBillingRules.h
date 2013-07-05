#pragma once
#include "BillingRules.h"
#include "DefaultBillingRuleBlocks.h"
#include <memory>

namespace AcademyBilling
{
    class DefaultBillingRulesRuleset;

    class DefaultBillingRules :
        public BillingRules
    {
        int freeMinutesSinceLastCredit;
        time_t lastCreditTime;
        static DefaultBillingRulesRuleset defaultBillingRulesRuleset;

    public:
        DefaultBillingRules(void);
        ~DefaultBillingRules(void);
        int chargeForCall(Subscriber &subscriber, const Call &call);
    };

    class DefaultBillingRulesRuleset
    {
        std::auto_ptr<DefaultBillingRuleBlock> firstRuleBlock;
    public:
        int calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo);
        DefaultBillingRulesRuleset();
    };
}
