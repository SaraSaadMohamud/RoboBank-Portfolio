//  Copyright 2025 Sara Saad

/******************************************* INCLUDE PART
 * **************************************** */
#include "../Inc/Portfolio.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
IAccount * Portfolio::GetAccount(const std::string &id) const {
  auto i = accounts_.find(id);

  if (i != accounts_.end()) {
    return (i->second.get());
  } else {
    return (nullptr);
  }
}

void Portfolio::ApplyTx(const TxRecord &tx) {
  IAccount *acc = GetAccount(tx.account_id);
  if (!acc) {
    exit(1);
  }

  switch (tx.kind) {
    case TxKind::KDEPOSIT:
      acc->Deposit(tx.amount_cents, tx.timestamp, tx.note);
      break;

    case TxKind::KWITHDRAWAL:
      acc->Withdraw(tx.amount_cents, tx.timestamp, tx.note);
      break;

    case TxKind::KFEE:
      acc->ChargeFee(tx.amount_cents, tx.timestamp, tx.note);
      break;

    case TxKind::KINTEREST:
      acc->PostSimpleInterest(tx.amount_cents, 356, tx.timestamp, tx.note);
      break;

    default:

      break;
  }
  batch_audit_.push_back(tx);
}

void Portfolio::AddAccount(std::unique_ptr<IAccount> acc) {
  accounts_[acc->GetId()] = std::move(acc);
}

size_t Portfolio::CountAccounts() { return (accounts_.size()); }

void Portfolio::ApplyAll(const std::vector<TxRecord> &txs) {
  for (const auto &tx : txs) {
    ApplyTx(tx);
  }
}

void Portfolio::ApplyFromLedger(const std::string *account_ids,
                                const int32_t *tx_types, const int64_t *amounts,
                                int32_t count) {
  std::vector<TxRecord> txs;
  for (int32_t i = 0; i < count; i++) {
    TxKind kind = static_cast<TxKind>(tx_types[i]);
    txs.push_back({kind, amounts[i], 0, "", account_ids[i]});
  }
  this->ApplyAll(txs);
}

bool Portfolio::Transfer(TransferRecord txr) {
  IAccount *from = GetAccount(txr.from_id);
  IAccount *to = GetAccount(txr.to_id);

  if (!from || !to) {
    return (false);
  }
  from->Withdraw(txr.amount_cents, txr.timestamp, (\
    txr.note + "Transfer Out!").c_str());
  to->Deposit(txr.amount_cents, txr.timestamp, (\
     txr.note + "Teransfer In!.").c_str());
  return (true);
}

int64_t Portfolio::TotalExposure() const {
  int64_t total = 0;
  Calculator calc;
  for (const auto &pair : accounts_) {
    total += pair.second->GetBalance();
  }
  return (total);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
