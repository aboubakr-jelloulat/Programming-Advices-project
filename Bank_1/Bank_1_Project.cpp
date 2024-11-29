#include "Bank_1.hpp"

enum	en_Main_option {list_client = 1, add_client = 2, delet_client = 3, update_client = 4, find_client = 5, Exit = 6};

static void	Show_Main_Menue(void);

static short	Read_user_choice(void)
{
	short	choice;
	do
	{
		cout << "Choose what do you want to do? [1 to 6] :   ";
		cin >> choice;
	} while (choice < 1 || choice > 6);

	return (choice);
}

static void	Go_back_to_Main_Menu(void)
{
	cout << "\n\nPress any key to go back to Main Menue ..." << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
	Show_Main_Menue();
}

static void	End_Screen(void)
{
	cout << "\n___________________________" << endl;
	cout << "\tProgram Ends ";
	cout << "\n___________________________" << endl;
}

static void	Execute_Maine_option (en_Main_option	Main_option)
{
	switch (Main_option)
	{
		case en_Main_option::list_client :
			system("clear");
			PrintAllClientsData();
			Go_back_to_Main_Menu();
			break;
		case en_Main_option::add_client :
			system("clear");
			Add_Clients();
			Go_back_to_Main_Menu();
			break;
		case en_Main_option::delet_client :
			system("clear");
			Delet_client();
			Go_back_to_Main_Menu();
			break;
		case en_Main_option::update_client :
			system("clear");
			Update_Client();
			Go_back_to_Main_Menu();
			break;
		case en_Main_option::find_client : 
			system("clear");
			Find_client();
			Go_back_to_Main_Menu();
			break;
		case en_Main_option::Exit :
			system("clear");
			End_Screen();
			break;
	}

}

static void	Show_Main_Menue(void)
{
	system("clear");
	cout << "==========================================" << endl;
	cout << "\t\tMain Menue Screen\n";
	cout << "==========================================" << endl;
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delet Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit.\n";

	cout << "==========================================\n" << endl;
	Execute_Maine_option ((en_Main_option) Read_user_choice());

}

void	bank_1_project(void)
{
	Show_Main_Menue();
}

int main (void)
{
	bank_1_project();
	return (0);
}
