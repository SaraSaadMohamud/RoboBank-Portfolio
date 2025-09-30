#ifndef _CALCULATOR_HPP_
#define _CALCULATOR_HPP_

class Calculator
{
    public:
    
    static long long deposit(long long balance, long long amount);

    static long long withdraw(long long balance, long long amount);

    static long long fee(long long balance, long long fee_amount);

    static long long interest(long long balance, double apr, int days, int basis);

};

#endif //_CALCULATOR_HPP_