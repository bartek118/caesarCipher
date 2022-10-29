#include <iostream>
#include <fstream>

#include <cstring>

#include "caesarCipher.hpp"

using namespace std;

class Main {
	public:
		int start(int argc, char* argv[]) {
			bool dec; 					// decoding = 1, encoding = 0
			bool setKey = 0; 				// key set = 1, default key(3) = 0
			char* fileIn = NULL;				// input filename
			char* fileOut = NULL;				// output filename
			int key;					// encryption key

			// if we didn't read all params properly, return 0 to OS
			if(readParams(argc, argv, dec, setKey, fileIn, fileOut, key) == 1) {
				return 0;
			}

			decEnc(setKey == 1 ? key : 3, fileIn, fileOut, dec);

			return 0;
		}

	private:
		// returns 0 if fine, return 1 if Usage is shown and return to OS
		int readParams(int argc, char* argv[], bool& dec, bool& setKey, char*& fileIn, char*& fileOut, int& key) { 
			fileIn = NULL;
			fileOut = NULL;
			setKey = 0;

                        if(argc < 2) {
                                printUsage(argv);
                                return 1;
                        }

			for(int i = 1; i < argc; i++) {
                                if(argv[i][0] == '-') {
                                        if(strlen(argv[i]) < 2) {
                                                printUsage(argv);
                                                return 1;
                                        }

                                        if(argv[i][1] == 'e' || argv[i][1] == 'd') {
                                                dec = (argv[i][1] == 'd');
                                                if(i+1 < argc && argv[i+1][0] != '-') {
                                                        fileIn = argv[i+1];
                                                        i++;
                                                }
                                        }
                                        else if(argv[i][1] == 'k') {
                                                setKey = 1;
                                                if(i+1 < argc) {
                                                        key = atoi(argv[i+1]);
                                                        i++;
                                                }
                                                else {
                                                        std::cout << "Encryption key not set" << std::endl;
                                                        printUsage(argv);
                                                        return 1;
                                                }
                                        }
                                }
                                else if(fileIn == NULL) {
                                        fileIn = argv[i];
                                }
                                else if(fileOut == NULL) {
                                        fileOut = argv[i];
                                }
                                else {
                                        std::cout << fileIn << " " << fileOut << std::endl;
                                        printUsage(argv);
                                        return 1;
                                }
                        }

			return 0;
		}

		void printUsage(char* argv[]) {
			std::cout << "Usage: " << argv[0] << " -d/-e [inputFile] [-k key] [outputFile]" << std::endl;
		}

		// dec = 1 denotes decoding
		void decEnc(int key, char* fileIn, char* fileOut, bool dec) {
			caesarCipher C(key);

                        ifstream in(fileIn);
                        ofstream out(fileOut);

			if(dec) {
				C.decodeStream(fileIn == NULL ? std::cin : in, fileOut == NULL ? std::cout : out);
			}
			else {
	                        C.encodeStream(fileIn == NULL ? std::cin : in, fileOut == NULL ? std::cout : out);
			}

                        in.close();
                        out.close();
		}
};

int main(int argc, char* argv[]) {
	Main M;
	return M.start(argc, argv);
}
