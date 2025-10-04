    /**
    * @file : APP.hpp
    * @brief: Entry point declaration for the banking application.
    * 
    * This header file declares the main driver function MainProgram() which serves as the central execution point of the banking system application. 
    * It acts as a high-level orchestrator that utilizes the Portfolio and related banking components (like IAccount) to run the core business logic, such as account management, transaction processing, and reporting.
    * The actual implementation of MainProgram() should be defined in a corresponding .cpp file (e.g., APP.cpp), while this header provides the external declaration for integration or testing purposes.
    *
    */

#ifndef APP_HPP_
#define APP_HPP_

/*********************************************** include part ************************************ */
#include <iostream>

#include"Portfolio.hpp"
#include "IAccount.hpp"
///////////////////////////////////////////////////////////////////////////////////////////////////////

/**************************************** Function Declertion ************************************** */
/**

    * @brief: Main driver function of the banking application.
    * This function contains the primary logic that initializes the application, sets up the portfolio of accounts, processes user input or transactions, and manages the overall workflow of the banking system.
    * It is typically invoked from the global main() function in the application's entry point (e.g., main.cpp). 
    * The exact operations performed inside may include:
        - Creating and adding accounts (e.g., Checking, Savings).
        - Applying batches of transactions (deposits, withdrawals, fees, interest).
        - Executing transfers between accounts.
        - Generating reports or summaries (e.g., total exposure, audit logs).
    * @note The implementation of this function is not defined in this header;
    *
    */
void MainProgram();

#endif //APP_HPP_