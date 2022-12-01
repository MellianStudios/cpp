#include <iostream>
#include "Models/Auth/Account/Account.h"

int main()
{
    std::string command;

    std::cout << "auth server running" << std::endl;

    while (true) {
        std::cout << "enter command" << std::endl;

        std::getline(std::cin, command);

        if (command == "ACCOUNT SEARCH") {
            int id;

            std::cout << "enter ID" << std::endl;

            std::cin >> id;

            Account *account = Account::getByColumnValue("id = ?", {id});

            std::cout << "username " << account->m_username << std::endl;
        }

        if (command == "exit") {
            return 0;
        }
    }

    return 0;
}
