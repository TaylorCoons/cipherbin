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
    char TransformCharacter(const std::string& key, const char& c) {
        uint8_t pos;
        for (pos = 0; pos < key.size(); pos++) {
            if (tolower(key[pos]) == tolower(c)) {
                break;
            }
        }
        return 'a' + pos;
    }
    std::string Transform(const std::string& key, const std::string& text, bool forward) {
        std::string transformedText;
        for (unsigned int i = 0; i < text.size(); i++) {
            if (forward) {
                transformedText.push_back(TransformCharacter(key, text[i]));
            } else {
                transformedText.push_back(key[static_cast<uint8_t>(tolower(text[i])-'a')]);
            }
        }
        return transformedText;
    }

    public:
    std::string Encrypt(const std::string& key, const std::string& plainText) {
        return Transform(key, plainText, true);
    }

    std::string Decrypt(const std::string& key, const std::string& cipherText) {
        return Transform(key, cipherText, false);
    }

    bool ValidateKey(const std::string& key, const std::string& text) {
        if (key.size() != 26) {
            std::cout << "Key length must be 26" << std::endl;
            return false;
        }
        return true;
    }    

};


#endif
