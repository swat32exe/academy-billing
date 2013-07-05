#include "DefaultBillingRules.h"
#include "Subscriber.h"

namespace AcademyBilling
{
    DefaultBillingRules::DefaultBillingRules(void)
        :freeMinutesSinceLastCredit(30)
    {
    }

    DefaultBillingRules::~DefaultBillingRules(void)
    {
    }

    int DefaultBillingRules::chargeForCall(Subscriber &subscriber, const Call &call)
    {
        
        int callDuration = call.getDuration();
        time_t callTime = call.getTime();
        std::string number = call.getCalleeNumber();

        // Free minutes will be modified implicitly.
        AcademyBilling::DefaultBillingRuleBlockCallInfo callInfo(callDuration, callTime, lastCreditTime, freeMinutesSinceLastCredit, number);
        
        int callCost = defaultBillingRulesRuleset.calculateCallCost(callInfo);
        subscriber.charge(callCost);

        return callCost;
    }

    int DefaultBillingRulesRuleset::calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo)
    {
        return firstRuleBlock->calculateCallCost(callInfo);
    }

    DefaultBillingRulesRuleset::DefaultBillingRulesRuleset()
    {
        std::vector<std::string> insideNetworkPrefixes;
        insideNetworkPrefixes.push_back("050");
        insideNetworkPrefixes.push_back("066");
        insideNetworkPrefixes.push_back("095");
        insideNetworkPrefixes.push_back("099");

        // Last block in sequence.
        std::auto_ptr<DefaultBillingRuleBlock> stop(new DefaultBillingRuleBlockStop());

        // Charge fixed fee 0.95 and stop processing.
        std::auto_ptr<DefaultBillingRuleBlock> fixedMinuteFeeOutsideNetwork(new DefaultBillingRuleBlockChargeFixedMinuteFee(95, stop));

        // Charge fixed fee 0.50 and stop processing.
        std::auto_ptr<DefaultBillingRuleBlock> fixedMinuteFeeInsideNetwork(new DefaultBillingRuleBlockChargeFixedMinuteFee(50, stop));
        // Use free minutes, that were provided after last refill. If not enough go to fixedMinuteFeeInsideNetwork rule.
        std::auto_ptr<DefaultBillingRuleBlock> freeMinutesAfterCredit(new DefaultBillingRuleBlockFreeMinutesAfterCredit(30*24*60*60, fixedMinuteFeeInsideNetwork));
        // Use 5 free minutes, if it's weekend.
        std::auto_ptr<DefaultBillingRuleBlock> weekendFreeMinutes(new DefaultBillingRuleBlockWeekendFreeMinutes(5,freeMinutesAfterCredit));

        // Select rules according ro called subscriber network.
        std::auto_ptr<DefaultBillingRuleBlock> networkTypeSplitter(new DefaultBillingRuleBlockNetworkTypeSplitter(insideNetworkPrefixes,weekendFreeMinutes,fixedMinuteFeeOutsideNetwork));
        // Fixed connection fee.
        firstRuleBlock =  std::auto_ptr<DefaultBillingRuleBlock>(new DefaultBillingRuleBlockConnectionFee(33,networkTypeSplitter));
    }
}
