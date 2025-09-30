#ifndef _IACCOUNT_CPP_
#define _IACCOUNT_CPP_

/********************************************** include Part ***************************************** */
#include <vector>
#include "Types.hpp"
#include "Calculator.hpp"
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*********************************************** Macros Part **************************************** */
#define MaxAudit   256
/********************************************* Classes Part ***************************************** */
class IAccount
{
    public:
    virtual ~IAccount();

    /****** Getter Function ******* */
    virtual std::string get_id()            = 0;      // returns the account ID
    virtual AccountType get_type()          = 0;      // returns Checking or Savings
    virtual AccountSettings get_setting()   = 0;      // returns balance in cents

    /******* State ******* */
    virtual long long get_balance() const = 0;
    virtual const std::vector<TxRecord>& get_audit() = 0;

    /******** Setter Functions****** */
    virtual void deposit(long long amount_cents, long long ts, const char* note) = 0;               ///< Deposit money
    virtual  void withdraw(long long amount_cents, long long ts, const char* note) = 0;              ///< Withdraw money
    virtual void charge_fee(long long fee_cents, long long ts, const char* note) = 0;               ///< Charge a fee
    virtual void post_simple_interest(int days, int basis, long long ts, const char* note) = 0;     ///< Post interest
    virtual void Apply(const TxRecord& tx) = 0;

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////

class Base_Account : public IAccount
{
    protected:

    std::string id;
    AccountSettings setting;
    long long balance_cent;
    std::vector<TxRecord> audit_;
    int audit_count_; 

    void record(const TxRecord& rec);
    void update_balance(long long cents);

    public:

    Base_Account(std::string id_, AccountSettings settings_, long long opening_balnce);
    std::string get_id();
    long long get_balance() const;
    AccountSettings get_setting() ;
    const std::vector<TxRecord>& get_audit();

    void deposit(long long amount_cents, long long ts, const char* note);               ///< Deposit money
    void withdraw(long long amount_cents, long long ts, const char* note);              ///< Withdraw money
    void charge_fee(long long fee_cents, long long ts, const char* note);               ///< Charge a fee
    void post_simple_interest(int days, int basis, long long ts, const char* note);     ///< Post interest
    void Apply(const TxRecord& tx);

    virtual AccountType get_type()  = 0;
};

class Checking_Account : public Base_Account
{
    public:
    Checking_Account(std::string id_, long long fee_centsm, long long opening_balance);
    AccountType get_type();
    void Apply_fee(long long timestamp,const char* note);
};

class Saving_Account : public Base_Account
{
    public:
    Saving_Account(std::string id, double apr,long long opening_balance);
    AccountType get_type();
    void Apply_interest(long long timestamp,const char* note);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // _IACCOUNT_CPP_