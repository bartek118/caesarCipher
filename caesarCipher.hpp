#ifndef CAESARCIPHER_HPP
#define CAESARCIPHER_HPP

#include <boost/lambda/lambda.hpp>

#include <algorithm>
#include <iterator>

#include <fstream>

using namespace boost::lambda;

class caesarCipher {
	public:
		caesarCipher() {
			key = 3;
		}

		caesarCipher(int _key) {
			key = _key%26;
		}

		void encodeStream(std::istream& fileIn, std::ostream& fileOut) {
			char c;
			while(fileIn.get(c)) {
				fileOut << encodeLetter(c);
			}
		}

		void decodeStream(std::istream& fileIn, std::ostream& fileOut) {
			char c;
			while(fileIn.get(c)) {
				fileOut << decodeLetter(c);
			}
		}

	private:
		int key;

		char encodeLetter(char c) {
			if(c >= 'a' && c <= 'z') {
				return (char) ((c - 'a' + key)%26 + 'a');
			}

			if(c >= 'A' && c <= 'Z') {
				return (char) ((c - 'A' + key)%26 + 'A');
			}

			return c;
		}

		char decodeLetter(char c) {
			if(c >= 'a' && c <= 'z') {
				return (char) ((c - 'a' + 26 - key)%26 + 'a');
			}

			if(c >= 'A' && c <= 'Z') {
				return (char) ((c - 'A' + 26 - key)%26 + 'A');
			}

			return c;
		}
};

#endif
