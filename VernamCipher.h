#ifndef VernamCipher_h 
#define VernamCipher_h

#include <string>
#include <iostream>
#include <bitset>

#include "Cipher.h"

/*
* MonoalphabeticCipher class
*/
class VernamCipher : Cipher {
    /* Variables */
    std::bitset<5> baudotSet[32] = {


    };

    char charSet[32] = {

    };

        
    /* Functions */
    private:
    std::bitset<5> CharToBaudot(char c) {

    }    

    char BaudotToChar(const std::bitset<5>& baudot) {

    }

    std::string Transform(const std::string& key, const std::string& text, bool forward) {
        
    }

    std::string FormatKey(const std::string& key, unsigned int length) {
               
    }

    public:
    std::string Encrypt(const std::string& key, const std::string& plainText) {
        return Transform(key, plainText, true);
    }

    std::string Decrypt(const std::string& key, const std::string& cipherText) {
        return Transform(key, cipherText, false);
    }

    bool ValidateKey(const std::string& key, const std::string& text) {
        return true;
    }    

};


#endif
