// Copyright 2025 Sara Saad

/**
    * @file : accounts.hpp
    * @brief: Central definitions for account types, transaction kinds,
   settings, and transaction records.
    *
    * This header file defines the foundational data structures and enumerations
   used throughout thebanking/account management system.
    * It includes:
        - The AccountType enumeration to distinguish between account categories
   (e.g., Checking, Savings).
        - The TxKind enumeration to classify different kinds of financial
   transactions.
        - The AccountSettings structure to hold configurable properties of an
   account (e.g., APR, fees).
        - The TxRecord structure to represent individual financial transactions
   with metadata.
        - The TransferRecord structure to describe money movements between
   accounts. *These definitions are used by classes such as IAccount,
   BaseAccount, and Portfolio tostandardize how accounts behave, how
   transactions are recorded, and how data is exchanged across the system.
    *
    */

#ifndef _HOME_SARA_DOCUMENTS_ROBOBANKPORTFOLIO_INC_TYPES_HPP_
#define _HOME_SARA_DOCUMENTS_ROBOBANKPORTFOLIO_INC_TYPES_HPP_

/******************************************** Include Part
 * ​***************************************** */
#include <cstdint>
#include <string>

#include "../Inc/Calculator.hpp"
/******************************************** Macros Part
 * ​****************************************** */
/**
 * @def  : kMAXAUDIT
 * @brief: Maximum number of audit records allowed per account.
 * This constant defines an upper limit on how many transaction records can be
 * stored in an account's audit log. It helps control memory usage and prevent
 * unbounded growth.
 *
 */
#define kMAXAUDIT 256

/**
 * @enum : AccountType
 * @brief: Specifies the type of a bank account.
 *
 * Different account types may have different behaviors, such as earning
 * interest or being subject to fees. This enum is used in AccountSettings and
 * IAccount::GetType().
 *
 */
enum class AccountType {
  KCHECKING = 0,  ///< A standard checking account, typically for everyday use
                  ///< with no interest.

  KSAVINGS  ///< A savings account, which may earn interest over time.t
};

/**
 * @enum : TxKind
 * @brief: Defines the various types of financial transactions that can occur on
 * an account. Each transaction kind represents a distinct action such as a
 * deposit, withdrawal,fee charge, interest credit, or transfer. Used in
 * TxRecord::kind to categorize transactions.
 *
 */
enum class TxKind {
  KDEPOSIT = 0,  ///< Money deposited into the account

  KWITHDRAWAL,  ///< Money withdrawn from the account

  KFEE,  ///< Fee charged to the account

  KINTEREST,  ///< Interest credited to the account

  KTRANSFERIN,  ///< Money transferred into this account from another.

  KTRANSFEROUT,  ///< Money transferred out of this account to another.
};

/**
 * @struct: AccountSettings
 * @brief : Holds configurable parameters and properties for a bank account.
 * This structure is typically used to initialize or describe the behavior and
 * features of an account, such as its type, interest rate (APR), and any flat
 * fees.
 *
 */
struct AccountSettings {
  AccountType account_type;  ///< Type of the account

  double apr;  ///< Annual Percentage Rate (interest rate)

  int64_t fee_flat_cents;  ///< Flat fee amount in cents
};

/**
 * @struct: TxRecord
 * @brief : Represents a single financial transaction performed on an account.
 * This structure encapsulates all necessary details about a transaction,
 * including the type, amount, timestamp, optional note, and the associated
 * account ID. TxRecords are used for auditing, applying changes, and recording
 * history.
 */
struct TxRecord {
  TxKind kind;  ///< Type of transaction

  int64_t amount_cents;  ///< Transaction amount in cents

  int64_t timestamp;  ///< When the transaction occurred

  const char *note;  ///< Optional description or note

  std::string account_id;  ///< The unique identifier of the account involved in
                           ///< the transaction.
};

/**
 * @struct TransferRecord
 * @brief Describes a transfer of funds from one account to another.
 * Used to represent a transaction where money is moved between two different
 * accounts, such as from a source (from_id) to a destination (to_id). Includes
 * metadata like timestamp and optional note.
 *
 */
struct TransferRecord {
  std::string
      from_id;  ///< The ID of the account from which funds are transferred.

  std::string to_id;  ///< The ID of the account receiving the funds.

  int64_t amount_cents;  ///< The amount transferred, in cents.

  int64_t timestamp;  ///< The time at which the transfer occurred.

  std::string note;  ///< Optional note describing the purpose or details of the
                     ///< transfer.
};

#endif  // _HOME_SARA_DOCUMENTS_ROBOBANKPORTFOLIO_INC_TYPES_HPP_
