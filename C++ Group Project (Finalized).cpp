/* ====================== GROUP 4 ===========================  */
/* Name: ASYRAF                                    (A25DWxxxx) */
/* Name: HAIDHAR                                   (A25DWxxxx) */
/* Name: FIRAS                                     (A25DWxxxx) */
/* Name: FITRI                                     (A25DWxxxx) */
/* Name: AISHWARRYA                                (A25DWxxxx) */
/* ==================== SECTION 45 =========================== */

//Firas begin
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cctype>
#include <iomanip>
#include <windows.h>

using namespace std;
bool isNumber(const string &input);

class User {
	
	protected:
		int userID;
		string username;
		double balance;
	
	public:
	    User(int id, string name, double bal) {
	    	userID = id;
	    	username = name;
	    	balance = bal;
	    	
		}
		
	    ~User() {
		
	}
	
	void setName (string name) {
        username = name;
    }

    void setBalance (double bal) {
        balance = bal;
    }
	
	void setId (int id){
		userID = id;
	}
	
	string getName() {
        return username;
    }

    double getBalance() {
        return balance;
    }
    
    int getID () {
    	return userID;
	}
	
	virtual void display() {
		cout << "User ID: " << userID << endl;
		cout << "Username: " << username << endl;
		cout << "Balance: RM " << balance << endl;
		
		
	}
	
	friend void displayUserDetails(const User &u);
		
};

//Firas end
//Haidhar start

class Bank {
	
	private:
		int bankID;
		static double sharedBalance;
		string bankName;
		
	public:
		
		Bank(int bId, string bName){
		
			bankName = bName;
			bankID = bId;
					
		}
		
		void setbankNum(int bId){
			bankID = bId;
		}
		
		void setbankName(string bName){
			bankName = bName;
		}
		
		int getbankID(){
			return bankID;
		}
				
		string getbankName(){
			return bankName;
		}
				
		static double getBalance() { 
		    return sharedBalance; 
		}
		
		static void showBalance() {
        cout << "Bank System Balance: \033[33mRM " << sharedBalance << "\033[0m" << endl;
        }
        
        static bool transferToUser(User &u, double amount) {

        if (sharedBalance >= amount) {
            sharedBalance -= amount;
            u.setBalance(u.getBalance() + amount);
            cout << "\033[32mTransfer Successful!\033[0m\n";
            return true;
        }
        else {
            cout << "\033[31mBank has insufficient funds!\033[0m\n";
            return false;
        }
    }
    
    void saveBankTransaction(double amount) {	//create and open file transaction2.txt
	    ofstream outFile("transaction2.txt", ios::app);
		outFile << "Bank: " << bankName
		        << " | Amount Transfered: RM " << amount
		        << " | Balance: RM " << sharedBalance << endl;
		outFile.close();
		
	}
	
	void viewTransaction2() {	
		ifstream inFile("transaction2.txt"); // retrieve transaction2.txt contents
		string line;
		
		cout << "\n\033[47m\033[34m==================== BANK TRANSACTION HISTORY ====================\033[0m\n\n";
		while(getline(inFile, line)) {
			cout << line << endl;
			
		}
		
		inFile.close();
		cout << "\n\033[47m\033[34m==================================================================\033[0m\n";
	}
	
	static void clearTransactions() { //clear or delete the file
		remove("transaction2.txt");
	}
};

double Bank::sharedBalance = 10000.00; // all banks share same balance to the lessen complexity

//Haidhar end
//Asy start

void idNew(User &u) {//int checker, making sure that if the input has non-digits it will not proceed to the next line of code
    
        
        if (u.getID() == 0) {
        string input;// will convert string to int later

        while (true) {
            cout << "Enter your ID (numbers only): ";
            cin >> input;

            if (!isNumber(input)) {//check if the input is digit or not
                cout << "\033[31mInvalid input! Please enter digits only.\033[0m\n";
                continue;
            }

            long long int id = stoll(input);   // convert safely from strings to int 64-bits
												// a.k.a fail safe
            if (id <= 0) {
                cout << "ID must be greater than 0.\n";
                continue;
            }

            u.setId(id); //it will change the id of in the user class, indirectly change the protected id declaration
            break;
        }
    }
}
	
