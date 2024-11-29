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

static vector <Client> LoadCleintsDataFromFile(string file_name)
{
    fstream MyFile;
    vector <Client> v_client;

    MyFile.open(file_name, ios::in);
    if (MyFile.is_open())
    {
        string line;
        Client s_data_one_client;
        while (getline(MyFile, line))
        {
            s_data_one_client = ConvertLinetoRecord(line, "#//#");
            v_client.push_back(s_data_one_client);
        }
        MyFile.close();
    }
    return (v_client);
}

static string Read_user_account_number(void)
{
	string acc_nb;

	cout << "Please enter account number of client : " << endl;
	getline (cin >> std::ws, acc_nb);

	return (acc_nb);
}

static bool	search_client_account_number(string account_number, Client &v_save)
{
	vector <Client> v_client;

    v_client = LoadCleintsDataFromFile(path_name);
	for (Client s : v_client)
	{
		if (s.account_number == account_number)
		{
			v_save = s;
			return (true);
		}
	}
	return (false);
}

static void PrintClientCard(Client s_client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << s_client.account_number;
	cout << "\nPin Code : " << s_client.pin_code;
	cout << "\nName : " << s_client.user_name;
	cout << "\nPhone : " << s_client.phone;
	cout << "\nAccount Balance: " << s_client.account_balance;
}

bool	Find_client(void)
{
	cout << "_______________________________________\n"<< endl;
    cout << "\t\tFind new client";
    cout << "\n_______________________________________"<< endl;
	string account_number;
	Client v_client;

	account_number = Read_user_account_number();
	if (search_client_account_number(account_number, v_client))
	{
		PrintClientCard(v_client);
		return (true);
	}
	else
	{
		cout << "\nClient with Account Number (" << account_number << ") is Not Found!" << endl;
		return (false);
	}	

}
