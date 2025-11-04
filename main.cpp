#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
#include "cipcom.h"
using namespace std;

int main() {

    //initialize necessary variables
    char op1;
    char op2;
    char op3;
    string in;
    string out;
    string keyin;
    string fpath;
    unsigned char bkey;
    int key;

    //print out available options
    cout << "CipGen HappyFish v1" << endl;
    cout << "===================" << endl;
    cout << "available options:" << endl;
    cout << "1. enter directly into the terminal" << endl;
    cout << "2. en/decrypt entire files" << endl;
    cout << "q. quit" << endl;
    cout << "> ";
    cin >> op1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    //direct terminal interaction
    if (op1 == '1') {
        cout << "(d)ecrypt or (e)ncrypt" << endl;
        cout << "> ";
        cin >> op2;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

		//encryption
        if (op2 == 'e') {
            cout << "Enter your text: ";
            getline(cin, in);
            cout << "Enter the caesar encryption key: ";
            getline(cin, keyin);
            stringstream(keyin) >> key;
            out = caescrypt(in, key);
            cout << "Step 1: Caesar Cipher: " << out << endl;
            out = numcrypt(out);
            cout << "Step 2: Number Mapping: " << out << endl;
            out = revcrypt(out);
            cout << "Final Encrypted text: " << out << endl;
        }
		//decryption
        else if (op2 == 'd') {
            cout << "Enter your encrypted text: ";
            getline(cin, in);
            cout << "Enter the caesar encryption key: ";
            getline(cin, keyin);
            stringstream(keyin) >> key;
            out = revcrypt(in);
            cout << "Step 1: Numbers in normal position: " << out << endl;
            out = denumcrypt(out);
            cout << "Step 2: Reverse-Mapping Numbers on Letters: " << out << endl;
            out = caescrypt(out, -key);
            cout << "Final encrypted text: " << out << endl;
        }
		//invalid args
        else {
            throw runtime_error("Invalid option, view manual for more information");
        }
    }
	//file de-/encryption
    else if (op1 == '2') {
        cout << "(t)ext or (b)yte file type " << endl;
        cout << "> ";
        cin >> op2;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter file path: ";
        getline(cin, fpath);

		//text file
        if (op2 == 't') {
            cout << "(d)ecryption or (e)ncryption" << endl;
            cout << "> ";
            cin >> op3;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

			//encryption
            if (op3 == 'e') {
                ifstream inf(fpath);
                if (!inf.is_open())
                    throw runtime_error("Error opening file, check filepath");

                in = rd(inf);
                inf.close();

                cout << "Enter caesar encryption key: ";
                getline(cin, keyin);
                stringstream(keyin) >> key;

                out = caescrypt(in, key);
                out = numcrypt(out);
                out = revcrypt(out);

                ofstream of(fpath);
                if (!of.is_open())
                    throw runtime_error("Couldn't open file for writing");

                of << out;
                of.close();
            }
			//decryption
            else if (op3 == 'd') {
                ifstream inf(fpath);
                if (!inf.is_open())
                    throw runtime_error("Can't open input file.");

                in = rd(inf);
                inf.close();

                cout << "Enter caesar decryption key: ";
                getline(cin, keyin);
                stringstream(keyin) >> key;

                out = revcrypt(in);
                out = denumcrypt(out);
                out = caescrypt(out, -key);

                ofstream of(fpath);
                if (!of.is_open())
                    throw runtime_error("Couldn't open file for writing.");

                of << out;
                of.close();
            }
        }
		//byte file
        else if (op2 == 'b') {
            cout << "(d)ecryption or (e)ncryption" << endl;
            cout << "> ";
            cin >> op3;

			//encryption
            if (op3 == 'e') {
                ifstream inf(fpath, ios::binary);
                if (!inf.is_open()) throw runtime_error("Can't open input byte file");

                ofstream temp("temp.bin", ios::binary);
                if (!temp.is_open()) throw runtime_error("Can't create temp file");

                cout << "Enter caesar encryption key (0 - 255): ";
                cin >> bkey;

                bytecrypt(inf, temp, bkey);
                inf.close(); temp.close();

                remove(fpath.c_str());
                rename("temp.bin", fpath.c_str());
            }
			//decryption
            else if (op3 == 'd') {
                ifstream inf(fpath, ios::binary);
                if (!inf.is_open()) throw runtime_error("Can't open input byte file");

                ofstream temp("temp.bin", ios::binary);
                if (!temp.is_open()) throw runtime_error("Can't create temp file");

                cout << "Enter caesar decryption key (0 - 255): ";
                cin >> bkey;

                bytedecrypt(inf, temp, bkey);
                inf.close(); temp.close();

                remove(fpath.c_str());
                rename("temp.bin", fpath.c_str());
            }
			//invalid args
            else {
                throw runtime_error("Invalid option, read manual for more information");
            }
        }
		//invalid args
        else {
            throw runtime_error("Invalid option, view manual for more information");
        }
    }
	//quit
    else if (op1 == 'q') {
        exit(0);
    }
	//invalid arg
    else {
        throw runtime_error("Invalid option, view manual for more information");
    }

	//wait for enter to end
    cout << "Press Enter to exit...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return 0;
}