class RechargeUser; //tells the compiler that class rechargeUser wujud. 
					//if put somewhere not near ontop of  class RechargeUser, it will not get the value
void statusConfirmation(RechargeUser &user, string answer, int diamonds, double price);// need to have function prototype near reacharge user.

class RechargeUser : public User {
	private:
		int diamonds;
		
	public:
		RechargeUser(int id, string name, double bal, int dia)
		    : User(id, name, bal) {
		    	diamonds = dia;
		    			    	
			}
			
		~RechargeUser() {
					
	}
		
	void display() override {//user information override from display function() in class User
		cout <<"\n\033[47m\033[34m=========  USER DETAILS  ========\033[0m\n";
			
		cout << "\n\tUser ID  : " << userID;
		cout << "\n\tUsername : " << username;
		cout << "\n\tBalance  : RM " << balance;
		cout << "\n\tDiamond  : " << diamonds << endl;
		
		cout << "\n\033[47m\033[34m---------------------------------\033[0m\n\n";
		
	}
	
	void recharge(int diamondAmount, double price) {// recharge diamond function
		
		if (balance >= price) {
			balance -= price;
			diamonds += diamondAmount;
			cout << "\033[32mRecharge Successful!\033[0m\n\n";
			saveTransaction(diamondAmount, price); //forward the price and amount to saveTransaction() function
			
		} else {
			cout << "\n\033[31mInsufficient Balance!\033[0m\n";
			
		}
		
	}
	
	void saveTransaction(int diamondAmount, double price) {	//the value gotten recharge() function will display and sorted here
	    ofstream outFile("transaction.txt", ios::app);
		outFile << "Username: " << username
		        << " | Diamonds Bought: " << diamondAmount
		        << "  Price: RM " << price << endl;
		outFile.close();
		
	}
	
	void viewTransaction() {	
		ifstream inFile("transaction.txt");
		string line;
		
		cout << "\n\033[47m\033[34m======================== TRANSACTION HISTORY ========================\033[0m\n\n";
		while(getline(inFile, line)) {// open transaction.txt file and cout the contents
			cout << line << endl;
			
		}

		inFile.close(); //close the .txt file
		cout << "\n\033[47m\033[34m=====================================================================\033[0m\n";	            
	}
	
	static void clearTransactions() {// clear the transaction to not intefere in the next programme run
		remove("transaction.txt");
	}
			
	friend void displayUserDetails(const User &u) {//display user details but not much
	cout << "\n\033[47m\033[34m----------- Friend Function Access -----------\033[0m\n\n";
	cout << "\tUsername : " << u.username << endl;
	cout << "\tBalance  : RM " << u.balance << "\n\n";
	cout << "\033[47m\033[34m----------------------------------------------\033[0m\n\n";
    }	            
};

void statusConfirmation(RechargeUser &user, string answer, int diamonds, double price)
{//the code will accept these forms of yes to proceed to recharge
    if (answer == "YES" || answer == "yes" || answer == "Yes" || answer == "y" || answer == "Y") {
        cout << "\n\033[32mPayment Is Successful\033[0m\n";
        user.recharge(diamonds, price);
    }
    else {//if the input besides the yes forms
        cout << "\033[41m\033[37mPayment Is Unsuccessful\033[0m\n\n";
    }
}

//Asy end
//Haidhar start

