#include "DefaultBillingRuleBlocks.h"
#include <regex>
#include <vector>
#include <string>

namespace AcademyBilling
{
    class DefaultBillingRules;

    DefaultBillingRuleBlockCallInfo::DefaultBillingRuleBlockCallInfo(int callDuration, time_t callTime, time_t lastRefillTime, int &freeMinutesSinceLastCredit, std::string number) :
        callDuration(callDuration)
        ,callTime(callTime)
        ,lastRefillTime(lastRefillTime)
        ,freeMinutesSinceLastCredit(freeMinutesSinceLastCredit)
        ,number(number)
    {
    }

    DefaultBillingRuleBlockConnectionFee::DefaultBillingRuleBlockConnectionFee(const int fee, std::auto_ptr<DefaultBillingRuleBlock> &next) :
        fee(fee)
        ,next(next)
    {
    }

    int DefaultBillingRuleBlockConnectionFee::calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo) const
    {
        return fee + next->calculateCallCost(callInfo);
    }

    DefaultBillingRuleBlockWeekendFreeMinutes::DefaultBillingRuleBlockWeekendFreeMinutes(const int minutesAmount, std::auto_ptr<DefaultBillingRuleBlock> &next) :
        minutesAmount(minutesAmount)
        ,next(next)
    {
    }

    int DefaultBillingRuleBlockWeekendFreeMinutes::calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo) const
    {
        tm timeInfo;
        localtime_s(&timeInfo, &callInfo.callTime);
        int weekDay=timeInfo.tm_wday;
        bool itIsWeekend = (weekDay == 0) || (weekDay == 6);

        if(itIsWeekend)
        {
            if (callInfo.callDuration <= 60*minutesAmount)
                return 0;

            callInfo.callDuration -= 60*minutesAmount;
        }
        return next->calculateCallCost(callInfo);
    }

    DefaultBillingRuleBlockFreeMinutesAfterCredit::DefaultBillingRuleBlockFreeMinutesAfterCredit(int minutesValidTime, std::auto_ptr<DefaultBillingRuleBlock> &next) :
        minutesValidTime(minutesValidTime)
        ,next(next)
    {
    }

    int DefaultBillingRuleBlockFreeMinutesAfterCredit::calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo) const
    {
        // If minutes still valid.
        if((callInfo.callTime - callInfo.lastRefillTime) > minutesValidTime)
        {
            if (callInfo.callDuration <= callInfo.freeMinutesSinceLastCredit * 60) {
                // If call length was 1:01 take 2 minutes anyway.
                callInfo.freeMinutesSinceLastCredit -= (callInfo.callDuration + 59) / 60;
                return 0;
            }
        
            callInfo.callDuration -= callInfo.freeMinutesSinceLastCredit * 60;
            callInfo.freeMinutesSinceLastCredit = 0;
        }
        return next->calculateCallCost(callInfo);
    }
    
    DefaultBillingRuleBlockNetworkTypeSplitter::DefaultBillingRuleBlockNetworkTypeSplitter(const std::vector<std::string> &insidePrefixes, std::auto_ptr<DefaultBillingRuleBlock> &nextInside, std::auto_ptr<DefaultBillingRuleBlock> &nextOutside) :
        insidePrefixes(insidePrefixes)
        ,nextInside(nextInside)
        ,nextOutside(nextOutside)
    {
    }

    int DefaultBillingRuleBlockNetworkTypeSplitter::calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo) const
    {
        // Number should be in format +xx(xxx)xxxxxxx.
        for(auto i = insidePrefixes.begin(); i!= insidePrefixes.end(); ++i){
            std::string expression = ".*(";
            expression += *i;
            expression += ").*";
            std::regex e(expression);
            if (std::regex_match (callInfo.number,e))
                return nextInside->calculateCallCost(callInfo);
        }
        return 0;
    }
    
    DefaultBillingRuleBlockChargeFixedMinuteFee::DefaultBillingRuleBlockChargeFixedMinuteFee(int fee, std::auto_ptr<DefaultBillingRuleBlock> &next) :
        fee(fee)
        ,next(next)
    {
    }

    int DefaultBillingRuleBlockChargeFixedMinuteFee::calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo) const
    {
        int callDurationInMinutes = (callInfo.callDuration + 59)/60;
        return callDurationInMinutes * fee + next->calculateCallCost(callInfo);
    }

    int DefaultBillingRuleBlockStop::calculateCallCost(DefaultBillingRuleBlockCallInfo &callInfo) const
    {
        return 0;
    }
}
