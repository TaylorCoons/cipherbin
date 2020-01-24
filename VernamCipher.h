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
        std::bitset<5>(0x00),
        std::bitset<5>(0x01), 
        std::bitset<5>(0x02),
        std::bitset<5>(0x03), 
        std::bitset<5>(0x04),
        std::bitset<5>(0x05), 
        std::bitset<5>(0x06),
        std::bitset<5>(0x07), 
        std::bitset<5>(0x08),
        std::bitset<5>(0x09), 
        std::bitset<5>(0x0A),
        std::bitset<5>(0x0B), 
        std::bitset<5>(0x0C),
        std::bitset<5>(0x0D), 
        std::bitset<5>(0x0E),
        std::bitset<5>(0x0F), 
        std::bitset<5>(0x10),
        std::bitset<5>(0x11), 
        std::bitset<5>(0x12),
        std::bitset<5>(0x13), 
        std::bitset<5>(0x14),
        std::bitset<5>(0x15), 
        std::bitset<5>(0x16),
        std::bitset<5>(0x17), 
        std::bitset<5>(0x18),
        std::bitset<5>(0x19), 
        std::bitset<5>(0x1A),
        std::bitset<5>(0x1B), 
        std::bitset<5>(0x1C),
        std::bitset<5>(0x1D), 
        std::bitset<5>(0x1E),
        std::bitset<5>(0x1F)
    };

    char charSet[32] = {
        '\x4E',
        '\x74',
        '\x43',
        '\x6F',
        '\x53',
        '\x68',
        '\x6E',
        '\x6D',
        '\x4C',
        '\x6C',
        '\x72',
        '\x67',
        '\x69',
        '\x70',
        '\x63',
        '\x76',
        '\x65',
        '\x7A',
        '\x64',
        '\x62',
        '\x73',
        '\x79',
        '\x66',
        '\x78',
        '\x61',
        '\x77',
        '\x6A',
        '\x46',
        '\x75',
        '\x71',
        '\x6B',
        '\x47'
    };

        
    /* Functions */
    private:
    std::bitset<5> CharToBaudot(char c) {
        for (unsigned int i = 0; i < 32; i++) {
            if (charSet[i] == c) {
                return baudotSet[i];
            } 
        }
    }    

    char BaudotToChar(const std::bitset<5>& baudot) {
        for (unsigned int i = 0; i < 32; i++) {
            if (baudotSet[i] == baudot) {
                return charSet[i];
            }
        }
    }

    std::string Transform(const std::string& key, const std::string& text) {
        std::string formatedKey = FormatKey(key, text.size());
        std::string textOut;
        for (unsigned int i = 0; i < text.size(); i++) {
            std::bitset<5> tBits = CharToBaudot(text[i]);
            std::bitset<5> kBits = CharToBaudot(formatedKey[i]);
            char c = BaudotToChar(tBits ^ kBits);
            textOut.push_back(c); 
        }
        return textOut;
    }

    std::string FormatKey(const std::string& key, unsigned int length) {
        std::string formatedKey;
        for (unsigned int i = 0; i < length; i++) {
            formatedKey.push_back(key.at(i % i));
        }
        return formatedKey; 
    }

    public:
    std::string Encrypt(const std::string& key, const std::string& plainText) {
        return Transform(key, plainText);
    }

    std::string Decrypt(const std::string& key, const std::string& cipherText) {
        return Transform(key, cipherText);
    }

    bool ValidateKey(const std::string& key, const std::string& text) {
        return true;
    } 

    void KeyDesc() {
        std::cout << "The key is variable length set of characters in [a-z, NULL, CR, SP, LF, FS, LS]" << std::endl;
    }

    void TextDesc() {
        std::cout << "The text must be contained in the set [a-z,NULL,CR,SP,LF,FS,LS]" << std::endl;
        std::cout << "N, 0x4E: null character" << std::endl;
        std::cout << "C, 0x43: Carriage Return" << std::endl;
        std::cout << "S, 0x53: Space" << std::endl;
        std::cout << "L, 0x4C: Line Feed" << std::endl;
        std::cout << "F, 0x46: Figure Shift" << std::endl;
        std::cout << "G, 0x47: Letter Shift" << std::endl;
        std::cout << "**Since limited text input these are mapped to the capital ascii letter" << std::endl;
    }
};


#endif
