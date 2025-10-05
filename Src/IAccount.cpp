// Copyright 2025 Sara Saad

#include "../Inc/IAccount.hpp"

#include "../Inc/Calculator.hpp"

BaseAccount::BaseAccount(std::string id, AccountSettings settings,
                         int64_t opening_balnce) {
  id_ = id;
  setting_ = settings;
  balance_cent_ = opening_balnce;
}

void BaseAccount::Record(const TxRecord &rec) {
  if (audit_.size() >= 1000) {
    audit_.erase(audit_.begin());
  }

  audit_.push_back(rec);
}

std::string BaseAccount::GetId() { return (id_); }

void BaseAccount::UpdateBalance(int64_t cents)
{
  balance_cent_ = Calculator::Deposit(balance_cent_,cents);
}

int64_t BaseAccount::GetBalance() const 
{
    return(balance_cent_);
}

AccountSettings BaseAccount::GetSetting() { return (setting_); }

const std::vector<TxRecord> &BaseAccount::GetAudit() { return (audit_); }

void BaseAccount::Deposit(int64_t amount_cents, int64_t ts,
                          const char *note) {
  balance_cent_ = Calculator::Deposit(balance_cent_, amount_cents);
  Record({TxKind::KDEPOSIT, amount_cents, ts, note});
}
void BaseAccount::Withdraw(int64_t amount_cents, int64_t ts, const char *note) {
  balance_cent_ = Calculator::Withdraw(balance_cent_, amount_cents);
  Record({TxKind::KWITHDRAWAL, amount_cents, ts, note});
}
void BaseAccount::ChargeFee(int64_t fee_cents, int64_t ts, const char *note) {
  balance_cent_ = Calculator::Fee(balance_cent_, fee_cents);
  Record({TxKind::KFEE, fee_cents, ts, note});
}
void BaseAccount::PostSimpleInterest(int32_t days, int32_t basis, int64_t ts,
                                     const char *note) {
  int64_t interest =
      Calculator::Interest(balance_cent_, setting_.apr, days, basis);
  UpdateBalance(interest);
  Record({TxKind::KINTEREST, interest, ts, note});
}

void BaseAccount::Apply(const TxRecord &tx) {
  switch (tx.kind) {
    case TxKind::KDEPOSIT:
      this->Deposit(tx.amount_cents, tx.timestamp, tx.note);
      break;

    case TxKind::KWITHDRAWAL:
      this->Withdraw(tx.amount_cents, tx.timestamp, tx.note);
      break;

    case TxKind::KFEE:
      this->ChargeFee(tx.amount_cents, tx.timestamp, tx.note);
      break;

    case TxKind::KINTEREST:
      this->PostSimpleInterest(30, 365, tx.timestamp, tx.note);
      break;

    case TxKind::KTRANSFERIN:
      balance_cent_ = Calculator::Deposit(balance_cent_, tx.amount_cents);
      Record(TxRecord{TxKind::KTRANSFERIN, tx.amount_cents, tx.timestamp,
                      tx.note});
      break;

    case TxKind::KTRANSFEROUT:
      balance_cent_ = Calculator::Withdraw(balance_cent_, tx.amount_cents);
      Record(TxRecord{TxKind::KTRANSFEROUT, tx.amount_cents, tx.timestamp,
                      tx.note});
      break;

    default:
      break;
  }
}

CheckingAccount::CheckingAccount(std::string id, int64_t fee_centsm,
                                 int64_t opening_balance)
    : BaseAccount(id, {AccountType::KCHECKING, 0.0, fee_centsm},
                  opening_balance) {}

AccountType CheckingAccount::GetType() { return (AccountType::KCHECKING); }

void CheckingAccount::ApplyFee(int64_t timestamp, const char *note) {
  this->ChargeFee(setting_.fee_flat_cents, timestamp, note);
}

SavingAccount::SavingAccount(std::string id, double apr,
                             int64_t opening_balance)
    : BaseAccount(id, {AccountType::KSAVINGS, apr, 0}, opening_balance) {}

AccountType SavingAccount::GetType() { return (AccountType::KSAVINGS); }

void SavingAccount::ApplyInterest(int64_t timestamp, const char *note) {
  this->PostSimpleInterest(30, 365, timestamp, note);
}


IAccount::~IAccount() {}

