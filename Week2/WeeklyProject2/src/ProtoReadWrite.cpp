#include "ProtoReadWrite.h"
#include <Account.pb.h>
#include <Sha256.h>

#include <vector>
#include <fstream>
#include <string>

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

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

bool ProtoReadWrite::check_account_exists(std::string &username, std::string &password){
	pb::Accounts accounts;

    std::string sha256_password = sha256(password);

	// Read the existing address book.
	std::fstream input("Account.data", std::ios::in | std::ios::binary);
	if(!accounts.ParseFromIstream(&input)){
        logger.log("Failed to parse address book.");
		//std::cerr << "Failed to parse address book." << std::endl;
		return false;
	}

	for(int i = 0; i < accounts.account_size(); i++){
		pb::Account account = accounts.account(i);

		if(username == account.username() && sha256_password == account.password()){
        	return true;
        }
	}
	// Optional:  Delete all global objects allocated by libprotobuf.
  	google::protobuf::ShutdownProtobufLibrary();
	return false;
}

bool ProtoReadWrite::check_account_exists(int &accountnum){
	pb::Accounts accounts;

	// Read the existing address book.
	std::fstream input("Account.data", std::ios::in | std::ios::binary);
	if(!accounts.ParseFromIstream(&input)){
        logger.log("Failed to parse address book.");
		//std::cerr << "Failed to parse address book." << std::endl;
		return false;
	}

	for(int i = 0; i < accounts.account_size(); i++){
		pb::Account account = accounts.account(i);

		if(accountnum == account.accountnum()){
        	return true;
        }
	}
	// Optional:  Delete all global objects allocated by libprotobuf.
  	google::protobuf::ShutdownProtobufLibrary();
	return false;
}

void ProtoReadWrite::show_all_accounts(){

    pb::Accounts accounts;

	// Read the existing address book.
	std::fstream input("Account.data", std::ios::in | std::ios::binary);
	if(!accounts.ParseFromIstream(&input)){
        logger.log("Failed to parse address book.");
		//std::cerr << "Failed to parse address book." << std::endl;
		return;
	}

	 for(int i = 0; i < accounts.account_size(); i++){
		const pb::Account account = accounts.account(i);

        std::cout << "################################" << std::endl;
		std::cout << "Account number: " << account.accountnum() << std::endl;
		std::cout << "Customer name: " << account.fname() << " " << account.lname() << std::endl;
		std::cout << "Date opened: " << account.dateopened() << std::endl;
	}

	// Optional:  Delete all global objects allocated by libprotobuf.
  	google::protobuf::ShutdownProtobufLibrary();
	return;
}

