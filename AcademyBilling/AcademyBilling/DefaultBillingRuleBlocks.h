#pragma once
#include "BillingRules.h"
#include <vector>
#include <string>

namespace AcademyBilling
{
    class DefaultBillingRules;

    /** Structure storing all information, necessary for ruleBlocks to process call.
    *   Might be modified during processing
    */
    struct DefaultBillingRuleBlockCallInfo
    {
        int callDuration;
        time_t callTime;
        time_t lastRefillTime;
        int &freeMinutesSinceLastCredit;
        std::string number;

        DefaultBillingRuleBlockCallInfo(int callDuration, time_t callTime, time_t lastRefillTime, int &freeMinutesSinceLastCredit, std::string number);
    };

    class DefaultBillingRules;
    
    /** Rule block interface. 
    *   Each block may do some partial call cost calculation and then invoke next block.
    */
    class DefaultBillingRuleBlock
    {
    public:
        virtual int calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo) const =0;
    };

    class DefaultBillingRuleBlockConnectionFee :
        public DefaultBillingRuleBlock
    {
        int fee;
        std::auto_ptr<DefaultBillingRuleBlock> next;
    public:
        DefaultBillingRuleBlockConnectionFee(const int fee, std::auto_ptr<DefaultBillingRuleBlock> &next);
        int calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo) const;
    };

    class DefaultBillingRuleBlockWeekendFreeMinutes :
        public DefaultBillingRuleBlock
    {
        int minutesAmount;
        std::auto_ptr<DefaultBillingRuleBlock> next;
    public:
        DefaultBillingRuleBlockWeekendFreeMinutes(const int minutesAmount, std::auto_ptr<DefaultBillingRuleBlock> &next);
        int calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo) const;
    };

    class DefaultBillingRuleBlockFreeMinutesAfterCredit :
        public DefaultBillingRuleBlock
    {
        std::auto_ptr<DefaultBillingRuleBlock> next;
        int minutesValidTime;
    public:
        DefaultBillingRuleBlockFreeMinutesAfterCredit(int minutesValidTime, std::auto_ptr<DefaultBillingRuleBlock> &next);
        int calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo) const;
    };

    class DefaultBillingRuleBlockNetworkTypeSplitter :
        public DefaultBillingRuleBlock
    {
        std::auto_ptr<DefaultBillingRuleBlock> nextInside;
        std::auto_ptr<DefaultBillingRuleBlock> nextOutside;
        std::vector<std::string> insidePrefixes;
    public:
        DefaultBillingRuleBlockNetworkTypeSplitter(const std::vector<std::string> &insidePrefixes, std::auto_ptr<DefaultBillingRuleBlock> &nextInside, std::auto_ptr<DefaultBillingRuleBlock> &nextOutside);
        int calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo) const;
    };

    class DefaultBillingRuleBlockChargeFixedMinuteFee :
        public DefaultBillingRuleBlock
    {
        int fee;
        std::auto_ptr<DefaultBillingRuleBlock> next;
    public:
        DefaultBillingRuleBlockChargeFixedMinuteFee(int fee, std::auto_ptr<DefaultBillingRuleBlock> &next);
        int calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo) const;
    };

    class DefaultBillingRuleBlockStop :
        public DefaultBillingRuleBlock
    {
    public:
        int calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo) const;
    };
}
