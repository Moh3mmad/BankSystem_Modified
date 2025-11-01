#include<iostream>
#include<string>
#include<iomanip>
#include <fstream>
#include <vector>

using namespace std;

const string ClientFileNameForBankP = "ClientFileNameForBankP.txt";

void ShowMainMenu();


struct stClient 
{
	string AccountNumber;
	string  PinCode;
	string Name;
	string phone;
	double AccountBalance;
	bool MarkClientDelte = false;

};

string ReadAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	getline(cin>>ws, AccountNumber);
	return AccountNumber;
}

vector<string> SplitString(string Line, string Seperator = "#//#")//d
{
	vector <string> vClient;
	string LWords;
	int pos;
	while ((pos = Line.find(Seperator)) != std::string::npos)
	{
		LWords = Line.substr(0, pos);
		if (LWords != "")
		{
			vClient.push_back(LWords);
		}

		Line.erase(0, pos + Seperator.length());
	}
	if (Line != "")
		vClient.push_back(Line);

	return vClient;
}

string ConvertRecordToLine(stClient& Client, string Seperator = "#//#")//d
{
	string Line = "";
	Line += Client.AccountNumber + Seperator;
	Line += Client.PinCode + Seperator;
	Line += Client.Name + Seperator;
	Line += Client.phone + Seperator;
	Line += to_string(Client.AccountBalance);

	return Line;
}

stClient ConvertLineToRecord(string Line)
{
	stClient LoadClient;
	vector <string> vClientData = SplitString(Line);

	LoadClient.AccountNumber = vClientData[0];
	LoadClient.PinCode = vClientData[1];
	LoadClient.Name = vClientData[2];
	LoadClient.phone = vClientData[3];
	LoadClient.AccountBalance = stod(vClientData[4]);

	return LoadClient;
}

void LoadDataFromClientToFile(vector <stClient>& vClient)
{
	fstream MyFile;
	MyFile.open(ClientFileNameForBankP, ios::out);// | ios::app

	string Line = "";
	if (MyFile.is_open())
	{
		for (stClient& C : vClient)
		{
			if (C.MarkClientDelte == false)
			{
				MyFile << ConvertRecordToLine(C) << endl;
			}

		}
		MyFile.close();
	}
}

vector<stClient> LoadDataFromFileToClient()
{
	fstream MyFile;
	MyFile.open(ClientFileNameForBankP, ios::in);

	string Line;
	vector <stClient> vClient;
	stClient Client;

	if (MyFile.is_open())
	{
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return vClient;
}

bool ClientExistByAccountNumber(string AccountNumber, string FileName)
{
	fstream MyFile;
	vector <stClient> vClient;
	MyFile.open(FileName, ios::in);//read mode

	if (MyFile.is_open())
	{
		string Line;
		stClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}

stClient ReadNewClient()
{
	stClient Client;

	cout << "Enter Account Number ?";
	// Usage of std::ws will extract allthe whitespace character
	getline(cin>>ws,Client.AccountNumber);

	while (ClientExistByAccountNumber(Client.AccountNumber, ClientFileNameForBankP))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exist, Enter another Account Number ?";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PinCode ?";
	getline(cin, Client.PinCode);

	cout << "Enter Name ?";
	getline(cin, Client.Name);

	cout << "Enter Phone ?";
	getline(cin, Client.phone);

	cout << "Enter Account Balance ?";
	cin >> Client.AccountBalance;
	cin.ignore();

	return Client;

}

void PrintClientRecordLine(stClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.phone;
	cout << "| " << setw(12) << left << Client.AccountBalance<<"|";

}

void ShowAllClientsScreen()
{

	vector <stClient> vClient = LoadDataFromFileToClient();
	cout << "\n\t\t\t\t\tClient List (" << vClient.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_____________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance"<<"|";
	cout << "\n_______________________________________________________";
	cout << "_____________________________________________\n" << endl;


	if (vClient.size()== 0)
	{
		cout << "\t\t\t\tNo Clients Available In the System!";

	}
	else
	{

		for (stClient& C : vClient)
		{

			PrintClientRecordLine(C);

			cout << endl;
		}

		cout << "\n_______________________________________________________";
		cout << "_____________________________________________\n" << endl;
	}


}

void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
	}
	MyFile.close();
}

