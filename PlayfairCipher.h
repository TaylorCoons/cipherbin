#ifndef CaeserCipher_h
#define CeaserCipher_h

#include <string>
#include <iostream>

#include "Cipher.h"

/* 
* PlayfairCipher class
*/

class PlayfairCipher : Cipher {
   
    /* Variables */
    private:
    char table[5][5];
    const char filler = 'x';
 
    /* Functions */
    private:
    std::string FormatKey(const std::string& key) {
        std::string formatedKey;
        formatedKey.clear();
        formatedKey.push_back(key[0]);
        for (int i = 1; i < key.size(); i++) {
            if (key[i] == 'q') {
                continue;   
            }
            if (key[i] == key[i - 1]) {
                continue;
            } else {
                formatedKey.push_back(key[i]);
            }
        }
        std::cout << "Formated Key: " << formatedKey << std::endl;
        return formatedKey;
    }

    std::string FormatPlainText(const std::string& plainText) {
        std::string formatedText;
        for (int i = 0; i < plainText.size(); i += 2) {
            formatedText.push_back(plainText[i]);
            if ((i + 1) < plainText.size()) {
                if (plainText[i] == plainText[i + 1]) {
                    formatedText.push_back(filler);
                    i--;
                }
                else {
                    formatedText.push_back(plainText[i + 1]);
                }
            }
        }
        if (formatedText.size() % 2) {
            formatedText.push_back(filler);
        }
        std::cout << "Formated Text: " << formatedText << std::endl;
        return formatedText;
    }
    
    void PopulateTable(const std::string& formatedKey) {
        char usedChars[25] = { 
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
            'n', 'o', 'p', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' 
        };
        for (unsigned int i = 0; i < formatedKey.size(); i++) {
            table[i / 5][i % 5] = formatedKey[i];
            uint8_t kOrd = static_cast<uint8_t>(formatedKey[i] - 'a');
            if (kOrd > 'p') {
                kOrd--;
            }
            usedChars[kOrd] = '\0';
        } 
        for (unsigned int i = formatedKey.size(); i < 25; i++) {
            for (unsigned int j = 0; j < 25; j++) {
                if (usedChars[j] != '\0') {
                    table[i / 5][i % 5] = usedChars[j];
                    usedChars[j] = '\0';
                    break;
                }
            }
        }
        for (unsigned int i = 0; i < 5; i++) {
            for (unsigned int j = 0; j < 5; j++) {
                std::cout << table[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
     
    public:
    std::string Encrypt(const std::string& key, const std::string& plainText) {
        std::string cipherText;
        std::string formatedKey = FormatKey(key);
        std::string formatedText = FormatPlainText(plainText);
        std::cout << "Formated textittt: " << formatedText << std::endl;
        PopulateTable(formatedKey);
        for (unsigned int i = 0; i < formatedText.size(); i += 2) {
            unsigned int rowA = 0;
            unsigned int colA = 0;
            bool match = false;
            for (rowA = 0; rowA < 5; rowA++) {
                for (colA = 0; colA < 5; colA++) {
                    std::cout << "A " << rowA << colA << " : " << table[rowA][colA] << std::endl;
                    std::cout << "text[i]: " << formatedText[i] << std::endl;
                    if (table[rowA][colA] == formatedText[i]) {
                        std::cout << "Match found" << std::endl;
                        match = true;
                    }
                    if (match) {
                        break;
                    }
                }
                if (match) {
                    break;
                }
            }
            unsigned int rowB = 0;
            unsigned int colB = 0;
            match = false;
            for (rowB = 0; rowB < 5; rowB++) {
                for (colB = 0; colB < 5; colB++) {
                    if (table[rowB][colB] == formatedText[i + 1]) {
                        match = true;
                    }
                    if (match) {
                        break;
                    }
                }
                if (match) {
                    break;
                }
            }
            std::cout << "A(" << rowA << ", " << colA << ")=" << table[rowA][colA] << std::endl;
            std::cout << "B(" << rowB << ", " << colB << ")=" << table[rowB][colB] << std::endl;
            if (rowA == rowB) {
                colA = (colA + 1) % 5;
                colB = (colB + 1) % 5;
            } else if (colA == colB) {
                rowA = (rowA + 1) % 5;
                rowB = (rowB + 1) % 5;
            } else {
                unsigned int tmp = colA;
                colA = colB;
                colB = tmp;
            }
            std::cout << "A'(" << rowA << ", " << colA << ")=" << table[rowA][colA] << std::endl;
            std::cout << "B'(" << rowB << ", " << colB << ")=" << table[rowB][colB] << std::endl;
            cipherText.push_back(table[rowA][colA]);
            cipherText.push_back(table[rowB][colB]);
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
        return true; 
    };

};

#endif
