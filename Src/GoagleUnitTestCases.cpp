#include "Calculator.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include "IAccount.hpp"
#include  "Portofilo.hpp"

TEST(CalculatorTest,DepositTest)
{
    Calculator mycal;
    int balance = 100;
    int add = 500;

    ASSERT_GT(add,0);
    int Sum = mycal.Deposit(balance,add);

    EXPECT_TRUE(Sum == balance+ add);
}

TEST (CalculatorTest,WithdrawTest)
{
    Calculator mycal;
    int balance = 1000;
    int amount = 500;

    ASSERT_LT(amount,balance);

    int Sub = mycal.Withdraw(balance,amount);
    EXPECT_TRUE(Sub == balance - amount);

}

TEST (CalculatorTest, FeeTest)
{
    Calculator mycal;
    int balance = 10;
    int amount = 500;

    int res = mycal.Fee(balance,amount);
    ASSERT_EQ(res,balance-amount);
}

TEST (CalculatorTest,InterestTest)
{
    Calculator mycal;

    long long int balance = 10000;
    double Percent = 0.05;
    int years = 30;
    int basis = 365;

    ASSERT_GT(balance,0);

    int res = mycal.Interest(balance,Percent,years,basis);
    EXPECT_TRUE(res == 41);


}

TEST(SavingAccountTest,GetIDTest)
{
    SavingAccount ckAcc("ACC001", 0.05, 50000);

    std::string id = ckAcc.GetId();
    ASSERT_STREQ(id.c_str(),"ACC001");

}

TEST(CheckingAccountTest, GetIDTest)
{
    CheckingAccount ckAcc("CHK001", 200, 100000); 
    std::string id = ckAcc.GetId();

    ASSERT_STREQ(id.c_str(), "CHK001");
}

TEST(CheckingAccountTest, GetBalanceTest)
{
    CheckingAccount ckAcc("CHK001", 200, 100000);
    int res = ckAcc.GetBalance();
    ASSERT_EQ(res,100000);
}


TEST(CheckingAccountTest, GetTypeTest)
{
    CheckingAccount ckAcc("CHK001", 200, 100000);
    AccountType type = ckAcc.GetType();

    ASSERT_EQ(type, AccountType::KCHECKING);
}


TEST(PortfolioTest, GetAccount_ValidId)
{
    Portfolio portfolio;

    auto acc = std::make_unique<CheckingAccount>("CHK001", 100, 50000);
    std::string id = acc->GetId();

    portfolio.AddAccount(std::move(acc));

    IAccount* found = portfolio.GetAccount("CHK001");

    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->GetId(), id);
}

TEST(PortfolioTest, GetAccount_InvalidId)
{
    Portfolio portfolio;

    auto acc = std::make_unique<CheckingAccount>("CHK001", 100, 50000);
    portfolio.AddAccount(std::move(acc));

    IAccount* found = portfolio.GetAccount("INVALID_ID");
    EXPECT_EQ(found, nullptr);
}


int main (int argc, char *argv[])
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