void AddNewClient()
{
	stClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientFileNameForBankP, ConvertRecordToLine(Client));
}
 
void AddNewClients()
{
	char AddMore = 'Y';
	do
	{
		cout << "Adding New Client:\n\n";
		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');

}

void ShowAddNewClientsScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";

	AddNewClients();
}

void PrintClientCard(stClient& Client)
{
	cout << "The Following Are The Client Details :";
	cout << "\n------------------------------------------------\n";
	cout << "Account Number :" << Client.AccountNumber << endl;
	cout << "Pin Code       :" << Client.PinCode << endl;
	cout << "Name           :" << Client.Name << endl;
	cout << "Phone          :" << Client.phone << endl;
	cout << "Account Balance :" << Client.AccountBalance << endl;
	cout << "\n------------------------------------------------\n";

}

bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClient,stClient &Client)
{

	for (stClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C; // Data Of Client Marked/found
			return true;

		}
	}
	return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClient)
{

	for (stClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkClientDelte = true;
			return true;

		}
	}
	return false;
}

bool DeleteClientByAccountNumber(string AccountNumber , vector <stClient>&vClient)
{

	stClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClient);
			LoadDataFromClientToFile(vClient);

			//Refresh Clients 
		//	vClient = LoadDataFromFileToClient(); not necessary
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}

	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
	

}

void ShowDeleteClient()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";
	vector <stClient> vClient = LoadDataFromFileToClient();
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClient);

}

stClient GetClientUpdatting(string AccountNumber)
{
	stClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode ?";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name ?";
	getline(cin, Client.Name);

	cout << "Enter Phone ?";
	getline(cin, Client.phone);

	cout << "Enter Account Balance ?";
	cin >> Client.AccountBalance;


	return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber,vector<stClient>&vClient)
{
	stClient Client;
	char Answer = 'y';

	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want update this client? y/n ? ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			for (stClient& C : vClient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = GetClientUpdatting(AccountNumber);
					break;//return of this loop
				}
			}

			LoadDataFromClientToFile(vClient);
			cout << "\n\nClient Updated Successfully.";
			return true;

		}

	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}




}

void ShowUpdateClient()
{
	cout << "\n-----------------------------------\n";
	cout << "\nUpdate Client Screen";
	cout << "\n-----------------------------------\n";

	string AccountNumber = ReadAccountNumber();
	vector <stClient> vClient = LoadDataFromFileToClient();
	UpdateClientByAccountNumber(AccountNumber, vClient);
}

void ShowFindClientScreen()
{

	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";

	string AccountNumber = ReadAccountNumber();

	vector <stClient> vClient = LoadDataFromFileToClient();

	stClient Client;
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintClientCard(Client);
	}
	else
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

	
}

void ShowEndScreen()
{

	cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	cout << "\t\tProgram Ends :-)";
	cout << "\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";

}

enum enMainMenueOptios {
	enListClients = 1, enAddNewClient = 2, enDeleteClient = 3,
	enUpdateClient = 4, enFindClient = 5, enExit = 6

};

void GoBackToMainMenu()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenu();


}

short ReadMainMenuOption()
{
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}

void PerfromMainMenueOption(enMainMenueOptios MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOptios::enListClients:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenu();
		break;
	

	case enMainMenueOptios::enAddNewClient :
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenu();
		break;
	
	case enMainMenueOptios::enDeleteClient :
		system("cls");
		ShowDeleteClient();
		GoBackToMainMenu();
		break;
	
	case enMainMenueOptios::enUpdateClient :
		system("cls");
		ShowUpdateClient();
		GoBackToMainMenu();
		break;
	

	case enMainMenueOptios::enFindClient :
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;
	
	case enMainMenueOptios::enExit :
		system("cls");
		ShowEndScreen();
		break;
	
	}
}

void ShowMainMenu()
{

	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit.\n";
	cout << "===========================================\n";
	PerfromMainMenueOption((enMainMenueOptios)ReadMainMenuOption());
}

int main()
{

	ShowMainMenu();
	system("pause>0");

}