void ProtoReadWrite::show_account_num(){
    int accountNum;

    std::cout << "Enter account number to search for: ";
    std::cin >> accountNum;

    while (!std::cin.good()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    pb::Accounts accounts;

    // Read the existing address book.
	std::fstream input("Account.data", std::ios::in | std::ios::binary);
	if(!accounts.ParseFromIstream(&input)){
        logger.log("Failed to parse address book.");
		//std::cerr << "Failed to parse address book." << std::endl;
		return;
	}

    if(check_account_exists(accountNum) == true){

        for(int i = 0; i < accounts.account_size(); i++){
            const pb::Account account = accounts.account(i);

            if(accountNum == account.accountnum()){
                std::cout << std::endl << "################################" << std::endl;
                std::cout << "Customer name: " << account.fname() << " " << account.lname() << std::endl;
                std::cout << "SSN: " << (account.ssn()).substr(5,8) << std::endl;
                std::cout << "Date opened: " << account.dateopened() << std::endl;
                std::cout << "################################" << std::endl;
            }
        }
    }
    else{
        logger.log("No matching account found with account number"+accountNum);
        //std::cout << "No matching account found with account number " << accountNum << std::endl << std::endl;
        show_account_num();             // retries method if not matching account number found
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
  	google::protobuf::ShutdownProtobufLibrary();
}

void ProtoReadWrite::show_account_num(int accountNum){

    pb::Accounts accounts;

    // Read the existing address book.
	std::fstream input("Account.data", std::ios::in | std::ios::binary);
	if(!accounts.ParseFromIstream(&input)){
        logger.log("Failed to parse address book.");
		//std::cerr << "Failed to parse address book." << std::endl;
		return;
	}

    if(check_account_exists(accountNum) == true){

        for(int i = 0; i < accounts.account_size(); i++){
            const pb::Account account = accounts.account(i);

            if(accountNum == account.accountnum()){
                std::cout << std::endl << "################################" << std::endl;
                std::cout << "Customer name: " << account.fname() << " " << account.lname() << std::endl;
                std::cout << "SSN: " << account.ssn() << std::endl;
                std::cout << "Date opened: " << account.dateopened() << std::endl;
                std::cout << "################################" << std::endl;
            }
        }
    }
    else{
        logger.log("No matching account found with account number ");
        //std::cout << "No matching account found with account number " << accountNum << std::endl << std::endl;
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
  	google::protobuf::ShutdownProtobufLibrary();
}

void ProtoReadWrite::show_account_name(){
    std::string tmpfname, tmplname;

    std::cout << "Enter first name for search:";
    std::cin >> tmpfname;
    std::cout << "Enter last name for search:";
    std::cin >> tmplname;
    std::cout << std::endl;

    while (!std::cin.good()){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    rtrim(tmpfname);
    rtrim(tmplname);

    pb::Accounts accounts;

    // Read the existing address book.
	std::fstream input("Account.data", std::ios::in | std::ios::binary);
	if(!accounts.ParseFromIstream(&input)){
        logger.log("Failed to parse address book.");
		//std::cerr << "Failed to parse address book." << std::endl;
		return;
	}

    std::vector<int> searchResults_accountnums;
    std::vector<std::string> searchResults;


    for(int i = 0; i < accounts.account_size(); i++){
		const pb::Account account = accounts.account(i);

		if(levenshtein_distance(tmpfname, account.fname()) < 4 && levenshtein_distance(tmplname, account.lname()) < 4){
            if(tmpfname.compare(account.fname()) == 0 && tmplname.compare(account.lname()) == 0){

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
                show_account_num(searchResults_accountnums[j]);
                return;
            }
        }
    }
    logger.log("No matching account found for "+tmpfname+" "+tmplname);
    //std::cout << "No matching account found for " << tmpfname << " " << tmplname << std::endl;
    show_account_name();

   // Optional:  Delete all global objects allocated by libprotobuf.
  	google::protobuf::ShutdownProtobufLibrary();
}

void ProtoReadWrite::new_account(){
    std::string username, password;
    std::string fname, lname;
    int ssn;
    double balance = 0.00;
    std::string tmpDate;
    int dateOpened;
    char accountType; // checking 'c' or savings 's'
    int admin;
    int accountNum;

    std::cout << "Enter new account number: ";
    std::cin >> accountNum;

    // checks if accountNum alread exists
    if(check_account_exists(accountNum) == true){    
        logger.log("Account already exists");
        //std::cout << "Account already exists" << std::endl;
    }
    else{
        std::cout << "Enter new username: ";
        std::cin >> username;
        std::cout << "Enter new password: ";
        std::cin >> password;

        // checks minimim username and password length
        if(username.length() < 5){
            std::cout << "Username is too short (minimum 5 characters)" << std::endl;
            
            new_account();
            return;
        }
        else if(password.length() < 5){
            std::cout << "password is too short (minimum 5 characters)" << std::endl;
            new_account();
            return;
        }
        else if(username == password){
            std::cout << "Username and password cannot be the same" << std::endl;
            new_account();
            return;
        }

        std::cout << "Enter new first name: ";
        std::cin >> fname;
        std::cout << "Enter new last name: ";
        std::cin >> lname;
        std::cout << "Enter new SSN (9 digits): ";
        std::cin >> ssn;
        std::cout << "Enter new date opened yyyy-mm-dd: ";
        std::cin >> tmpDate;
        std::cout << "Enter new account type (S or C): ";
        std::cin >> accountType;
        std::cout << "Enter new admin elevation (0 for user, 1 for admin: ";
        std::cin >> admin;

        // remove '-' from date string
        tmpDate.erase(std::remove(tmpDate.begin(), tmpDate.end(), '-'), tmpDate.end());
        dateOpened = std::stoi(tmpDate);

        AccountData *accountdata = new AccountData();

        accountdata->setAccountNum(accountNum);        
        accountdata->setUsername(username);
        accountdata->setPassword(sha256(password));
        accountdata->setFName(fname);
        accountdata->setLName(lname);
        accountdata->setSSN(ssn);
        accountdata->setBalance(balance);
        accountdata->setDateOpened(dateOpened);
        accountdata->setAccountType(accountType);
        accountdata->setAdmin(admin);

        pb::Accounts accounts;

        // Read the existing address book.
        std::fstream input("Account.data", std::ios::in | std::ios::binary);
        if (!input) {
            std::cout << "Account.data" << ": File not found.  Creating a new file." << std::endl;
        } 
        else if(!accounts.ParseFromIstream(&input)){
            logger.log("Failed to parse address book.");
            //std::cerr << "Failed to parse address book." << std::endl;
            return;
        }

        write_data(*accounts.add_account(), *accountdata);

        // Write the new address book back to disk.
        std::fstream output("Account.data", std::ios::out | std::ios::trunc | std::ios::binary);
        if (!accounts.SerializeToOstream(&output)) {
            logger.log("Failed to write address book.");
            //std::cerr << "Failed to write address book." << std::endl;
        return;
        }
        
        // Optional:  Delete all global objects allocated by libprotobuf.
  	    google::protobuf::ShutdownProtobufLibrary();

        if(check_account_exists(accountNum) == true){
            logger.log("Account successfully created!");
            //std::cout << "Account successfully created!" << std::endl;
        }
    }
}

void ProtoReadWrite::write_data(pb::Account &account, AccountData &accountdata){
    account.set_accountnum(accountdata.getAccountNum());
    account.set_username(accountdata.getUsername());
    account.set_password(accountdata.getPassword());
    account.set_fname(accountdata.getFName());
    account.set_lname(accountdata.getLName());
    account.set_ssn(std::to_string(accountdata.getSSN()));
    account.set_balance(accountdata.getBalance());
    account.set_dateopened(accountdata.getDateOpened());
    account.set_accounttype(accountdata.getAccountType());
    account.set_admin(accountdata.getAdmin());
}

void ProtoReadWrite::write_data_transaction(double& amnt, int &accountnum){

    pb::Accounts accounts;

    // Read the existing address book.
    std::fstream input("Account.data", std::ios::in | std::ios::binary);
    if (!input) {
        logger.log("Account.data: File not found.  Creating a new file.");
        //std::cout << "Account.data" << ": File not found.  Creating a new file." << std::endl;
    } 
    else if(!accounts.ParseFromIstream(&input)){
        logger.log("Failed to parse address book.");
        //std::cerr << "Failed to parse address book." << std::endl;
        return;
    }

    pb::Account account = *accounts.add_account();
    pb::Account_Transaction transaction;

    account.set_accountnum(accountnum);
    transaction.set_amount_recv(amnt);
    

    // Write the new address book back to disk.
    std::fstream output("Account.data", std::ios::out | std::ios::trunc | std::ios::binary);
    if (!accounts.SerializeToOstream(&output)) {
        logger.log("Failed to write address book.");
        //std::cerr << "Failed to write address book." << std::endl;
    return;
    }
    
    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

};

void ProtoReadWrite::close_account(){
    int localAccountNum1, localAccountNum2;

    std::cout << "Enter account number of associated account: ";
    std::cin >> localAccountNum1;
    std::cout << "Repeated associated account number for security ";
    std::cin >> localAccountNum2;

    if(localAccountNum1 == localAccountNum2 && check_account_exists(localAccountNum1) == true){
        std::string choice;

        std::cout << "Type yes/no to remove the associated account:";
        std::cin >> choice;
        std::cout << std::endl;

        if(choice != "yes" || choice !="Yes"){
            std::cout << "Account deletion cancelled, Account deletion is not supported yet" << std::endl;
        }
        else{
            std::cout << "Account deletion is not supported yet" << std::endl;
        }
    }
}

AccountData ProtoReadWrite::get_account(std::string &username, std::string &password){
    pb::Accounts accounts;
    AccountData accountdata;

    std::string sha256_password = sha256(password);

	// Read the existing address book.
	std::fstream input("Account.data", std::ios::in | std::ios::binary);
	if(!accounts.ParseFromIstream(&input)){
        logger.log("Failed to parse address book.");
		//std::cerr << "Failed to parse address book." << std::endl;
		return accountdata;
	}

	for(int i = 0; i < accounts.account_size(); i++){
		pb::Account account = accounts.account(i);

		if(username == account.username() && sha256_password == account.password()){
        	accountdata.setAccountNum(account.accountnum());
            accountdata.setBalance(account.balance());        

            return accountdata;
        }
	}
	// Optional:  Delete all global objects allocated by libprotobuf.
  	google::protobuf::ShutdownProtobufLibrary();
	return accountdata;
}