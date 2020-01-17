HPP = Cipher.h CLIParser/CLIParser.h $(wildcard *Cipher.h)
CPP = CLIParser/CLIParser.cpp
cipherbin: $(CPP) $(HPP) cipherbin.cpp
	g++ -g -o cipherbin $(CPP) $(HPP) cipherbin.cpp

