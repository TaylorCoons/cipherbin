cipherbin: cipherbin.cpp CLIParser/CLIParser.h CLIParser/CLIParser.cpp Cipher.h CaeserCipher.h MonoalphabeticCipher.h
	g++ -g -o cipherbin CLIParser/CLIParser.h CLIParser/CLIParser.cpp Cipher.h CaeserCipher.h MonoalphabeticCipher.h cipherbin.cpp

