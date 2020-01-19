#ifndef VigenereCipher_h 
#define VigenereCipher_h

#include <string>
#include <iostream>

#include "Cipher.h"

/*
* MonoalphabeticCipher class
*/
class VigenereCipher : Cipher {
    
    /* Functions */
    private:
    std::string Transform(const std::string& key, const std::string& text, bool forward) {
        std::string formatedKey = FormatKey(key, text.size());
        std::string formatedText;
        int dir = 1;
        if (!forward) {
            dir = -1;
        }
        for (unsigned int i = 0; i < text.size(); i++) {
            int shift = static_cast<int>(tolower(formatedKey[i]) - 'a');
            int tOrd = static_cast<int>(tolower(text[i]) - 'a'); 
            int ord = (tOrd + dir * shift) % 26; 
            ord = (ord < 0 ? ord + 26 : ord);
            formatedText.push_back(static_cast<char>(ord) + 'a');
        }
        return formatedText;
    }

    std::string FormatKey(const std::string& key, unsigned int length) {
        std::string formatedKey = key;
        while (formatedKey.size() < length) {
            formatedKey += key;
        }
        return formatedKey.substr(0, length);
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
