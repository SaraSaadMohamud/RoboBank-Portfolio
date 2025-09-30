#include "Portfolio.hpp"

IAccount* Portfolio::get_account(const std::string& id) const
{
    auto i = accounts.find(id);

    if(i != accounts.end())
    {
       return( i->second.get());
    }
    else
    {
        return(nullptr);
    }
}

void Portfolio::apply_tx(const TxRecord& tx)
{
    IAccount* acc = get_account(tx.account_id);
    if(!acc)
    {
       exit(1);
    }

    switch(tx.kind)
    {
        case TxKind::Deposit:
        acc->deposit(tx.amount_cents,tx.timestamp,tx.note);
        break;

        case TxKind::Withdrawal:
        acc->withdraw(tx.amount_cents,tx.timestamp,tx.note);
        break;

        case TxKind::Fee:
        acc->charge_fee(tx.amount_cents,tx.timestamp,tx.note);
        break;

        case TxKind::Interest:
        acc->post_simple_interest(tx.amount_cents,356,tx.timestamp,tx.note);
        break;

        default:
        break;
    }
    batch_audit.push_back(tx);
}

void Portfolio::add_account(std::unique_ptr<IAccount> acc)
{
    accounts[acc->get_id()] = std::move(acc);
}

size_t Portfolio:: count_accounts()
{
    return(accounts.size());
}

void Portfolio::apply_all(const std::vector<TxRecord>& txs) 
{
    for (const auto& tx : txs)
    {
        apply_tx(tx);
    }
}

void Portfolio::apply_from_ledger(const std::string* account_ids, const int* tx_types, const long long* amounts, int count)
{
    std::vector<TxRecord> txs;
    for(int i = 0; i< count ; i++)
    {
        TxKind kind = static_cast<TxKind>(tx_types[i]);
        txs.push_back({kind,amounts[i],0,"",account_ids[i]});
    }
    this->apply_all(txs);
}

bool Portfolio:: transfer(TransferRecord txr)
{
    IAccount* from = get_account(txr.from_id);
    IAccount* to = get_account(txr.to_id);

    if(!from || !to)
    {
        return(false);
    }
    from ->withdraw(txr.amount_cents,txr.timestamp,(txr.note+"Transfer Out!").c_str());
    to ->deposit(txr.amount_cents,txr.timestamp,(txr.note + "Teransfer In!.").c_str());
    return(true);
}

long long Portfolio:: total_exposure() const
{
    long long total = 0;
    Calculator calc;
    for(const auto&pair : accounts)
    {
        total += pair.second->get_balance();
    }
    return(total);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////