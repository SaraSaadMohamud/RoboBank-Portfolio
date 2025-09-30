#include "Calculator.hpp"

long long Calculator::deposit(long long balance, long long amount)
{
    return balance + amount;
}

long long Calculator::withdraw(long long balance, long long amount)
{
    return balance - amount;
}

long long Calculator::fee(long long balance, long long fee_amount)
{
    return balance - fee_amount;
}

long long Calculator::interest(long long balance, double apr, int days, int basis)
{
    double fraction = (static_cast<double>(days) / basis);
    double interest_value = balance * apr * fraction;

    return static_cast<long long> (interest_value);
}