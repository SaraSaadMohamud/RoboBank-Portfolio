/********************************************include part*************************************************** */
#include "../Inc/Calculator.hpp"
//////////////////////////////////////////////////////////////////

long long Calculator::Deposit(long long balance, long long amount)
{
    return balance + amount;
}

long long Calculator::Withdraw(long long balance, long long amount)
{
    return balance - amount;
}

long long Calculator::Fee(long long balance, long long fee_amount)
{
    return balance - fee_amount;
}

long long Calculator::Interest(long long balance, double apr, int days, int basis)
{
    double fraction = (static_cast<double>(days) / basis);
    double interest_value = balance * apr * fraction;

    return static_cast<long long> (interest_value);
}