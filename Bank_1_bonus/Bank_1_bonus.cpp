#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string path_name = "clients.txt";

void    Main_Menue();
static void	ft_Deposit();
static void	Transactions_screen();


struct  s_Client
{
    string account_number;
    string pin_code;
    string user_name;
    string Phone;
    double account_balance;
    bool mark_for_delet = false;
};

enum    e_Menue_option{list_client = 1, add_new_client = 2, delet_client = 3, update_client = 4, find_client = 5, Transaction = 6, Exit = 7};

enum    e_transactions_option{Deposit = 1, Withdraw = 2, Total_Balances = 3, return_Main_Menue = 4};

static vector<string> split_string(string s1, string seperator)
{
    vector<string> v_string;
    int pos = 0;
    string s_word;
 
    while ((pos = s1.find(seperator)) != std::string::npos)
    {
        s_word = s1.substr(0, pos); 
        if (s_word != "")
        {
            v_string.push_back(s_word);
        }

        s1.erase(0, pos + seperator.length());
    }

    if (s1 != "")
    {
        v_string.push_back(s1);
    }

    return (v_string);

}

static s_Client ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    s_Client Client;
    vector<string> v_data;
    v_data = split_string(Line, Seperator);

    Client.account_number = v_data[0];
    Client.pin_code = v_data[1];
    Client.user_name = v_data[2];
    Client.Phone = v_data[3];
    Client.account_balance = stod(v_data[4]);
    return (Client);
}

static string convert_vector_to_line(s_Client Client, string Seperator = "#//#")
{

    string line = "";
    line += Client.account_number + Seperator;
    line += Client.pin_code + Seperator;
    line += Client.user_name + Seperator;
    line += Client.Phone + Seperator;
    line += to_string (Client.account_balance);
    return (line);
}

static bool client_is_found(string account_number, string path_name)
{
    vector <s_Client> v_clients;
    fstream MyFile;
    MyFile.open(path_name, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        s_Client Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.account_number == account_number)
            {
                MyFile.close();
                return (true);
            }
            v_clients.push_back(Client);
        }

        MyFile.close();

    }
    return (false);
}

static s_Client Read_one_client()
{
    s_Client Client;
    cout << "Enter Account Number? ";

    getline(cin >> ws, Client.account_number);

    while (client_is_found(Client.account_number, path_name))
    {
        cout << "\nClient with [" << Client.account_number << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.account_number);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.pin_code);

    cout << "Enter Name? ";
    getline(cin, Client.user_name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.account_balance;

    return (Client);
}

static vector <s_Client> Load_cleints_data_from_file(string path_name)
{
    vector <s_Client> v_Clients;
    fstream my_file;
    my_file.open(path_name, ios::in);

    if (my_file.is_open())
    {
        string Line;
        s_Client Client;

        while (getline(my_file, Line))
        {
            Client = ConvertLinetoRecord(Line);
            v_Clients.push_back(Client);
        }
        my_file.close();
    }
    return (v_Clients);
}

void Print_client_info(s_Client Client)
{
    cout << "| " << setw(15) << left << Client.account_number;
    cout << "| " << setw(10) << left << Client.pin_code;
    cout << "| " << setw(40) << left << Client.user_name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.account_balance;
}

static void show_screen()
{
    vector <s_Client> vClients = Load_cleints_data_from_file(path_name);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n________________________________________________________________________________________________" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n________________________________________________________________________________________________" << endl;
    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (s_Client Client : vClients)
        {

            Print_client_info(Client);
            cout << endl;
        }
	cout << "\n________________________________________________________________________________________________" << endl;
}

static void Print_Client_Card(s_Client Client)
{
    cout << "\nThe following are the client details: " << endl;
    cout << "_______________________________________" << endl;
    cout << "\nAccout Number: " << Client.account_number;
    cout << "\nPin Code     : " << Client.pin_code;
    cout << "\nName         : " << Client.user_name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.account_balance;
    cout << "\n_______________________________________" << endl;
}

static bool find_client_by_account_number(string AccountNumber, vector <s_Client> vClients, s_Client& Client)
{
    for (s_Client C : vClients)
    {

        if (C.account_number == AccountNumber)
        {
            Client = C;
            return (true);
        }

    }
    return (false);
}

static s_Client ChangeClientRecord(string account_nb)
{
    s_Client Client;

    Client.account_number = account_nb;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.pin_code);

    cout << "Enter Name? ";
    getline(cin, Client.user_name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.account_balance;
    return (Client);
}

static bool Mark_client_for_delet(string account_number, vector <s_Client>& vClients)
{

    for (s_Client& C : vClients)
    {

        if (C.account_number == account_number)
        {
            C.mark_for_delet = true;
            return (true);
        }

    }
    return (false);
}

