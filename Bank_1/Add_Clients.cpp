#include "Bank_1.hpp"

static vector<string> split_string(string Line, string delim)
{
    string s_word;
    vector <string> v_client;
    int pos;

    while ((pos = Line.find(delim)) != std::string::npos)
    {
        s_word = Line.substr(0, pos);
        if (s_word != "")
        {
            v_client.push_back(s_word);
        }
        Line.erase(0, pos + delim.length());
    }
    if (Line != "")
    {
        v_client.push_back(Line);
    }
    return (v_client);
}

static Client ConvertLinetoRecord(string Line, string delim)
{
    vector <string> v_client;
    Client s_client;

    v_client = split_string(Line, delim);

    s_client.account_number = v_client[0];
    s_client.pin_code = v_client[1];
    s_client.user_name = v_client[2];
    s_client.phone = v_client[3];
    s_client.account_balance = v_client[4];
	
    return (s_client);
}
static bool is_it_added_before(string account_number, string path_name)
{
    vector <Client> v_client;
    fstream My_File;

    My_File.open(path_name, ios::in);
    if (My_File.is_open())
    {
        string line;
        Client s_client;
        while (getline(My_File, line))
        {
            s_client = ConvertLinetoRecord(line, "#//#");
            if (s_client.account_number == account_number)
            {
                My_File.close();
                return (true);
            }
            v_client.push_back(s_client);
        }
    }
    My_File.close();
    return (false);
}

static Client	Read_client_info(void)
{
	Client client_data;

    cout << "Enter Account Number? " << endl;
    getline(cin >> std::ws, client_data.account_number);

    while (is_it_added_before(client_data.account_number, path_name))
    {
        cout << "\nClient with [" << client_data.account_number << "] already exists. Enter another account number : ";
        getline(cin >> std::ws, client_data.account_number);
    }

    cout << "Enter Pin code? " << endl;
    getline(cin, client_data.pin_code);

    cout << "Enter Name? " << endl;
    getline(cin, client_data.user_name);

    cout << "Enter phone? " << endl;
    getline(cin, client_data.phone);

    cout << "Enter Account Balance? " << endl;
    getline(cin, client_data.account_balance);

    return client_data;

}

static string	ConvertRecordToLine(Client client, string delim = "#//#")
{
    string line = "";

    line += client.account_number + delim;
    line += client.pin_code + delim;
    line += client.user_name + delim;
    line += client.phone + delim;
    line += client.account_balance;

    return line;
}

static void	Add_data_to_File(string Line, string path_name)
{
    fstream My_File;

    My_File.open(path_name, ios::out | ios::app);
    if (My_File.is_open())
    {
        My_File << Line << endl;
        My_File.close();
    }
}

static void Add_new_client()
{
    Client client_data;
    client_data = Read_client_info();
    Add_data_to_File(ConvertRecordToLine(client_data, "#//#"), path_name);
}

void Add_Clients(void)
{

    cout << "_______________________________________\n"<< endl;
    cout << "\t\tAdd new client";
    cout << "\n_______________________________________"<< endl;
    char flag;
    do
    {
        system("clear");
        cout << "\tAdding new client : \n" << endl;
        Add_new_client();
        cout << "\nClient Added Successfully\nDo you want to add more Client (Y / N)? : " << endl;
        cin >> flag;
		if (flag == 'n' || flag == 'N')
			return ;

    } while (toupper(flag) == 'Y');
}
