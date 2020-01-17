#include <iostream>
#include <string>
#include "CLIParser/CLIParser.h"

// Validate list options
bool ValidateList();

// Validate encrypt options
bool ValidateEncryptOpts(CLIParser::OPTIONS& options, const std::string* cipherList, unsigned int numCiphers);

// Validate decrypt options
bool ValidateDecryptOpts(CLIParser::OPTIONS& options, const std::string* cipherList, unsigned int numCiphers);

// List supported ciphers
void ListCiphers(const std::string* cipherList, unsigned int numCiphers);

int main(int argc, char** argv) {
    // Instantiate argument parser
    CLIParser argparse;
    // Instantiate options
    CLIParser::OPTIONS encryptOpts;
    CLIParser::OPTIONS decryptOpts;
    std::string cipherList[] = {
        "Caeser",
        "Monoalphabetic",
        "Playfair",
        "Hill",
        "Vigenere",
        "Vernam"
    };
    unsigned int numCiphers = sizeof(cipherList) / sizeof(std::string);
    encryptOpts["key"] = {
        "--key", 
        "-k", 
        CLIParser::ARG_TYPE::REQUIRED_ARG, 
        CLIParser::OPT_TYPE::REQUIRED_OPT 
    };
    encryptOpts["plaintext"] = { 
        "--plaintext", 
        "-p", 
        CLIParser::ARG_TYPE::REQUIRED_ARG, 
        CLIParser::OPT_TYPE::REQUIRED_OPT };
    encryptOpts["cipher"] = { 
        "--cipher",
        "-c",
        CLIParser::ARG_TYPE::REQUIRED_ARG,
        CLIParser::OPT_TYPE::REQUIRED_OPT 
    };
    decryptOpts["key"] = { 
        "--key",
        "-k",
        CLIParser::ARG_TYPE::REQUIRED_ARG,
        CLIParser::OPT_TYPE::REQUIRED_OPT 
    };
    decryptOpts["ciphertext"] = { 
        "--ciphertext",
        "-e",
        CLIParser::ARG_TYPE::REQUIRED_ARG,
        CLIParser::OPT_TYPE::REQUIRED_OPT 
    };
    decryptOpts["cipher"] = { 
        "--cipher",
        "-c",
        CLIParser::ARG_TYPE::REQUIRED_ARG,
        CLIParser::OPT_TYPE::REQUIRED_OPT 
    };
    
    // Add the subparsers
    argparse.AddParser("encrypt", &encryptOpts);
    argparse.AddParser("decrypt", &decryptOpts);
    argparse.AddParser("list", nullptr);
    // Parse the arguments
    std::string subParser = argparse.Parse(argc, argv);
    
    // Check if there was an error parsing
    if (!argparse.ParseError()) {
        // Branch on subParser
        if (subParser == "list") {
            if (ValidateList()) {
                ListCiphers(cipherList, numCiphers);
            }
        } else if (subParser == "encrypt") {
            if (ValidateEncryptOpts(encryptOpts, cipherList, numCiphers)) {

            }
        } else if (subParser == "decrypt") {
            if (ValidateDecryptOpts(decryptOpts, cipherList, numCiphers)) {

            } 
        }
    }    

    return 0;
}

// Validate list options
bool ValidateList() {
    return true;
}

// Validate encrypt options
bool ValidateEncryptOpts(CLIParser::OPTIONS& options, const std::string* cipherList, unsigned int numCiphers) {
    for (unsigned int i = 0; i < numCiphers; i++) {
        if (cipherList[i] == options["cipher"].result) {
            return true;
        }
    }
    std::cout << "Cipher must be in supported cipher list" << std::endl;
    return false;
}

// Validate decrypt options
bool ValidateDecryptOpts(CLIParser::OPTIONS& options, const std::string* cipherList, unsigned int numCiphers) {
    return true;
}

// List supported ciphers
void ListCiphers(const std::string* cipherList, unsigned int numCiphers) {
    std::cout << "Supported ciphers: ";
    for (unsigned int i = 0; i < numCiphers; i++) {
        std::cout << cipherList[i];
        if (static_cast<int>(i) != static_cast<int>(numCiphers) - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}
