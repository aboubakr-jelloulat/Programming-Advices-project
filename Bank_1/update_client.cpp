#include "Bank_1.hpp"

static vector<string> split_string(string Line, string delim)
{
    vector<string> v_client;
    string s_word;
    size_t pos = 0;

    while ((pos = Line.find(delim)) != std::string::npos)
    {
        s_word = Line.substr(0, pos);
        if (!s_word.empty())
        {
            v_client.push_back(s_word);
        }
        Line.erase(0, pos + delim.length());
    }
    if (!Line.empty())
    {
        v_client.push_back(Line);
    }

    return v_client;
}

Client ConvertLinetoRecord(string Line, string delim)
{
    vector<string> v_client = split_string(Line, delim);
    Client s_client;

    s_client.account_number = v_client[0];
    s_client.pin_code = v_client[1];
    s_client.user_name = v_client[2];
    s_client.phone = v_client[3];
    s_client.account_balance = v_client[4];

    return s_client;
}

static string ConvertRecordToLine(Client client, std::string delim = "#//#")
{
    string line = "";

    line += client.account_number + delim;
    line += client.pin_code + delim;
    line += client.user_name + delim;
    line += client.phone + delim;
    line += client.account_balance;

    return line;
}

vector<Client> LoadCleintsDataFromFile(string file_name)
{
    vector<Client> v_client;
    fstream MyFile;

    MyFile.open(file_name, ios::in);
    if (MyFile.is_open())
    {
        string line;
        while (getline(MyFile, line))
        {
            Client s_data_one_client = ConvertLinetoRecord(line, "#//#");
            v_client.push_back(s_data_one_client);
        }
        MyFile.close();
    }
    return v_client;
}

string Read_user_account_number()
{
    string acc_nb;

    cout << "\nPlease enter account number of client: ";
    getline(cin >> ws, acc_nb);

    return acc_nb;
}

bool search_client_account_number(string account_number, vector<Client> v_client, Client &v_save)
{
    for (Client s : v_client)
    {
        if (s.account_number == account_number)
        {
            v_save = s;
            return true;
        }
    }
    return false;
}

void PrintClientCard(Client s_client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccount Number: " << s_client.account_number;
    cout << "\nPin Code: " << s_client.pin_code;
    cout << "\nName: " << s_client.user_name;
    cout << "\nPhone: " << s_client.phone;
    cout << "\nAccount Balance: " << s_client.account_balance;
}

bool Mark_client_for_delet(string account_number, vector<Client> &v_client)
{
    for (Client &c : v_client)
    {
        if (c.account_number == account_number)
        {
            c.Mark_for_delet = true;
            return (true);
        }
    }
    return (false);
}
vector<Client> Save_Client_data_to_file(string path_name, vector<Client> v_client)
{
    fstream My_File;
    string line;
    My_File.open(path_name, ios::out);
    if (My_File.is_open())
    {
        for (Client s : v_client)
        {
            if (s.Mark_for_delet == false)
            {
                line = ConvertRecordToLine(s, "#//#");
                My_File << line << endl;
            }
        }
        My_File.close();
    }
    return (v_client);
}

Client	ChangeClientRecord (string account_number)
{
	Client client_data;

    client_data.account_number = account_number;

    cout << "Enter Pin code? " << endl;
    getline(cin >> ws, client_data.pin_code);

    cout << "Enter Name? " << endl;
    getline(cin, client_data.user_name);

    cout << "Enter phone? " << endl;
    getline(cin, client_data.phone);

    cout << "Enter Account Balance? " << endl;
    getline(cin, client_data.account_balance);

    return client_data;

}
bool	save_change_updating(string account_number, vector<Client> &v_client)
{
	Client s_client;
    char    is_delet = 'N';

    if (search_client_account_number(account_number, v_client, s_client))
    {
        PrintClientCard(s_client);
    
        cout << endl << "Are you sure you want update this client y/n ? " << endl;
        cin >> is_delet;
        if (is_delet == 'Y' || is_delet == 'y')
        {
            for (Client &s : v_client)
			{
				if (s.account_number == account_number)
				{
					s = ChangeClientRecord (account_number);
					break;
				}
			}
			Save_Client_data_to_file(path_name, v_client); // hna

            cout << "\n\tClient Update Successfully.";
            return (true);
        }
    }
    cout << "\nClient with Account Number (" << account_number << ") is Not Found!" << endl;
    return (false);
}

void Update_Client(void)
{
    cout << "_______________________________________\n"<< endl;
    cout << "\t\tUpdate client";
    cout << "\n_______________________________________"<< endl;
    string account_number = Read_user_account_number();
    vector<Client> v_client = LoadCleintsDataFromFile(path_name);

    save_change_updating (account_number, v_client);
   
}
