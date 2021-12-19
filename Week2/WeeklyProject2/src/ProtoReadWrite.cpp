#include "ProtoReadWrite.h"
#include <users.pb.h>
#include <AccountData.h>

#include <vector>
#include <fstream>

// helper function
unsigned levenshtein_distance(const std::string s1, std::string s2) {

	const std::size_t len1 = s1.size(), len2 = s2.size();
	std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

	d[0][0] = 0;
	for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

	for(unsigned int i = 1; i <= len1; ++i)
		for(unsigned int j = 1; j <= len2; ++j) {
            d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
        }

	return d[len1][len2];
}

ProtoReadWrite::ProtoReadWrite(AccountData &a){
    accountdata = a;
}

// returns all customer data
bankcli::Customers ProtoReadWrite::read_proto(){

	bankcli::Customers customer;

	// Read the existing address book.
	std::fstream input("users.data", std::ios::in | std::ios::binary);
	if(!customer.ParseFromIstream(&input)){
		std::cerr << "Failed to parse address book." << std::endl;
		return customer;
	}

	// Optional:  Delete all global objects allocated by libprotobuf.
  	google::protobuf::ShutdownProtobufLibrary();
	return customer;
}


void ProtoReadWrite::write_proto(){

    bankcli::Customers customer;

    // Read the existing address book.
    std::fstream input("users.data", std::ios::in | std::ios::binary);
    if (!input) {
      std::cout << "users.data" << ": File not found.  Creating a new file." << std::endl;
    } 
    else if(!customer.ParseFromIstream(&input)){
      std::cerr << "Failed to parse address book." << std::endl;
      return;
    }

    // add a user
    write_data(customer.add_account());
    

    // Write the new address book back to disk.
    std::fstream output("users.data", std::ios::out | std::ios::trunc | std::ios::binary);
    if (!customer.SerializeToOstream(&output)) {
      std::cerr << "Failed to write address book." << std::endl;
      return;
    }
  
    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return ;
}

void ProtoReadWrite::write_proto(bankcli::Account &account, double &balance){

    bankcli::Customers customer;

    // Read the existing address book.
    std::fstream input("users.data", std::ios::in | std::ios::binary);
    if (!input) {
      std::cout << "users.data" << ": File not found.  Creating a new file." << std::endl;
    } 
    else if(!customer.ParseFromIstream(&input)){
      std::cerr << "Failed to parse address book." << std::endl;
      return;
    }

    // update balance
    account.set_balance(balance);
    

    // Write the new address book back to disk.
    std::fstream output("users.data", std::ios::out | std::ios::trunc | std::ios::binary);
    if (!customer.SerializeToOstream(&output)) {
      std::cerr << "Failed to write address book." << std::endl;
      return;
    }
  
    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return ;
}

void ProtoReadWrite::write_data(bankcli::Account *account){

    account->set_accountnum(accountdata.getAccountNum());
    account->set_username(accountdata.getUsername());
    account->set_password(accountdata.getPassword());
    account->set_fname(accountdata.getFName());
    account->set_lname(accountdata.getLName());
    account->set_ssn(accountdata.getSSN());
    account->set_balance(accountdata.getBalance());
    account->set_dateopened(accountdata.getDateOpened());
    account->set_accounttype(accountdata.getAccountType());
    account->set_admin(accountdata.getAdmin());
}

void ProtoReadWrite::show_all_accounts(){
    bankcli::Customers customer = read_proto();

    for(int i = 0; i < customer.account_size(); i++){
		const bankcli::Account account = customer.account(i);

    std::cout << "################################" << std::endl;
		std::cout << "Account number: " << account.accountnum() << std::endl;
		std::cout << "Customer name: " << account.fname() << " " << account.lname() << std::endl;
		std::cout << "Date opened: " << account.dateopened() << std::endl;
	}
}

void ProtoReadWrite::show_account(int accountNum){

  bankcli::Customers customer = read_proto();

    for(int i = 0; i < customer.account_size(); i++){
		const bankcli::Account account = customer.account(i);

		if(accountNum == account.accountnum()){
            std::cout << std::endl << "################################" << std::endl;
            std::cout << "Customer name: " << account.fname() << " " << account.lname() << std::endl;
            std::cout << "SSN: " << account.ssn() << std::endl;
            std::cout << "Date opened: " << account.dateopened() << std::endl;
            std::cout << "################################" << std::endl;
    }
	}
}

void ProtoReadWrite::show_account(std::string fname, std::string lname){
	std::vector<int> searchResults_accountnums;
    std::vector<std::string> searchResults;

    bankcli::Customers customer = read_proto();

    for(int i = 0; i < customer.account_size(); i++){
		const bankcli::Account account = customer.account(i);

		if(levenshtein_distance(fname, account.fname()) < 4 && levenshtein_distance(lname, account.lname()) < 4){
            if(fname.compare(account.fname()) == 0 && lname.compare(account.lname()) == 0){

                searchResults.insert(searchResults.begin(), account.fname()+" "+account.lname());
                searchResults_accountnums.insert(searchResults_accountnums.begin(), account.accountnum());
            }
            else{
                searchResults.push_back(account.fname()+" "+account.lname());
                searchResults_accountnums.push_back(account.accountnum());

            }
        }
	}

    if(searchResults.size() != 0){
        for(int i=0; i<searchResults.size(); i++){
        std::cout << i+1 << ". " << searchResults[i] << std::endl;
        }

        std::cout << "0. Cancel search" << std::endl << std::endl;
        int option;
        std::cout << "Select which user to view: ";
        std::cin >> option;

        // selects customer based on user input
        for(int j = 0; j < searchResults.size(); j++){
            if(option == 0){
                return;
            }
            if(j+1 == option){ // if option==1
                show_account(searchResults_accountnums[j]);
                return;
            }
        }
    }
    
    std::cout << "No matching account found for " << fname << " " << lname << std::endl;
    show_account(fname, lname);
}

