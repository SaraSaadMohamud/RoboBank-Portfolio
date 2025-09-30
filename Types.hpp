/** @file accounts.hpp
 *  @brief Defines account types, transactions, and the main Account class.
 */

#ifndef _ACCOUNTS_HPP_
#define _ACCOUNTS_HPP_

/******************************************** Include Part ​***************************************** */
#include <string>
#include "Calculator.hpp"

/******************************************** Macros Part ​****************************************** */

#define kMaxAudit   256  ///< Maximum number of audit records per account

enum class  AccountType
{
    Checking = 0,            ///< Regular checking account

    Savings                  ///< Savings account with possible interest

};

enum class TxKind
{
    Deposit = 0,             ///< Money deposited into the account

    Withdrawal,              ///< Money withdrawn from the account

    Fee,                     ///< Fee charged to the account

    Interest,                ///< Interest credited to the account

    TransferIn,              ///< Money transferred into this account from another.

    TransferOUT              ///< Money transferred out of this account to another.

} ;

struct AccountSettings
{
    AccountType AccountType;  ///< Type of the account

    double apr;               ///< Annual Percentage Rate (interest rate)

    long long fee_flat_cents; ///< Flat fee amount in cents
};

struct  TxRecord
{
    TxKind kind;              ///< Type of transaction

    long long amount_cents;   ///< Transaction amount in cents

    long long timestamp;      ///< When the transaction occurred

    const char* note;         ///< Optional description or note

    std::string account_id;   ///< The unique identifier of the account involved in the transaction.
};


struct TransferRecord

{

    std::string from_id;      ///< The ID of the account from which funds are transferred.

    std::string to_id;        ///< The ID of the account receiving the funds.

    long long amount_cents;   ///< The amount transferred, in cents.

    long long timestamp;      ///< The time at which the transfer occurred.

    std::string note;         ///< Optional note describing the purpose or details of the transfer.

};

#endif 