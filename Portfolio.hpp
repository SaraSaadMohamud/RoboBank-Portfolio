#ifndef _PORTFOLIO_HPP_
#define _PORTFOLIO_HPP_
/**************************************************** include Part ******************************************** */
#include<memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "Types.hpp"
#include "IAccount.hpp" 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************** Class Part *********************************************** */

class Portfolio
{
    private:
    std::unordered_map<std::string, std::unique_ptr<IAccount>> accounts;
    std::vector<TxRecord> batch_audit;

    void apply_tx(const TxRecord& tx);

    public:
    void add_account(std::unique_ptr<IAccount> acc);
    size_t count_accounts();
    IAccount* get_account(const std::string& id) const;

    void apply_all(const std::vector<TxRecord>& txs) ;
    void apply_from_ledger(const std::string* account_ids, const int* tx_types, const long long* amounts, int count);

    bool transfer(TransferRecord txr);
    long long total_exposure() const;

};
#endif  // _PORTFOLIO_HPP_