#include "../Inc/IAccount.hpp"

BaseAccount::BaseAccount(std::string id, AccountSettings settings, long long opening_balnce)
{
    id_ = id;
    setting_ = settings;
    balance_cent_ = opening_balnce;
}

void BaseAccount:: Record(const TxRecord& rec)
{
    if (audit_.size() >= 1000)
    {
         audit_.erase(audit_.begin()); 
    } 

    audit_.push_back(rec);
}

void BaseAccount::UpdateBalance(long long cents)
{
    balance_cent_ = Calculator::Deposit(balance_cent_,cents);
}

std::string BaseAccount::GetId()
{
    return(id_);
}

long long BaseAccount::GetBalance() const 
{
    return(balance_cent_);
}

AccountSettings BaseAccount::GetSetting()
{
    return(setting_);
}

const std::vector<TxRecord>& BaseAccount:: GetAudit()
{
    return(audit_);
}

void BaseAccount::Deposit(long long amount_cents, long long ts, const char* note)
{
    balance_cent_ = Calculator::Deposit(balance_cent_,amount_cents);
    Record({TxKind::KDEPOSIT,amount_cents,ts,note});
}
void BaseAccount::Withdraw(long long amount_cents, long long ts, const char* note)
{
    balance_cent_ = Calculator::Withdraw(balance_cent_,amount_cents);
    Record({TxKind::KWITHDRAWAL,amount_cents,ts,note});
}
void BaseAccount::ChargeFee(long long fee_cents, long long ts, const char* note)
{
    balance_cent_ = Calculator::Fee(balance_cent_,fee_cents);
    Record({TxKind::KFEE,fee_cents,ts,note});
}
void BaseAccount::PostSimpleInterest(int days, int basis, long long ts, const char* note)
{
    long long interest = Calculator::Interest(balance_cent_,setting_.apr,days,basis);
    UpdateBalance(interest);
    Record({TxKind::KINTEREST,interest,ts,note});
}

void BaseAccount:: Apply(const TxRecord& tx)
{
    switch(tx.kind)
    {
        case TxKind::KDEPOSIT:
        this->Deposit(tx.amount_cents,tx.timestamp,tx.note);
        break;

        case TxKind::KWITHDRAWAL:
        this->Withdraw(tx.amount_cents,tx.timestamp,tx.note);
        break;

        case TxKind::KFEE:
        this->ChargeFee(tx.amount_cents,tx.timestamp,tx.note);
        break;

        case TxKind::KINTEREST:
        this->PostSimpleInterest(30,365,tx.timestamp,tx.note);
        break;

        case TxKind::KTRANSFERIN:
        balance_cent_ = Calculator::Deposit(balance_cent_,tx.amount_cents);
        Record(TxRecord{TxKind::KTRANSFERIN,tx.amount_cents,tx.timestamp,tx.note});
        break;

        case TxKind::KTRANSFEROUT:
        balance_cent_ = Calculator::Withdraw(balance_cent_,tx.amount_cents);
        Record(TxRecord{TxKind::KTRANSFEROUT,tx.amount_cents,tx.timestamp,tx.note});
        break;

        default:
        break;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CheckingAccount::CheckingAccount(std::string id, long long fee_centsm, long long opening_balance):
BaseAccount(id,{AccountType::KCHECKING,0.0,fee_centsm},opening_balance){}

AccountType CheckingAccount::GetType()
{
    return(AccountType::KCHECKING);
}

void CheckingAccount:: ApplyFee(long long timestamp,const char* note)
{
    this->ChargeFee(setting_.fee_flat_cents,timestamp,note);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SavingAccount::SavingAccount(std::string id, double apr,long long opening_balance):
BaseAccount(id,{AccountType::KSAVINGS,apr,0},opening_balance) {}

AccountType SavingAccount::GetType()
{
    return(AccountType::KSAVINGS);
}

 void SavingAccount::ApplyInterest(long long timestamp,const char* note)
 {
    this->PostSimpleInterest(30,365,timestamp,note);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IAccount::~IAccount() {};