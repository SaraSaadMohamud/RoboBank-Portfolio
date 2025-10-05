// Copyright 2025 Sara Saad

/**
 * @file : Calculator.hpp
 * @brief: Utility class for performing common financial calculations related to
 *banking operations.
 *
 *The Calculator class provides static utility methods to perform basic
 *financial operations such as deposits, withdrawals, fees, and interest
 *calculations. All methods are stateless and operate purely on their input
 *parameters, making them thread-safe and easily testable. These utilities are
 *commonly used by account management systems to update balances, and apply
 *financial transactions.
 *
 */

#ifndef _HOME_SARA_DOCUMENTS_ROBOBANKPORTFOLIO_INC_CALCULATOR_HPP_
#define _HOME_SARA_DOCUMENTS_ROBOBANKPORTFOLIO_INC_CALCULATOR_HPP_

/**
* @class: Calculator
* @brief: Provides static methods for common financial calculations.
*
*This is a utility class containing only static methods. It is not meant to be
instantiated.
*
* Each method performs a specific financial computation:
    - Deposit: Computes the new balance after adding funds.
    - Withdraw: Computes the new balance after subtracting funds.
    - Fee: Computes the new balance after deducting a fee.
    - Interest: Computes interest earned over a period and returns the updated
balance.
*
*/
#include <cstdint>
#include <string>

class Calculator {
 public:
  /**
   * @brief: Calculate the new balance after a deposit.
   * @param balance: The current balance in cents.
   * @param amount : The amount to deposit, in cents.
   * @return: long long The new balance after the deposit.
   *
   * @details:
   * This method simply adds the deposit amount to the current balance.
   * It assumes the amount is valid and non-negative.
   * @example:
   * long long newBalance = Calculator::Deposit(10000, 5000); // 10000 + 5000 =
   * 15000
   *
   */
  static int64_t Deposit(int64_t balance, int64_t amount);

  /**
   *
   * @brief Calculate the new balance after a withdrawal.
   * @param balance: The current balance in cents.
   * @param amount : The amount to withdraw, in cents.
   * @return :long long The new balance after the withdrawal.
   * @details:
   * This method subtracts the withdrawal amount from the current balance.
   * It assumes the amount is valid and that sufficient funds may exist (not
   * enforced here).
   * @example:
   * long long newBalance = Calculator::Withdraw(15000, 3000); ///< 15000 - 3000
   * = 12000
   *
   */
  static int64_t Withdraw(int64_t balance, int64_t amount);

  /**
   * @brief: Calculate the new balance after deducting a fee.
   * @param balance   : The current balance in cents.
   * @param fee_amount: The fee amount to deduct, in cents.
   * @return: long long The new balance after the fee deduction.
   * @details:
   * This method subtracts a fixed fee amount from the balance.
   * Typically used for monthly maintenance fees or transaction charges.
   * @example:
   * long long newBalance = Calculator::Fee(10000, 100); // 10000 - 100 = 9900
   *
   */
  static int64_t  Fee(int64_t balance, int64_t fee_amount);

  /**
  * @brief: Calculate the new balance after applying simple interest.
  * @param balance: The current balance in cents.
  * @param apr    : The annual percentage rate (as a decimal, e.g., 0.05 for
  5%).
  * @param days   : The number of days the interest is applied over.
  * @param basis  : The number of days in the year for interest calculation
  (e.g., 360 or 365).
  *
  * @return : long long The new balance after adding the interest, in cents.
  * @details:
  * This method calculates simple interest using the formula:
      \f[
      \text{Interest} = \text{balance} \times \frac{\text{apr} \times
  \text{days}}{\text{basis}} \f]
  * The resulting interest is added to the balance, and the total is returned as
  cents.
  * All values are handled in integer arithmetic (cents), so precision is
  limited accordingly.
  * @example:
  // For 10000 cents (100.00 USD), 5% APR, 30 days, 360 day basis:
  // Interest = 10000 * (0.05 * 30 / 360) = 10000 * 0.0041667 ≈ 41.67 cents
  // New balance ≈ 10041 cents
  long long newBalance = Calculator::Interest(10000, 0.05, 30, 360);
  *
  */
  static int64_t Interest(int64_t balance, double apr, int32_t days,
                            int32_t basis);
};

#endif  // _HOME_SARA_DOCUMENTS_ROBOBANKPORTFOLIO_INC_CALCULATOR_HPP_
