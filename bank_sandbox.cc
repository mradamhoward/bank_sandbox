#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#define NUM_VAR_CUSTOMER 6
#define OUTPUT_FILE "out.txt"

using namespace std;

class customer{

 public:
    string name;
    int age;
    double balance;
    char gender;
    bool overdraft;
    double overdraftAmount;

   
    customer(string name, int age, double balance, char gender, bool overdraft, double overdraftAmount) : 
    name(name), age(age), balance(balance), gender(gender), overdraft(overdraft), overdraftAmount(overdraftAmount)
    {};

    customer(){

    };

    void printDetails();
    string getDetails();
};

void customer::printDetails(){
    cout << "----------------CUSTOMER-----------------\n";
    cout << "Name: " << name << " \nAge: " << age << " \nBalance: " << balance << " \nGender: " << gender << " \nOverdraft: "  << overdraft << " \nOverdraft Amount: " << overdraftAmount << endl;   
}

string customer::getDetails(){
   return name + "\n" + to_string(age) + "\n" + to_string(balance) + "\n" + to_string(gender) + "\n" + to_string(overdraft) + "\n" + to_string(overdraftAmount) + "\n"; 
}

class menu {
    public:
    menu(){};

    void printMenu();
    void printCustomers(vector<customer>& customers);
    void saveCustomersToFile(string details);
    void loadCustomersFromFile(vector<customer>& customers);
    void searchForCustomers(vector<customer>& customers);
    void removeCustomer(vector<customer>& customers);
    void editCustomer(vector<customer>& customers);
    void chargeAllAmount(vector<customer>& customers, double amount);
    void chargeSpecificAmount(vector<customer>& customers, double amount, string person);
    void clearFile();
};



void menu::printMenu(){
    cout << "\nEnter the option: \n";
    cout << "1: View customers. \n";
    cout << "2: Add a customer. \n";
    cout << "3: Remove customers(s). \n";
    cout << "4: Edit customer(s). \n";
    cout << "5: Search for customer(s). \n";
    cout << "6: Load customers from file. \n";
    cout << "7: Save customers to file. \n";
    cout << "8: Charge all accounts certain amount. \n";
    cout << "9: Charge specific account certain amount. \n";
    cout << "10: Clear file contents! \n";
}

void menu::printCustomers(vector<customer>& customers){
for(customer& c : customers){
        c.printDetails();
    }
}

void menu::saveCustomersToFile(string details){
    ofstream out;
    out.open(OUTPUT_FILE, std::ios_base::app);
    out << details;
    out.close();
}

customer addCustomer(){
    string name;
    int age;
    double balance;
    char gender;
    bool overdraft;
    double overdraftAmount;

    cout << "Enter name : \n";
    cin.ignore();
    getline(cin, name);

    cout << "Enter age: \n";
    cin >> age;

    cout << "Enter balance: \n";
    cin >> balance;

    cout << "Enter gender (m/f): \n";
    cin >> gender;

    cout << "Enter overdraft (y/n): \n";
    char answer;
    cin >> answer;
      if(answer == 'y'){
		overdraft = true;
    } else {
    	overdraft = false;
    }

    cout << "Enter Overdraft Amount: \n";
    cin >> overdraftAmount;
    
    customer c (name, age, balance, gender, overdraft, overdraftAmount);

    return c;
}

void menu::loadCustomersFromFile(vector<customer>& customers){
    ifstream in(OUTPUT_FILE);
    vector<string> lines;
    if(in.is_open()){
        int counter = 0;
        string holder;
        while(!in.eof()){
            getline(in, holder);
            lines.push_back(holder);
        }
    }

    int num_vars = NUM_VAR_CUSTOMER;
    int counter = 0;

    string name;
    int age;
    double balance;
    char gender;
    bool overdraft;
    double overdraftAmount;

    for(string s : lines){
        if(counter == 0){
            name = s;
            counter++;
        } else if(counter == 1) {
            age = stoi(s);
            counter++; 
        } else if (counter == 2){
            balance = stod(s);
            counter++;
        } else if (counter == 3){
            gender = s[0];
            counter++;
        } else if (counter == 4){
            if(s == "1"){
                overdraft = true;
            } else {
                overdraft = false;
            }
            counter++;
        } else if (counter == 5){
            overdraftAmount = stod(s);
            counter = 0;
            customer c(name, age, balance, gender, overdraft, overdraftAmount);
            customers.push_back(c);
        }
    }
}

