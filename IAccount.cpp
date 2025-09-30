#include "IAccount.hpp"

Base_Account::Base_Account(std::string id_, AccountSettings settings_, long long opening_balnce)
{
    id = id_;
    setting = settings_;
    balance_cent = opening_balnce;
}

void Base_Account:: record(const TxRecord& rec)
{
    if (audit_.size() >= 1000)
    {
         audit_.erase(audit_.begin()); 
    } 

    audit_.push_back(rec);
}

void Base_Account::update_balance(long long cents)
{
    balance_cent = Calculator::deposit(balance_cent,cents);
}

std::string Base_Account::get_id()
{
    return(id);
}

long long Base_Account::get_balance() const 
{
    return( balance_cent);
}

AccountSettings Base_Account::get_setting()
{
    return(setting);
}

const std::vector<TxRecord>& Base_Account:: get_audit()
{
    return(audit_);
}

void Base_Account::deposit(long long amount_cents, long long ts, const char* note)
{
    balance_cent = Calculator::deposit(balance_cent,amount_cents);
    record({TxKind::Deposit,amount_cents,ts,note});
}
void Base_Account::withdraw(long long amount_cents, long long ts, const char* note)
{
    balance_cent = Calculator::withdraw(balance_cent,amount_cents);
    record({TxKind::Withdrawal,amount_cents,ts,note});
}
void Base_Account::charge_fee(long long fee_cents, long long ts, const char* note)
{
    balance_cent = Calculator::fee(balance_cent,fee_cents);
    record({TxKind::Fee,fee_cents,ts,note});
}
void Base_Account::post_simple_interest(int days, int basis, long long ts, const char* note)
{
    long long interest = Calculator::interest(balance_cent,setting.apr,days,basis);
    update_balance(interest);
    record({TxKind::Interest,interest,ts,note});
}

void Base_Account:: Apply(const TxRecord& tx)
{
    switch(tx.kind)
    {
        case TxKind::Deposit:
        this->deposit(tx.amount_cents,tx.timestamp,tx.note);
        break;

        case TxKind::Withdrawal:
        this->withdraw(tx.amount_cents,tx.timestamp,tx.note);
        break;

        case TxKind::Fee:
        this->charge_fee(tx.amount_cents,tx.timestamp,tx.note);
        break;

        case TxKind::Interest:
        this->post_simple_interest(30,365,tx.timestamp,tx.note);
        break;

        case TxKind::TransferIn:
        balance_cent = Calculator::deposit(balance_cent,tx.amount_cents);
        record(TxRecord{TxKind::TransferIn,tx.amount_cents,tx.timestamp,tx.note});
        break;

        case TxKind::TransferOUT:
        balance_cent = Calculator::withdraw(balance_cent,tx.amount_cents);
        record(TxRecord{TxKind::TransferOUT,tx.amount_cents,tx.timestamp,tx.note});
        break;

        default:
        break;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Checking_Account::Checking_Account(std::string id_, long long fee_centsm, long long opening_balance):
Base_Account(id_,{AccountType::Checking,0.0,fee_centsm},opening_balance){}

AccountType Checking_Account::get_type()
{
    return(AccountType::Checking);
}

void Checking_Account:: Apply_fee(long long timestamp,const char* note)
{
    this->charge_fee(setting.fee_flat_cents,timestamp,note);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Saving_Account::Saving_Account(std::string id, double apr,long long opening_balance):
Base_Account(id,{AccountType::Savings,apr,0},opening_balance) {}

AccountType Saving_Account::get_type()
{
    return(AccountType::Savings);
}

 void Saving_Account::Apply_interest(long long timestamp,const char* note)
 {
    this->post_simple_interest(30,365,timestamp,note);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IAccount::~IAccount() {};