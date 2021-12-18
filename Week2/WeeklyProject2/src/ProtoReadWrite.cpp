#include "ProtoReadWrite.h"
#include <users.pb.h>
#include <AccountData.h>

#include <vector>
#include <fstream>

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

