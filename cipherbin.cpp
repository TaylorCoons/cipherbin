#include <iostream>
#include <string>
#include "CLIParser/CLIParser.h"

// Cipher includes
#include "Cipher.h"
#include "CaeserCipher.h"
#include "MonoalphabeticCipher.h"

// Validate list options
bool ValidateList();

// Validate cipher option
bool ValidateCipherOpt(CLIParser::OPTIONS& options, const std::string* cipherList, unsigned int numCiphers);

// List supported ciphers
void ListCiphers(const std::string* cipherList, unsigned int numCiphers);

// Instantiate polymorphic cipher based on subclass
Cipher* InstantiateCipher(const std::string& cipher);

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
    if (argparse.ParseError()) {
        return 1;
    }
        
    // Branch on subParser
    if (subParser == "list") {
        if (ValidateList()) {
            ListCiphers(cipherList, numCiphers);
        }
    } else if (subParser == "encrypt") {
        if (!ValidateCipherOpt(encryptOpts, cipherList, numCiphers)) {
            return 1; 
        }
        Cipher* cipher = InstantiateCipher(encryptOpts["cipher"].result);
        if (!cipher->ValidateKey(encryptOpts["key"].result, encryptOpts["plaintext"].result)) {
            return 1;
        }
        std::string cipherText;
        cipherText = cipher->Encrypt(encryptOpts["key"].result, encryptOpts["plaintext"].result);
        std::cout << cipherText << std::endl;
        if (cipher != nullptr) {
            delete cipher;
            cipher = nullptr;
        }
    } else if (subParser == "decrypt") {
        if (!ValidateCipherOpt(decryptOpts, cipherList, numCiphers)) {
            return 1;
        }
        Cipher* cipher = InstantiateCipher(decryptOpts["cipher"].result);
        if (!cipher->ValidateKey(decryptOpts["key"].result, decryptOpts["ciphertext"].result)) {
            return 1;
        }
        std::string plainText;
        plainText = cipher->Decrypt(decryptOpts["key"].result, decryptOpts["ciphertext"].result);
        std::cout << plainText << std::endl; 
        if (cipher != nullptr) {
            delete cipher;
            cipher = nullptr;
        }
    }

    return 0;
}

// Validate list options
bool ValidateList() {
    return true;
}

// Validate encrypt options
bool ValidateCipherOpt(CLIParser::OPTIONS& options, const std::string* cipherList, unsigned int numCiphers) {
    for (unsigned int i = 0; i < numCiphers; i++) {
        if (cipherList[i] == options["cipher"].result) {
            return true;
        }
    }
    std::cout << "Cipher must be in supported cipher list" << std::endl;
    return false;
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

// Instantiate polymorphic cipher based on subclass
Cipher* InstantiateCipher(const std::string& cipher) {
    if (cipher == "Caeser") {
        return reinterpret_cast<Cipher*>(new CeaserCipher);
    } else if (cipher == "Monoalphabetic") {
        return reinterpret_cast<Cipher*>(new MonoalphabeticCipher);
    }
}
