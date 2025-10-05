// Copyright 2025 Sara Saad

/**
 * @file : Portfolio.hpp
 * @brief: Manages a collection of bank accounts and processes batch financial
 * transactions.
 *
 * The Portfolio class acts as a container and manager for multiple IAccount
 * instances,such as CheckingAccount and SavingAccount. It allows adding
 * accounts, retrieving themby ID, applying batches of transactions, executing
 * transfers between accounts, and calculating the total exposure (likely sum of
 * all balances or risk). It also supports batch operations for efficiency, such
 * as applying multiple transactionsat once or importing transaction data from
 * structured sources (like ledgers). Internally, it maintains a mapping of
 * account IDs to account objects and tracks a batch-level audit log for
 * operations.
 *
 */
#ifndef _HOME_SARA_DOCUMENTS_ROBOBANKPORTFOLIO_INC_PORTOFILO_HPP_
#define _HOME_SARA_DOCUMENTS_ROBOBANKPORTFOLIO_INC_PORTOFILO_HPP_

/**************************************************** include Part
 * ******************************************** */
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../Inc/IAccount.hpp"
#include "../Inc/Types.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************** Class Part
 * *********************************************** */
/**
    * @class: Portfolio
    * @brief: A manager for a portfolio of bank accounts and financial
   transactions.
    *
    * This class serves as the core container for managing multiple accounts in
   a banking system.
    *
    * It provides functionality to:
        - Add and retrieve individual accounts.
        - Apply transactions (deposits, withdrawals, fees, etc.) to accounts
   either individually or in batches.
        - Perform money transfers between accounts.
        - Compute aggregate metrics like total exposure (e.g., total balance
   across accounts).
        - Maintain an internal audit log for batch operations.
    *
    * The accounts are stored in an unordered_map for fast lookup by account
   ID,and each account is owned via a std::unique_ptr for safe memory
   management.
    *
    */
class Portfolio {
 private:
  std::unordered_map<std::string, std::unique_ptr<IAccount>>
      accounts_;  ///< Map of account IDs to account instances.
  std::vector<TxRecord>
      batch_audit_;  ///< Internal log of batch-applied transactions.
  /**
   * @brief   : Apply a single transaction record to the appropriate account.
   * @param tx: The transaction record to apply.
   *
   * @details:
   * This helper method locates the target account using the transaction's
   *account ID, and invokes the appropriate Apply() method on the IAccount
   *interface. It is used internally by batch operations like ApplyAll() and
   *ApplyFromLedger().
   *
   */
  void ApplyTx(const TxRecord &tx);

 public:
  /**
   * @brief    : Add a new account to the portfolio.
   * @param acc: Unique pointer to the account to be added.
   *
   * @details:
   * Ownership of the account is transferred to the Portfolio.
   * The account is stored internally in the accounts_ map using its ID as the
   * key. If an account with the same ID already exists, behavior is undefined
   * (likely overwritten).
   *
   */
  void AddAccount(std::unique_ptr<IAccount> acc);
  /**
   * @brief : Get the number of accounts currently managed in the portfolio.
   * @return: size_t The count of accounts.
   *
   */
  size_t CountAccounts();

  IAccount* GetAccount(const std::string &id) const;
  /**
   * @brief    : Apply a list of transactions to their respective accounts.
   * @param txs: Vector of transaction records to apply.
   *
   * @details:
   * Iterates through the provided transactions and applies each one to the
   * corresponding account using ApplyTx(). Useful for bulk processing.
   *
   */
  void ApplyAll(const std::vector<TxRecord> &txs);

  /**

  * @brief: Apply a series of transactions from structured ledger data.
  * @param account_ids: Array of account IDs for each transaction.
  * @param tx_types   : Array of transaction types (mapped internally or used
  for routing).
  * @param amounts    : Array of transaction amounts in cents.
  * @param count      : The number of transactions (length of the above arrays).
  *
  * @details
  *This method constructs and applies transactions in a lightweight way using
  parallel arrays for account IDs, transaction types, and amounts.
  * Likely used to import transactions from external ledgers or batch files.
  * The actual TxRecord construction is handled internally.
  *
  */
  void ApplyFromLedger(const std::string *account_ids, const int32_t *tx_types,
                       const int64_t *amounts, int count);
  /**
   * @brief: Transfer funds between two accounts.
   * @param txr: The transfer record containing source, destination, amount,
   * etc.
   * @return   : bool True if the transfer succeeded, false otherwise.
   *
   * @details:
   * Executes a funds transfer between two accounts. Likely validates inputs,
   * checks balances, and records the transaction in both accounts' audit logs.
   * The TransferRecord type is assumed to contain from/to account IDs, amount,
   * timestamp, etc.
   *
   */
  bool Transfer(TransferRecord txr);
  /**
   * @brief : Calculate the total exposure across all accounts.
   * @return: long long The aggregated exposure value in cents.
   *
   * @details:
   * "Exposure" typically refers to the total balance or risk-weighted value of
   * all accounts in the portfolio. This method sums up the balances (or another
   * exposure metric) from all managed accounts.
   *
   */
  int64_t TotalExposure() const;
};
#endif  // _HOME_SARA_DOCUMENTS_ROBOBANKPORTFOLIO_INC_PORTOFILO_HPP_
