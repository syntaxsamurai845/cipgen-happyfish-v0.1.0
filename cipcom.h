#ifndef CIPCOM_H
#define CIPCOM_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <stdexcept>

//function for encrypting one char
char shiftChar(char c, int key){
	if (isupper(c)) {
		return 'A' + (c - 'A' + key + 26) % 26;
	} else if (islower(c)) {
		return 'a' + (c - 'a' + key + 26) % 26;
	} else {
		return c;

	} 

}

//function for caesar encryption
std::string caescrypt(const std::string &in, int key){

	//initializing necessary variables
	std::string out;
	out.reserve(in.size());
	for(char c : in){
		out += shiftChar(c, key);
	}
	return out;
}
//function to get the position of the letter
int getpos(char c){
	c = tolower(c);

	if(c >= 'a' && c <= 'z'){
		return c - 'a' + 1;
	}
	return -1;
}

//number-mapping function
std::string numcrypt(const std::string &in){

	//initializing necessary variables
	std::string out;
	int len = in.length();

	//encryption loop
	for(int i = 0; i < len; i++){
		char cur = in[i];
		if(std::isalpha(cur)){
			int num = getpos(cur);
			if(num < 10) out += '0';
			out += std::to_string(num);
		}else if(cur == ' '){
			out += '/';
		}else{
			out += cur;
		}
	}

	//return encrypted text
	return out;
}

//function to decrypt the numbermapped text
std::string denumcrypt(const std::string &in){

	//necessary variables
	std::string out;
	int len = in.length();

	//decryption loop
	for(int i = 0; i < len; ){
		char cur = in[i];

		if(isdigit(cur)){
			if(i + 1 < len && isdigit(in[i + 1])){
				int num = (cur - '0') * 10 + (in[i + 1] - '0');
				if(num >= 1 && num <= 26) {
					out += 'a' + (num - 1);
					i += 2;
					continue;
				}
			}
			out += cur;
		} else if(cur == '/') {
			out += ' ';
		} else {
			out += cur;
		}

		i++;

	}

	//return decrypted text
	return out;

}

//function to reverse a given string
std::string revcrypt(const std::string &in){

	std::string out = in;
	std::reverse(out.begin(), out.end());
	return out;
}

//function to read a text file
std::string rd(std::ifstream& file){

	std::string out;
	std::string line;
	while(getline(file, line)) {
		out += line + "\n";
	}
	return out;

}

//function to read a binary file
std::vector<unsigned char> rd_bin(std::ifstream &in){
	if(!in.is_open()){
		throw std::runtime_error("Can't read byte data, check if file path is correct.");
	}

	std::vector<unsigned char> dat(
			(std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>()
			);

	return dat;
}

//function to encrypt a byte file
void bytecrypt(std::ifstream& in, std::ofstream &out, unsigned char key){

	std::vector<unsigned char> dat = rd_bin(in);

	for(auto &byte : dat){
		byte = (byte + key) % 256;
	}

	std::reverse(dat.begin(), dat.end());
	out.write(reinterpret_cast<char*>(dat.data()), dat.size());
}

//function to decrypt a byte file
void bytedecrypt(std::ifstream &in, std::ofstream &out, unsigned char key){
	std::vector<unsigned char> dat = rd_bin(in);
	std::reverse(dat.begin(), dat.end());
	for(auto &byte : dat){
		byte = (byte - key + 256) % 256;  
	}
	out.write(reinterpret_cast<char*>(dat.data()), dat.size());
}
#endif