static vector <s_Client> SaveCleintsDataToFile(string path_name, vector <s_Client> vClients)
{
    fstream MyFile;
    MyFile.open(path_name, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {
        for (s_Client C : vClients)
        {

            if (C.mark_for_delet == false)
            {
                DataLine = convert_vector_to_line(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }
    return (vClients);
}

static void AddDataLineToFile(string path_name, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(path_name, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

static void AddNewClient()
{
    s_Client Client;
    Client = Read_one_client();
    AddDataLineToFile(path_name, convert_vector_to_line(Client));
}

static void Add_new_Client()
{
    char AddMore = 'Y';
    do
    {
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully,\n\tdo you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

static bool DeleteClientByAccountNumber(string AccountNumber, vector <s_Client>& vClients)
{
    s_Client Client;
    char Answer = 'n';

    if (find_client_by_account_number(AccountNumber, vClients, Client))
    {

        Print_Client_Card(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Mark_client_for_delet(AccountNumber, vClients);
            SaveCleintsDataToFile(path_name, vClients);

            vClients = Load_cleints_data_from_file(path_name);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
    return false;
}

static bool update_client_by_account_number(string AccountNumber, vector <s_Client>& vClients)
{

    s_Client Client;
    char Answer = 'n';

    if (find_client_by_account_number(AccountNumber, vClients, Client))
    {

        Print_Client_Card(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (s_Client& C : vClients)
            {
                if (C.account_number == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(path_name, vClients);

            cout << endl << "Client Updated Successfully." << endl;
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!" << endl;
        return false;
    }
}

static string Read_account_number_of_number()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return (AccountNumber);
}

static void delet_client_screen()
{
    cout << "\n-----------------------------------" << endl;
    cout << "\tDelete Client : ";
    cout << "\n-----------------------------------" << endl;

    vector <s_Client> vClients = Load_cleints_data_from_file(path_name);
    string AccountNumber = Read_account_number_of_number();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

static void update_client_screen()
{
    cout << "\n-----------------------------------" << endl;
    cout << "\tUpdate Client Info : ";
    cout << "\n-----------------------------------" << endl;

    vector <s_Client> vClients = Load_cleints_data_from_file(path_name);
    string AccountNumber = Read_account_number_of_number();
    update_client_by_account_number(AccountNumber, vClients);

}

static void Add_newClient_screen()
{
    cout << "\n-----------------------------------" << endl;
    cout << "\tAdd New Clients : ";
    cout << "\n-----------------------------------" << endl;

    Add_new_Client();
}

static void Find_client_screen()
{
    cout << "\n-----------------------------------" << endl;
    cout << "\tFind Client : ";
    cout << "\n-----------------------------------" << endl;

    vector <s_Client> vClients = Load_cleints_data_from_file(path_name);
    s_Client Client;
    string AccountNumber = Read_account_number_of_number();
    if (find_client_by_account_number(AccountNumber, vClients, Client))
        Print_Client_Card(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

static void Ene_program_screen()
{
    cout << "\n-----------------------------------" << endl;
    cout << "\tProgram Ends ...";
    cout << "\n-----------------------------------" << endl;
}



static void Go_back()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    Main_Menue();
}

static short read_user_choice()
{
    short choice;
    do
    {
        cout << "Choose what do you want to do? [1 to 7] :   ";
        cin >> choice;
    } while (choice < 1 || choice > 7);

    return choice;
}

static short	choice_Transactions()
{
	short choice;
    do
    {
        cout << "Choose what do you want to do? [1 to 4] :   ";
        cin >> choice;
    } while (choice < 1 || choice > 4);

    return (choice);
}

static double Read_deposit_amount()
{
	double	amount;

	do
	{
		cout << "Please enter deposit amount ?  ";
		cin >> amount;
	} while (amount < 0);
	return (amount);
}

static void	Change_deposit_amount(string AccountNumber, double amount,vector <s_Client>& vClients)
{
	char	accept;
    cout << "Are you sure you want perform this transaction? y/n ?  ";
	cin >> accept;

    if (accept == 'y' || accept == 'Y')
    {
        for (s_Client& C : vClients)
        {
            if (C.account_number == AccountNumber)
            {
                C.account_balance += amount;
                SaveCleintsDataToFile(path_name, vClients);
                cout << endl << "Amount Added Successfully :  " << C.account_balance << endl;
                break;
            }
        }
    }
}

static void	ft_Deposit()
{

	vector <s_Client> vClients;
	s_Client Client;
	string AccountNumber;

	vClients = Load_cleints_data_from_file(path_name);
    AccountNumber = Read_account_number_of_number();
    while (!find_client_by_account_number(AccountNumber, vClients, Client))
    {
        cout << "\nClient with Account Number[" << AccountNumber << "] does not exist!";
        AccountNumber = Read_account_number_of_number();
    }
    Print_Client_Card(Client);
    double amount = Read_deposit_amount();
    Change_deposit_amount(AccountNumber, amount, vClients);

}

static void Go_Back_To_Transactions_Menue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    Transactions_screen();

}
static void	Deposit_screen()
{
	cout << "\n-----------------------------------" << endl;
    cout << "\t Deposit Screen : ";
    cout << "\n-----------------------------------" << endl;

    ft_Deposit();
}

static void	Withdraw_screen()
{
	cout << "\n-----------------------------------" << endl;
    cout << "\t Withdraw Screen : ";
    cout << "\n-----------------------------------" << endl;

    vector <s_Client> vClients;
	s_Client Client;
	string AccountNumber;

	vClients = Load_cleints_data_from_file(path_name);
    AccountNumber = Read_account_number_of_number();
    while (!find_client_by_account_number(AccountNumber, vClients, Client))
    {
        cout << "\nClient with Account Number[" << AccountNumber << "] does not exist!";
        AccountNumber = Read_account_number_of_number();
    }
    Print_Client_Card(Client);
    double amount;

    cout <<  endl << "Please enter withdraw amount? : ";
    cin >> amount;

    while (Client.account_balance < amount)
    {
        cout << endl << "Amount Exceeds the balance, you can withdraw up to : " << Client.account_balance<< endl;
        cout << "Please enter another amount? ";
        cin >> amount;
    }

    Change_deposit_amount(AccountNumber, amount * (-1), vClients);
}

static void print_client_balance(s_Client Client)
{
    cout << "| " << setw(18) << left << Client.account_number;
    cout << "| " << setw(40) << left << Client.user_name;
    cout << "| " << setw(15) << left << Client.account_balance;
}

static void Total_Balances_screen()
{
    double Total_balances = 0;
    vector <s_Client>    v_Client;
    v_Client = Load_cleints_data_from_file(path_name);

    cout << "\n\t\t\tBalances List(" << v_Client.size() << ") Client (s). " << endl;
    cout << " ___________________________________________________________________________________________\n" << endl;
    cout << "| " << left << setw(18) << "Account Number ";
    cout << "| " << left << setw(40) << "Client Name ";
    cout << "| " << left << setw(15) << "Balance ";
    cout << "\n ___________________________________________________________________________________________\n" << endl;

    if (v_Client.size() == 0)
        cout << "\t\tNo Clients Available In the System!";
    else
    {
        for (s_Client &one_client : v_Client)
        {
            print_client_balance(one_client);
            Total_balances += one_client.account_balance;
            cout << endl;
        }
    }
    cout << " ___________________________________________________________________________________________\n" << endl;


    cout << "\t\t\t  Total Balances = " << Total_balances << endl;
}

static void	Transactions_Menue_option(e_transactions_option option)
{
	switch (option)
	{
	case e_transactions_option::Deposit :
    {
		system ("clear");
		Deposit_screen();
        Go_Back_To_Transactions_Menue();
		break;
    }

	case e_transactions_option::Withdraw : 
    {
		system ("clear");
		Withdraw_screen();
        Go_Back_To_Transactions_Menue();
		break;
    }

    case e_transactions_option::Total_Balances : 
    {
		system ("clear");
		Total_Balances_screen();
        Go_Back_To_Transactions_Menue();
		break;
    }

    case e_transactions_option::return_Main_Menue : 
    {
		Main_Menue();
		break;
    }
	}

}

static void	Transactions_screen()
{
	cout << "\n======================================" << endl;
    cout << "\tTransactions Menue Screen : ";
    cout << "\n======================================" << endl;

	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n" << endl;

	Transactions_Menue_option ((e_transactions_option) choice_Transactions());
}

static void Main_Menu_Option(e_Menue_option option)
{
    switch (option)
    {
    case e_Menue_option::list_client:
    {
        system("clear");
        show_screen();
        Go_back();
        break;
    }
    case e_Menue_option::add_new_client:
       system("clear");
        Add_newClient_screen();
        Go_back();
        break;

    case e_Menue_option::delet_client:
        system("clear");
        delet_client_screen();
        Go_back();
        break;

    case e_Menue_option::update_client:
        system("clear");
        update_client_screen();
        Go_back();
        break;

    case e_Menue_option::find_client:
       system("clear");
        Find_client_screen();
        Go_back();
        break;

    case e_Menue_option::Transaction :
        system("clear");
        Transactions_screen();
        Go_back();
        break;

    case e_Menue_option::Exit:
        system("clear");
        Ene_program_screen();
        break;
    }
}

void Main_Menue()
{
    system("clear");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "===========================================\n";
    Main_Menu_Option((e_Menue_option)read_user_choice());
}

int main()
{
    Main_Menue();

    return (0);
}
