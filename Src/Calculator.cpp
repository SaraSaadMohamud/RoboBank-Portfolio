// Copyright 2025 Sara Saad

/********************************************include
 * part*************************************************** */
#include "../Inc/Calculator.hpp"

//////////////////////////////////////////////////////////////////

int64_t Calculator::Deposit(int64_t balance, int64_t amount) {
  return balance + amount;
}

int64_t Calculator::Withdraw(int64_t balance, int64_t amount) {
  return balance - amount;
}

int64_t Calculator::Fee(int64_t balance, int64_t fee_amount) {
  return balance - fee_amount;
}

int64_t Calculator::Interest(int64_t balance, double apr, int32_t days,
                               int32_t basis) {
  double fraction = (static_cast<double>(days) / basis);
  double interest_value = balance * apr * fraction;

  return static_cast<int64_t>(interest_value);
}