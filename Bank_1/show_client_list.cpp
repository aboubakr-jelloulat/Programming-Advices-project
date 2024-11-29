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

static void PrintClientRecord(Client Client)
{
    cout << "| " << setw(15) << left << Client.account_number;
    cout << "| " << setw(10) << left << Client.pin_code;
    cout << "| " << setw(40) << left << Client.user_name;
    cout << "| " << setw(12) << left << Client.phone;
    cout << "| " << setw(12) << left << Client.account_balance;
}

void  PrintAllClientsData(void)
{
	vector <Client> vClients = LoadCleintsDataFromFile(path_name);

    cout << "\n\t\t\tClient List (" << vClients.size() << ") Client(s)." << endl;

    cout << "\n _________________________________________________________________________________________________" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n _________________________________________________________________________________________________" << endl;

    for (Client Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "| ________________________________________________________________________________________________" << endl;

}