void Menu(){// diamond recharge menu + text colouring
	cout << "\t\033[33m ---------------------------------------\033[0m\n";
	cout << "\t\033[33m|\033[0m";
	cout << "\033[47m\033[34m    Diamond Amount     \033[0m\033[47m\033[33m|\033[0m\033[47m\033[34m    Price (RM) \033[0m";
	cout << "\033[33m|\033[0m\n";
	cout << "\t\033[33m|\033[47m---------------------------------------\033[0m\033[33m|\033[0m\n";
	
	cout << "\t\033[33m|\033[0m" << "\033[47m\033[34m 1. 14                 \033[0m";
	cout << "\033[47m\033[33m|\033[0m";
	cout << "\033[47m\033[34m1.09           \033[0m\033[33m|\033[0m\n\t";
	
	cout << "\033[33m|\033[0m" << "\033[47m\033[34m 2. 100+34             \033[0m";
	cout << "\033[47m\033[33m|\033[0m";
	cout << "\033[47m\033[34m8.96           \033[0m\033[33m|\033[0m\n\t";
	
	cout << "\033[33m|\033[0m" << "\033[47m\033[34m 3. 246+40             \033[0m";
	cout << "\033[47m\033[33m|\033[0m";
	cout << "\033[47m\033[34m18.43          \033[0m\033[33m|\033[0m\n\t";
		
	cout << "\033[33m|\033[0m" << "\033[47m\033[34m 4. 412+67             \033[0m";
	cout << "\033[47m\033[33m|\033[0m";
	cout << "\033[47m\033[34m35.67          \033[0m\033[33m|\033[0m\n\t";

	cout << "\033[33m|\033[0m" << "\033[47m\033[34m 5. 758                \033[0m";
	cout << "\033[47m\033[33m|\033[0m";
	cout << "\033[47m\033[34m55.28          \033[0m\033[33m|\033[0m\n\t";
	
	cout << "\033[33m|\033[0m" << "\033[47m\033[34m 6. 1024+120           \033[0m";
	cout << "\033[47m\033[33m|\033[0m";
	cout << "\033[47m\033[34m83.43          \033[0m\033[33m|\033[0m\n";
	
	cout << "\t\033[33m ---------------------------------------\033[0m\n";
	
}

void showBankMenu(Bank banks[], int size) {//show bank by using for loop
    cout << "\n\033[47m\033[34m======== SELECT BANK ========\033[0m\n\n";
    for (int i = 0; i < size; i++) {
        cout << "\t" << banks[i].getbankID() << ". " << banks[i].getbankName() << endl;
    }
    cout << "\n\033[47m\033[34m==============================\033[0m\n";
}

bool isNumber(const string &input) {//
    if (input.empty()) return false;

    for (char c : input) {
        if (!isdigit(c)) {
            return false;   // for not digit
        }
    }
    return true;
}

//Haidhar end
//Asy start

