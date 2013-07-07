#include "DefaultBillingRulesTests.h"

#include <DefaultBillingRules.h>
#include <Call.h>
#include <Refill.h>

namespace AcademyBillingTesting
{
    TEST_F(DefaultBillingRulesTests, default_billing_rules_weekend_calls)
    {
        std::auto_ptr<AcademyBilling::DefaultBillingRules> rules(new AcademyBilling::DefaultBillingRules());

        // This day is Saturday.
        tm timeTm;
        timeTm.tm_year=2013-1900;
        timeTm.tm_mon = 00;
        timeTm.tm_mday = 05;
        timeTm.tm_hour = 00;
        timeTm.tm_min = 00;
        timeTm.tm_sec = 00;
        timeTm.tm_isdst = 0;
        
        time_t timeT = mktime(&timeTm);

        int balance = 5000;
        AcademyBilling::Subscriber subscriber("+38(095)0112233", balance, rules.get(), AcademyBilling::Refill(10,timeT-100)); 
        
        // 5 first free minutes on weekend cover it
        AcademyBilling::Call call1("+38(095)0112233", "+38(095)0112233", timeT, 10);
        rules->chargeForCall(call1, subscriber);
        // Only conection.
        balance -= 33;
        ASSERT_EQ(balance, subscriber.getBalance());

        // Exectly one minute to other network.
        AcademyBilling::Call call2("+38(095)0112233", "+38(062)0112233", timeT += 100, 60);
        rules->chargeForCall(call2, subscriber);
        // 33 - for connection, 95 - minute.
        balance -= (33 + 95);
        ASSERT_EQ(balance, subscriber.getBalance());

        // 5 first free minutes + 30 minutes after refill + 1 second.
        AcademyBilling::Call call3("+38(095)0112233", "+38(095)0112233", timeT += 3600, (5+30)*60+1);
        rules->chargeForCall(call3, subscriber);
        // 33 - for connection, 50 - minute.
        balance -= (33 + 50);
        ASSERT_EQ(balance, subscriber.getBalance());

        // 5 first free minutes + 61 second, when 30 minutes are used.
        AcademyBilling::Call call4("+38(095)0112233", "+38(095)0112233", timeT += 3600, 60*5 + 61);
        rules->chargeForCall(call4, subscriber);
        // 33 - for connection, 50*2 - for 2 minutes.
        balance -= (33 + 50*2);
        ASSERT_EQ(balance, subscriber.getBalance());

        // Refilling balance (100).
        AcademyBilling::Refill refill(100, timeT += 3600);
        subscriber.addRefill(refill);
        balance += 100;
        ASSERT_EQ(balance, subscriber.getBalance());

        // 5 first free minutes + 61 second, should be covered by free minutes
        AcademyBilling::Call call5("+38(095)0112233", "+38(095)0112233", timeT += 3600, 60*5 + 61);
        rules->chargeForCall(call5, subscriber);
        // 33 - for connection.
        balance -= 33;
        ASSERT_EQ(balance, subscriber.getBalance());
    }
}