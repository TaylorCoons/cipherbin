#ifndef CaeserCipher_h
#define CeaserCipher_h

#include <string>
#include <iostream>

#include "Cipher.h"

/* 
* CeaserCipher class
*/

class CeaserCipher : Cipher {
    
    /* Functions */
    private:
    
    public:
 
    std::string Encrypt(const std::string& key, const std::string& plainText) {
        std::string cipherText;
        for (unsigned int i = 0; i < plainText.size(); i++) {
            uint8_t pOrd = static_cast<uint8_t>(plainText[i] - 'a');
            uint8_t kOrd = static_cast<uint8_t>(key[0] - 'a');
            cipherText.push_back(static_cast<char>((pOrd + kOrd) % 26) + 'a');
        }
        return cipherText;
    };

    std::string Decrypt(const std::string& key, const std::string& cipherText) {
        std::string plainText;
        for (unsigned int i = 0; i < cipherText.size(); i++) {
            uint8_t cOrd = static_cast<uint8_t>(cipherText[i] - 'a');
            uint8_t kOrd = static_cast<uint8_t>(key[0] - 'a');
            plainText.push_back(static_cast<char>((cOrd - kOrd) % 26) + 'a');
        }
        return plainText;
    };
    
    bool ValidateKey(const std::string& key, const std::string& text) {
        if (key.size() != 1) {
            std::cout << "Key length must be one" << std::endl;
            return false;
        }
        return true; 
    };

    void KeyDesc() {
        std::cout << "The key consists of one character from the set [a-z]" << std::endl;
    }

    void TextDesc() {
        std::cout << "The text must be contained in the set [a-z]" << std::endl;
    }

};

#endif
