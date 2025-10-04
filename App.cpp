/************************************************ INCLUDE PART *************************************** */
#include "Inc/App.hpp"
////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    MainProgram();
    
    return(0);
}

void MainProgram()
{
    ////////////////////////////////////////////// TEST1 ///////////////////////////////////////////////
    Portfolio portfolio;

    portfolio.AddAccount(std::make_unique<CheckingAccount>("CHK-001", 150, 1000));   
    portfolio.AddAccount(std::make_unique<SavingAccount>("SAV-010", 0.05, 5000));   


    std::cout << "Test 1: Portfolio size = " << portfolio.CountAccounts();

    if (portfolio.CountAccounts() == 2) 
    {
        std::cout << " (Passed)" << std::endl;
    }
    else 
    {
        std::cout << " (Failed)" << std::endl;
    }
    ////////////////////////////////////////////// TEST2 ///////////////////////////////////////////////
    std::vector<TxRecord> txs = {
                                {TxKind::KDEPOSIT, 100000, 1234567890, "Deposit", "CHK-001"},
                                {TxKind::KWITHDRAWAL, 25000, 1234567891, "Withdraw", "CHK-001"},
                                {TxKind::KFEE, 1500, 1234567892, "Fee", "CHK-001"}
                                };
    portfolio.ApplyAll(txs);
    long long chk_balance = portfolio.GetAccount("CHK-001")->GetBalance();
    std::cout << "Test 2: CHK-001 balance = " << chk_balance;

    if (chk_balance == 73500) 
    {
        std::cout << " (Passed)" << std::endl;
    } 
    else 
    {
        std::cout << " (Failed)" << std::endl;
    }

    ///////////////////////////////////////////////// TEST3 /////////////////////////////////////////////
    
    portfolio.GetAccount("SAV-010")->Deposit(500000, 1234567893, "Initial Deposit for Interest Test");
    portfolio.GetAccount("SAV-010")->PostSimpleInterest(31,365, 1234567894,"Interest");
    long long sav_balance = portfolio.GetAccount("SAV-010")->GetBalance();
    std::cout << "Test 3: SAV-010 balance after interest = " << sav_balance;

    if (sav_balance == 502123) 
    { 
        std::cout << " (Passed)" << std::endl;
    } 
    else
    {
        std::cout << " (Failed, expected ~502123)" << std::endl;
    }

    ////////////////////////////////////////////// TEST4 ///////////////////////////////////////////////
    
    TransferRecord tr{"SAV-010", "CHK-001", 30000, 1234567895, "Transfer"};
    bool transfer_success = portfolio.Transfer(tr);

    chk_balance = portfolio.GetAccount("CHK-001")->GetBalance();
    sav_balance = portfolio.GetAccount("SAV-010")->GetBalance();

    std::cout << "Test 4: Transfer success = " << transfer_success << ", CHK-001 = " << chk_balance << ", SAV-010 = " << sav_balance;
    if (transfer_success && chk_balance == 103500 && sav_balance == 472123) 
    {
        std::cout << " (Passed)" << std::endl;
    } 
    else
    {
        std::cout << " (Failed)" << std::endl;
    }
    


   ////////////////////////////////////////////// TEST5 ///////////////////////////////////////////////
   
    portfolio.AddAccount(std::make_unique<CheckingAccount>("CHK-001", 150, 1000));  
    portfolio.AddAccount(std::make_unique<CheckingAccount>("CHK-002", 0, 0));
    portfolio.AddAccount(std::make_unique<SavingAccount>("SAV-010", 0.05, 500000));


    std::string ids[] = {"CHK-001", "CHK-002", "SAV-010"};
    int types[] = {
                static_cast<int>(TxKind::KWITHDRAWAL), 
                static_cast<int>(TxKind::KDEPOSIT), 
                static_cast<int>(TxKind::KDEPOSIT)
                };

    long long amts[] = {60000, 30000, 29877};


    portfolio.ApplyFromLedger(ids, types, amts, 3);

    long long chk1_balance = portfolio.GetAccount("CHK-001")->GetBalance();
    long long chk2_balance = portfolio.GetAccount("CHK-002")->GetBalance();
    long long sav1_balance = portfolio.GetAccount("SAV-010")->GetBalance();

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
    ////////////////////////////////////////////// TEST5 ///////////////////////////////////////////////

    long long total = portfolio.TotalExposure();
    std::cout << "Test 6: Total exposure = " << total;

    if (total == 43500 + 30000 + 502000) 
    {
        std::cout << " (Passed)" << std::endl;
    } 
    else
    {
        std::cout << " (Failed)" << std::endl;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
}
