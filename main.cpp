#include <iostream>
#include"Portfolio.hpp"
#include "IAccount.hpp"

int main()
{

    
    /* بسم الله الرحمن الرحيم */
    
    // Test1
    Portfolio portfolio;

    portfolio.add_account(std::make_unique<Checking_Account>("CHK-001", 150, 1000));   
    portfolio.add_account(std::make_unique<Saving_Account>("SAV-010", 0.05, 5000));   


    std::cout << "Test 1: Portfolio size = " << portfolio.count_accounts();

    if (portfolio.count_accounts() == 2) 
    {
        std::cout << " (Passed)" << std::endl;
    }
    else 
    {
        std::cout << " (Failed)" << std::endl;
    }

    // test2
    std::vector<TxRecord> txs = {
                                {TxKind::Deposit, 100000, 1234567890, "Deposit", "CHK-001"},
                                {TxKind::Withdrawal, 25000, 1234567891, "Withdraw", "CHK-001"},
                                {TxKind::Fee, 1500, 1234567892, "Fee", "CHK-001"}
                                };
    portfolio.apply_all(txs);
    long long chk_balance = portfolio.get_account("CHK-001")->get_balance();
    std::cout << "Test 2: CHK-001 balance = " << chk_balance;

    if (chk_balance == 73500) 
    {
        std::cout << " (Passed)" << std::endl;
    } 
    else 
    {
        std::cout << " (Failed)" << std::endl;
    }

    // Test3
    portfolio.get_account("SAV-010")->deposit(500000, 1234567893, "Initial Deposit for Interest Test");
    portfolio.get_account("SAV-010")->post_simple_interest(31,365, 1234567894,"Interest");
    long long sav_balance = portfolio.get_account("SAV-010")->get_balance();
    std::cout << "Test 3: SAV-010 balance after interest = " << sav_balance;

    if (sav_balance == 502123) 
    { 
        std::cout << " (Passed)" << std::endl;
    } 
    else
    {
        std::cout << " (Failed, expected ~502123)" << std::endl;
    }

    
    //Test4
    TransferRecord tr{"SAV-010", "CHK-001", 30000, 1234567895, "Transfer"};
    bool transfer_success = portfolio.transfer(tr);

    chk_balance = portfolio.get_account("CHK-001")->get_balance();
    sav_balance = portfolio.get_account("SAV-010")->get_balance();

    std::cout << "Test 4: Transfer success = " << transfer_success << ", CHK-001 = " << chk_balance << ", SAV-010 = " << sav_balance;
    if (transfer_success && chk_balance == 103500 && sav_balance == 472123) 
    {
        std::cout << " (Passed)" << std::endl;
    } 
    else
    {
        std::cout << " (Failed)" << std::endl;
    }
    


    
    //Test5
   
    portfolio.add_account(std::make_unique<Checking_Account>("CHK-001", 150, 1000));  
    portfolio.add_account(std::make_unique<Checking_Account>("CHK-002", 0, 0));
    portfolio.add_account(std::make_unique<Saving_Account>("SAV-010", 0.05, 500000));


    std::string ids[] = {"CHK-001", "CHK-002", "SAV-010"};
    int types[] = {
                static_cast<int>(TxKind::Withdrawal), 
                static_cast<int>(TxKind::Deposit), 
                static_cast<int>(TxKind::Deposit)
                };

    long long amts[] = {60000, 30000, 29877};


    portfolio.apply_from_ledger(ids, types, amts, 3);

    long long chk1_balance = portfolio.get_account("CHK-001")->get_balance();
    long long chk2_balance = portfolio.get_account("CHK-002")->get_balance();
    long long sav1_balance = portfolio.get_account("SAV-010")->get_balance();

    std::cout << "Test 5: After Ledger - CHK-001 = " << chk1_balance 
            << ", CHK-002 = " << chk2_balance 
            << ", SAV-010 = " << sav1_balance;

    if (chk_balance == 43500 && chk2_balance == 30000 && sav_balance == 502000) 
    {
        std::cout << " (Passed)" << std::endl;
    } 
    else
    {
        std::cout << " (Failed)" << std::endl;
    }

    //Test6

    long long total = portfolio.total_exposure();
    std::cout << "Test 6: Total exposure = " << total;

    if (total == 43500 + 30000 + 502000) 
    {
        std::cout << " (Passed)" << std::endl;
    } 
    else
    {
        std::cout << " (Failed)" << std::endl;
    }

    return(0);
}