void menu::searchForCustomers(vector<customer>& customers){
    vector<customer> results;

    cout << "What data type would you like to search for?: \n";
    cout << "1: Name\n";
    cout << "2: Age\n";
    cout << "3: Balance\n";
    cout << "4: Gender (m/f)\n";
    cout << "5: Overdraft (y/n)\n";
    cout << "6: Overdraft Amount\n";

    int choice;

    cin >> choice;

    switch(choice){
        case 1: 
        {
            string toSearch;
            cout << "Name to search for: ";
            cin >> toSearch;
            for(customer& c : customers){
                if(c.name == toSearch){
                    results.push_back(c);
                }
            }
            break;
        }
        case 2:
        {
            int toSearchAge;
            cout << "Name to search for: ";
            cin >> toSearchAge;
            for(customer& c : customers){
                if(c.age == toSearchAge){
                    results.push_back(c);
                }
            }
            break;
        }
        case 3:
        {
            int toSearchBalance;
            cout << "Balance to search for: ";
            cin >> toSearchBalance;
            for(customer& c : customers){
                if(c.balance == toSearchBalance){
                    results.push_back(c);
                }
            }
            break;
        }
        case 4:
        {
            char toSearchGender;
            cout << "Gender to search for: (m/f)";
            cin >> toSearchGender;
            for(customer& c : customers){
                if(c.gender == toSearchGender){
                    results.push_back(c);
                }
            }
            break;
        }
        case 5:
        {
            char toSearchOverdraft;
            cout << "Overdraft to search for: (y/n)";
            cin >> toSearchOverdraft;
            bool over;
            if(toSearchOverdraft == 'y'){
                over = true;
            } else {
                over = false;
            }
            for(customer& c : customers){
                if(c.overdraft == over){
                    results.push_back(c);
                }
            }
            break;
        }
        case 6:
        {
            double toSearchOverdraftAmount;
            cout << "Overdraft Amount to search for: (double)";
            cin >> toSearchOverdraftAmount;
            for(customer& c : customers){
                if(c.overdraftAmount == toSearchOverdraftAmount){
                    results.push_back(c);
                }
            }
            break;
        }

    }
    vector<customer>& ref = results;
  
    cout << "Results from search: \n";

    printCustomers(ref);
}




void menu::removeCustomer(vector<customer>& customers){
    string toRemove;
    cout << "Enter the name of the customer you would like to remove: ";
    cin.ignore();
    getline(cin, toRemove);
    int index = 0;
    for(customer& c : customers){
        if(c.name == toRemove){
        customers.erase(customers.begin() +  index);    
         }
        index++;
    }
}

void menu::editCustomer(vector<customer>& customers){
    string toEdit;
    cout << "Enter the name of the customer you would like to remove: ";
    cin.ignore();
    getline(cin, toEdit);
    int index = 0;

    for(customer& c : customers){
        if(c.name == toEdit){
            cout << "Enter new name for " << c.name << "\n";
            cin.ignore();
            getline(cin, c.name);
            cout << "Enter new age for " << c.name << "\n";
            cin >> c.age;
            cout << "Enter new balance for " << c.name << "\n";
            cin >> c.balance;
            cout << "Enter new gender (m/f) for " << c.name << "\n";
            cin >> c.gender;
            cout << "Does" << c.name << " require a new overdraft" << "\n";
            char answer;
            cin >> answer;
            if(answer == 'y'){
                c.overdraft = true;
            } else {
                c.overdraft = false;
            }

            if(c.overdraft){
                cout << "Enter new overdraftAmount for " << c.name << "\n";
                cin >> c.overdraftAmount;
            } else {
                c.overdraftAmount = 0;
            }
          
            cout << "Success!\n";
            c.printDetails();
            cout << "Are the new details.";
         }
        index++;
    }
}


void menu::chargeAllAmount(vector<customer>& customers, double amount){
    for(customer& c: customers){
        c.balance += amount;
    }
}

void menu::chargeSpecificAmount(vector<customer>& customers, double amount, string person){
    for(customer& c: customers){
        if(c.name == person){
            c.balance += amount;
        }
    }
}

void menu::clearFile(){
    std::ofstream ofs;
    ofs.open(OUTPUT_FILE, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}


int main(){
    vector<customer> customers;

    customer customer1(string("Adam Howard"), 24, 50.00, 'm', true, 100.00);

    customers.push_back(customer1);

    menu m;

    int option;

    while(true){
        m.printMenu();
        cin.clear();
        cin.ignore();
        cin >> option;
        switch(option){
            case 1:
            { 
                m.printCustomers(customers);
                option = 0;
                break;
            }
            case 2:
            {
                customers.push_back(addCustomer());
                option = 0;
                break;
            }
            case 3:
            {
                m.removeCustomer(customers);
                option = 0;
                break;
            }
            case 4:
            {
                m.editCustomer(customers);
                option = 0;
                break;
            }
            case 5:
            {
                m.searchForCustomers(customers);
                option = 0;
                break;
            }
            case 6:
            { 
                m.loadCustomersFromFile(customers);
                option = 0;
                break;
            }
            case 7:
            {
                for(customer& c : customers){
                    m.saveCustomersToFile(c.getDetails());
                }
                option = 0;
                break;
            }
            case 8:
            {
                cout << "Enter the amount you would like to apply to all customers' balance: ";
                double amount;
                cin >> amount;
                m.chargeAllAmount(customers, amount);
                option = 0;
                m.printCustomers(customers);
                break;
            }
            case 9:
            {
                cout << "Enter the person you would like to apply the amount to their balance: ";
                string person;
                cin.ignore();
                getline(cin, person);
                cout << "Enter the amount you would like to apply to balance: ";
                double amount;
                cin >> amount;
                m.chargeSpecificAmount(customers, amount, person);
                option = 0;
                break;
            }
            case 10:
            {
                m.clearFile();
                cout << "File cleared!!!";
            }                     
        }
    }   
}