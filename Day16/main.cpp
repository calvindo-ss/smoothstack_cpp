#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <bitset>

float addition(std::string a, std::string b){
    float a_f, b_f;

    // first operand
    if(a.compare(0, 2, "0x") == 0){
        a_f = std::stoul (a, nullptr, 16);
    }
    else if(a.compare(0, 2, "0b") == 0){
        a_f = std::stoul (a.substr(2, a.size()), nullptr, 2);
    }
    else{
        a_f = std::stof(a);
    }

    // second operand
    if(b.compare(0, 2, "0x") == 0){
        b_f = std::stoul (b, nullptr, 16);
    }
    else if(b.compare(0, 2, "0b") == 0){
        b_f = std::stoul (b.substr(2, b.size()), nullptr, 2);
    }
    else{
        b_f = std::stof(b);
    }

    return a_f + b_f;
}

void s_to_hex(std::string s){
    if(s.compare(0, 2, "0b") == 0){
        int num = std::stoul (s.substr(2, s.size()), nullptr, 2); // convert binary to int
        std::cout << "prompt > " << "0x" << std::hex << num << std::endl; // convert int to hex
    }
    else{
        int num = stoi(s);
        std::cout << "prompt > " << "0x" << std::hex << num << std::endl;
    }
}

void s_to_bin(std::string s){
    if(s.compare(0, 2, "0x") == 0){
        int num = std::stoul (s, nullptr, 16); // convert hex to int
        std::cout << "prompt > " << "0b" << std::bitset<14>(num) << std::endl; // convert int to bin
    }
    else{
        int num = stoi(s);
        std::cout << "prompt > " << "0x" << std::bitset<14>(num) << std::endl;
    }
}

void parse_line(std::string line){
    std::vector<std::string> v;
    std::string data;

    std::istringstream is(line);
    while (is >> data){
        v.push_back(data);
    }


    if(v.size() == 3 && v.at(1) == "+"){
        std::cout << "prompt > " << addition(v.at(0), v.at(2)) << std::endl;
    }

    else if(v.size() == 2){ // 2 arguments (hex/bin xxxxx)
        if(v.at(0) == "hex"){
            s_to_hex(v.at(1));
        }

        else if(v.at(0) == "bin"){
            s_to_bin(v.at(1));
        }
    }

    else if(v.size() == 1){ // single argument
        if(v.at(0).compare(0, 2, "0x") == 0){
            std::cout << "prompt > " << std::stoul (v.at(0), nullptr, 16) << std::endl;
        }

        else if(v.at(0).compare(0, 2, "0b") == 0){
            std::cout << "prompt > " << std::stoul (v.at(0).substr(2, v.at(0).size()), nullptr, 2) << std::endl;
        }
    }
}

int main(void){
    while(true){
        std::string line;

        std::cout << "prompt > ";
        std::getline(std::cin, line);

        if(line.empty()){
            continue;
        }
        else if(line.compare("quit") == 0 || line.compare("exit") == 0){
            break;
        }
        else{
            parse_line(line);
        }
    }
}


