#ifndef IACCOUNT_CPP_
#define IACCOUNT_CPP_

    /**
    * @file : IAccount.hpp
    * @brief: Interface and implementation for bank account system.
    *This header defines the core interfaces and base implementations for a banking system, that supports different types of accounts (e.g., Checking, Savings).
    * It includes an abstract interface (IAccount), a base implementation (BaseAccount), and derived classes (CheckingAccount, SavingAccount).
    * The system supports operations like deposits, withdrawals, fees, interest postings,and maintains an audit trail of transactions.
    * 
    */
/********************************************** include Part ***************************************** */
#include <vector>

#include "Types.hpp"
#include "Calculator.hpp"
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*********************************************** Macros Part **************************************** */
    /**
    * @def  : MAX_AUDIT
    * @brief: Maximum number of audit records to store per account.
    */
#define  MAX_AUDIT 256   
/********************************************* Classes Part ***************************************** */
/**
    * @class: IAccount
    * @brief: Abstract base class defining the interface for all account types.
    *
    * This interface declares the essential methods that all account types (e.g., Checking,Savings) must implement. 
    *I t includes methods for retrieving account information,
    * managing balance, recording transactions, and applying financial actions.
    * 
    */
class IAccount
{
    public:
    virtual ~IAccount();

    /**
    * @brief : Get the unique identifier of the account.
    * @return: std::string The account ID.
    */
    virtual std::string     GetId()        = 0; 

    /**
    * @brief : Get the type of the account (e.g., Checking or Savings).
    * @return: AccountType The type of account.
    */     
    virtual AccountType     GetType()      = 0; 

    /**
    * @brief : Get the account settings.
    / @return: AccountSettings The settings associated with the account.
    */     
    virtual AccountSettings GetSetting()   = 0;   

    /**
    * @brief : Get the current balance of the account in cents.
    * @return: long long The account balance in cents.
    */
    virtual long long GetBalance() const = 0;

    /**
    * @brief : Get the audit log of all transactions.
    * @return: const std::vector& Vector of transaction records.
    */
    virtual const std::vector<TxRecord>& GetAudit() = 0;

    /**
    * @brief: Deposit money into the account.
    * @param amount_cents: The amount to deposit, in cents.
    * @param ts          : Timestamp of the transaction.
    * @param note        : Optional note or description for the transaction.
    */
    virtual void Deposit(long long amount_cents, long long ts, const char* note) = 0; 

    /**
    * @brief: Withdraw money from the account.
    * @param amount_cents: The amount to withdraw, in cents.
    * @param ts          : Timestamp of the transaction.
    * @param note        : Optional note or description for the transaction.
    * 
    */              
    virtual void Withdraw(long long amount_cents, long long ts, const char* note) = 0;  

    /**
    * @brief: Charge a fee to the account.
    * @param fee_cents: The fee amount in cents.
    * @param ts       : Timestamp of the transaction.
    * @param note     : Optional note or description for the transaction.
    * 
    */
    virtual void ChargeFee(long long fee_cents, long long ts, const char* note) = 0; 

    /**
    * @brief: Post simple interest to the account.
    * @param days : Number of days the interest is calculated over.
    * @param basis: Interest basis (e.g., 360, 365).
    * @param ts   : Timestamp of the transaction.
    * @param note : Optional note or description for the transaction.
    * 
    */              
    virtual void PostSimpleInterest(int days, int basis, long long ts, const char* note) = 0; 

    /**
    * @brief   : Apply a transaction record to the account.
    * @param tx: The transaction record to apply.
    */   
    virtual void Apply(const TxRecord& tx) = 0;

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
    * @class: BaseAccount
    * @brief: Abstract base implementation of common account functionality.
    * This class provides reusable implementations for balance management,transaction auditing, and common operations,
     to be extended by concreteaccount types like CheckingAccount and SavingAccount.
    */
class BaseAccount : public IAccount
{
    protected:
    std::string id_;                ///< Unique account identifier
    AccountSettings setting_;       ///< Account configuration/settings
    long long balance_cent_;        ///< Current balance in cents
    std::vector<TxRecord> audit_;   ///< List of transaction records
    int audit_count_;               ///< Count of audits stored (up to MAX_AUDIT) 

    /**
    * @brief    : Record a transaction into the audit log.
    * @param rec:The transaction record to add.
    * 
    */
    void Record(const TxRecord& rec);

    /**
    * @brief: Update the account balance.
    * @param cents: The amount in cents to add (can be negative).
    * 
    */
    void UpdateBalance(long long cents);

    public:
    /**
    * @brief: Construct a new Base Account object
    * @param id            : The account identifier.
    * @param settings      :The initial settings for the account.
    * @param opening_balnce: The opening balance in cents.
    * 
    */
    BaseAccount(std::string id, AccountSettings settings, long long opening_balnce);
    
    std::string GetId();

    long long GetBalance() const;
    AccountSettings GetSetting() ;
    const std::vector<TxRecord>& GetAudit();

    void Deposit(long long amount_cents, long long ts, const char* note);                ///< Deposit money
    void Withdraw(long long amount_cents, long long ts, const char* note);               ///< Withdraw money
    void ChargeFee(long long fee_cents, long long ts, const char* note);                 ///< Charge a fee
    void PostSimpleInterest(int days, int basis, long long ts, const char* note);        ///< Post interest
    void Apply(const TxRecord& tx);

    /**
    * @brief : Get the type of the account.
    * @return: AccountType Must be implemented by derived classes.
    * 
    */
    virtual AccountType GetType()  = 0;
};
/**
    * @class: CheckingAccount
    * @brief: A checking account type with optional monthly fees.
    *
    *Inherits from BaseAccount and implements account type-specific behavior,such as applying a fixed monthly fee.
    */
class CheckingAccount : public BaseAccount
{
    public:
    /**
    * @brief: Construct a new Checking Account object
    * @param id             : The account ID.
    * @param fee_cents      : The monthly maintenance fee in cents.
    * @param opening_balance: The starting balance in cents.
    * 
    */
    CheckingAccount(std::string id, long long fee_centsm, long long opening_balance);

    /**
    * @brief : Get the type of the account (Checking).
    * @return: AccountType Always returns AccountType::CHECKING.
    * 
    */
    AccountType GetType();

    /**
    * @brief: Apply a monthly maintenance fee.
    * @param timestamp: The time when the fee is applied.
    * @param note     : Optional description.
    * 
    */
    void ApplyFee(long long timestamp,const char* note);
};
    /**
    * @class: SavingAccount
    * @brief: A savings account type that earns interest.
    *
    * Inherits from BaseAccount and implements interest calculation features.
    * 
    */
class SavingAccount : public BaseAccount
{
    public:
    /**
    * @brief:Construct a new Saving Account object
    * @param id             :The account ID.
    * @param apr            :The annual percentage rate (interest rate).
    * @param opening_balance: The starting balance in cents.
    * 
    */
    SavingAccount(std::string id, double apr,long long opening_balance);

    /**
    * @brief : Get the type of the account (Savings).
    * @return: AccountType Always returns AccountType::SAVINGS.
    * 
    */
    AccountType GetType();

    /**
    * @brief: Apply interest to the savings account based on time.
    * @param timestamp: The time when interest is applied.
    * @param note     : Optional description.
    * 
    */
    void ApplyInterest(long long timestamp,const char* note);
};

#endif // IACCOUNT_CPP_