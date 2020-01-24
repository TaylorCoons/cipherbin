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
        char usedChars[25] = {};
        unsigned int numUsed = 0;
        for (int i = 0; i < key.size(); i++) {
            if (key[i] == 'q') {
                continue;   
            }
            if (i == 0) {
                formatedKey.push_back(key[i]);
                continue;
            }
            bool prevUsed = false;
            for (unsigned int j = 0; j < numUsed; j++) {
                if (key[i] == usedChars[j]) {
                    prevUsed = true;
                    break;
                }
            }
            if (prevUsed) {
                continue;
            } else {
                formatedKey.push_back(key[i]);
                usedChars[numUsed] = key[i];
                numUsed++;
            }
        }
        return formatedKey;
    }

    std::string FormatText(const std::string& text) {
        std::string formatedText;
        for (int i = 0; i < text.size(); i += 2) {
            formatedText.push_back(text[i]);
            if ((i + 1) < text.size()) {
                if (text[i] == text[i + 1]) {
                    formatedText.push_back(filler);
                    i--;
                }
                else {
                    formatedText.push_back(text[i + 1]);
                }
            }
        }
        if (formatedText.size() % 2) {
            formatedText.push_back(filler);
        }
        return formatedText;
    }
    
    void PopulateTable(const std::string& formatedKey) {
        char usedChars[26] = { 
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
            'n', 'o', 'p', '\0', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' 
        };
        for (unsigned int i = 0; i < formatedKey.size(); i++) {
            table[i / 5][i % 5] = formatedKey[i];
            uint8_t kOrd = static_cast<uint8_t>(formatedKey[i] - 'a');
            usedChars[kOrd] = '\0';
        } 
        for (unsigned int i = formatedKey.size(); i < 26; i++) {
            for (unsigned int j = 0; j < 26; j++) {
                if (usedChars[j] != '\0') {
                    table[i / 5][i % 5] = usedChars[j];
                    usedChars[j] = '\0';
                    break;
                }
            }
        }
    }
     
    std::string Transform(const std::string& formatedKey, const std::string& formatedText, bool forward) {
        int shiftDir = 1;
        if (!forward) {
            shiftDir *= -1;
        }
        PopulateTable(formatedKey);
        std::string transformedText;
        for (unsigned int i = 0; i < formatedText.size(); i += 2) {
            int rowA = 0;
            int colA = 0;
            bool match = false;
            for (rowA = 0; rowA < 5; rowA++) {
                for (colA = 0; colA < 5; colA++) {
                    if (table[rowA][colA] == formatedText[i]) {
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
            int rowB = 0;
            int colB = 0;
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
            if (rowA == rowB) {
                colA = (colA + shiftDir) % 5;
                colB = (colB + shiftDir) % 5;
                colA = (colA < 0 ? colA + 5 : colA);
                colB = (colB < 0 ? colB + 5 : colB);
            } else if (colA == colB) {
                rowA = (rowA + shiftDir) % 5;
                rowB = (rowB + shiftDir) % 5;
                rowA = (rowA < 0 ? rowA + 5 : rowA);
                rowB = (rowB < 0 ? rowB + 5 : rowB);
            } else {
                unsigned int tmp = colA;
                colA = colB;
                colB = tmp;
            }
            transformedText.push_back(table[rowA][colA]);
            transformedText.push_back(table[rowB][colB]);
        }
        return transformedText;
 
    }
    
    public:
    std::string Encrypt(const std::string& key, const std::string& plainText) {
        std::string formatedKey = FormatKey(key);
        std::string formatedText = FormatText(plainText);
        return Transform(formatedKey, formatedText, true);
    };

    std::string Decrypt(const std::string& key, const std::string& cipherText) {
        std::string formatedKey = FormatKey(key);
        std::string formatedText = FormatText(cipherText);
        return Transform(formatedKey, formatedText, false);
    };
    
    bool ValidateKey(const std::string& key, const std::string& text) {
        return true; 
    };

    void KeyDesc() {
        std::cout << "The key is a variable length set of characters in [a-z]" << std::endl;
    }

    void TextDesc() {
        std::cout << "The text must be contained in the set [a-z]" << std::endl;
    }

};

#endif
