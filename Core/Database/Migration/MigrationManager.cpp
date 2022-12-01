#include "MigrationManager.h"
#include "Auth/2022_11_27_01_47_07_create_accounts_table/Migration_2022_11_27_01_47_07_create_accounts_table.h"

void MigrationManager::update()
{
    Migration_2022_11_27_01_47_07_create_accounts_table migration20221127014707CreateAccountsTable;
    migration20221127014707CreateAccountsTable.up();
}

void MigrationManager::fresh()
{
    Migration_2022_11_27_01_47_07_create_accounts_table migration20221127014707CreateAccountsTable;
    migration20221127014707CreateAccountsTable.down();
    migration20221127014707CreateAccountsTable.up();
}
