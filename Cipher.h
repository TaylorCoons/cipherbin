#ifndef Cipher_h
#define Cipher_h

#include <string>

/*
* Pure virtual base class representing a cipher
*/
class Cipher {
    
    /* Functions */
    private:

    public:
    virtual std::string Encrypt(const std::string& key, const std::string& plainText) = 0;
    virtual std::string Decrypt(const std::string& key, const std::string& cypherText) = 0;
    virtual bool ValidateKey(const std::string& key, const std::string& text) = 0;
    

};


#endif