void enableANSI() {// to enable windows 10 to unlock ANSI Escape Code to work
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

int main() {
	enableANSI(); // for windows 10 terminal
	//colour use ANSI Escape Code Colour, may need newer terminal(windows 11) to have colour to show up properly
	
	//Asy end
	//Fir start
	
	Bank banks[] = {// list of banks
        Bank(1, "Maybank"),
        Bank(2, "CIMB"),
        Bank(3, "Public Bank"),
        Bank(4, "RHB")
    };

    int totalBanks = 4;
	
	RechargeUser user1(0, "Haidhar", 100.00, 50);//this is user member created, giving specific info to them
	cout << "\033[36m";
	idNew(user1); //ask to input id and check whether the input id is all in digits 
	cout << "\033[0m";
	
	int choice, menu_ch;
	string answer;
	
	do {
	

    cout << "\033[47m\033[35m ------------------------------------------------------------------------------ \033[0m\n";
    cout << "\033[47m\033[35m|                         RECHARGE ONLINE SYSTEM                               |\033[0m\n";
    cout << "\033[47m\033[35m|                                                                              |\033[0m\n";

    cout << "\033[47m\033[35m|   1. Display User Info               2. Recharge Diamonds                    |\033[0m\n";

    cout << "\033[47m\033[35m|   3. Bank Transfer                   4. View Transaction History             |\033[0m\n";

    cout << "\033[47m\033[35m|   5. Friend Function Display         6. Exit                                 |\033[0m\n";

    cout << "\033[47m\033[35m|                                                                              |\033[0m\n";
    cout << "\033[47m\033[35m ------------------------------------------------------------------------------ \033[0m\n";

		cout << "\033[36mEnter choice: ";
		cin >> choice;
		cout << "\033[0m";
		
		switch (choice) {
			
			case 1:
						
				user1.display(); // display user info that has been put in RechargeUser user1(xxx, "xxx", xx.xx, xx)
				break;
// Fir end				
//Haidhar start				
			case 2:
				
				Menu();
				cin >> menu_ch;
				switch (menu_ch){
					case 1:
					    cout << "\nType \033[32mYes\033[0m to confirm: ";
					    cin >> answer;
					    
						statusConfirmation(user1, answer, 14, 1.09); // member pointer towards class User, receive answer to correspond to which menu of recharge 
						break;                                      // will be initiate via diamond and price
						
					case 2:
						cout << "\nType \033[32mYes\033[0m to confirm: ";
                        cin >> answer;
                        
						statusConfirmation(user1, answer, 134, 8.96);
						break;
						
					case 3:
						cout << "\nType \033[32mYes\033[0m to confirm: ";
                        cin >> answer;
                        
						statusConfirmation(user1, answer, 286, 18.43);
						break;
						
					case 4:
						cout << "\nType \033[32mYes\033[0m to confirm: ";
                        cin >> answer;
						
						statusConfirmation(user1, answer, 479, 35.67);
						break;
						
					case 5:
						cout << "\nType \033[32mYes\033[0m to confirm: ";
                        cin >> answer;
						
						statusConfirmation(user1, answer, 758, 55.28);
						break;
						
					case 6:
						cout << "\nType \033[32mYes\033[0m to confirm: ";
                        cin >> answer;
						
						statusConfirmation(user1, answer, 1144, 83.43);
						break;
						
					default:
						cout << "Invalid Choice!\n";
				}
				
				    break;
				    
			case 3:
				{
				
				showBankMenu(banks, totalBanks); // show all banks using for loop in a function

                int selected;
                cout << "\033[36mChoose Bank: ";
                cin >> selected;
                cout << "\033[0m";
                
                if (selected < 1 || selected > totalBanks) {// safe measures for failures
                    cout << "Invalid bank!\n";
                    break;
                    }

                    Bank &chosenBank = banks[selected - 1];

                    cout << "\nYou chose: \033[33m" << chosenBank.getbankName() << "\033[0m\n\n";

                    Bank::showBalance(); //show bank balance, though, all banks share the same balance

                    double amount;
                    cout << "Enter amount to transfer to your recharge wallet: RM ";
                    cin >> amount;
                    
                    if (amount <= 0) { //safety measure for failure
                        cout << "\n\033[31mInvalid amount!\033[0m\n\n";
                        break;
                        }
                    cout << endl;
                    Bank::transferToUser(user1, amount); //transfer input amount in bank balance to user wallet balance
                    
                    chosenBank.saveBankTransaction(amount); //transaction save in this function and saved at transaction2.txt
                    
                    cout << "Your new wallet balance: \033[33mRM " << user1.getBalance() << "\033[0m" << endl; //update wallet balance and display
					break;
			}
//Haidhar end
//Firas start			
			case 4:
			int selected;
			int opt;
			
			
                do{
                	cout << "\n\t1. View User Transactions\n";
                    cout << "\t2. View Bank Transactions\n";
                    cout << "\t3. Exit\n\n";
                    cout << "\033[36mEnter option : ";
                    
                    cin >> opt;
                    cout << "\033[0m";
                    cout << endl;
                	
                	
				    if (opt == 1) { // view transaction history
                	
                        user1.viewTransaction();
                    }
                    else if (opt == 2) {
                        showBankMenu(banks, totalBanks);
                        cout << "Select Bank to View History: ";
                        cin >> selected;

                        if (selected >= 1 && selected <= totalBanks) {
                        	
                            banks[selected - 1].viewTransaction2();
                        } else {
                            cout << "Invalid bank!\n";
                        }
                    }
					else if (opt == 3) {
                        cout << "Returning to Main Menu...\n";
                    }
                    else {        
                        cout << "Invalid option!\n";
                    }
                } while (opt != 3);
				
				break;
				
			case 5:	
				displayUserDetails(user1);
								
				break;
				
			case 6:
				cout << "\n\033[36mExiting System...\033[0m\n";
				
				RechargeUser::clearTransactions(); //delete transaction.txt
				Bank::clearTransactions(); //delete transaction2.txt
				cout << "\n\033[31mtransaction.txt file deleted...\n";
				cout << "transaction2.txt file deleted...\033[0m\n";
								    
				break;
				
			default:
				cout << "Invalid Choice!\n";
				
	        }
	} while (choice != 6);
	
	return 0;
}
