#ifndef BANK_1_HPP
# define BANK_1_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <iomanip>

using namespace std;

const string path_name = "clients.txt";

typedef struct Client_Data
{
    string	user_name;
    string	phone;
    string	pin_code;
    string	account_number;
    string	account_balance;
    bool 	Mark_for_delet;
} Client;


void	Add_Clients(void);
void	PrintAllClientsData(void);
bool	Find_client(void);
void    Delet_client(void);
void    Update_Client(void);
void	bank_1_project(void);

#endif