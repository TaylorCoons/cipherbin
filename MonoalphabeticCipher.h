#ifndef MonoalphabeticCipher_h
#define MonoalphabeticCipher_h

#include <string>
#include <iostream>

#include "Cipher.h"

/*
* MonoalphabeticCipher class
*/
class MonoalphabeticCipher : Cipher {
    
    /* Functions */
    private:

    public:
    virtual std::string Encrypt(const std::string& key, const std::string& plainText) {
        std::string cipherText;    
        for (unsigned int i = 0; i < plainText.size(); i++) {
            uint8_t pOrd = static_cast<uint8_t>(plainText[i] - 'a');
            cipherText.push_back(key[pOrd]);
        }
        return cipherText;
    }

    virtual std::string Decrypt(const std::string& key, const std::string& cipherText) {
        std::string plainText;
        for (unsigned int i = 0; i < cipherText.size(); i++) {
            uint8_t cOrd = static_cast<uint8_t>(cipherText[i] - 'a');
            plainText.push_back(key[cOrd]);
        }
        return plainText;
    }

    virtual bool ValidateKey(const std::string& key, const std::string& text) {
        if (key.size() != 26) {
            std::cout << "Key length must be 26" << std::endl;
            return false;
        }
        return true;
    }    

};


#endif
