//====
// rmcc.cpp
// - relocate C/C++ variable name pieces
// - usage: rmcc <input_file> <output_file> <_namepart_...>
//====
// g++ rmcc.cpp -o rmcc.exe -std=gnu++0x -I/Cpp/Boost/include/boost-1_55

#include <iostream>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

int matches = 0, partials = 0;

void parse(ifstream &fin, ofstream &fout, string relocate)
{
	cout << endl << relocate << " " << relocate.size() << endl;
    char curr, prev = '\0';

	bool inBlock = false;
	bool inFind = false, doneFind = false;
	int loc = 0;
    while (fin.get(curr)) {
		if (inBlock) {
			if (inFind) {
				++partials;
				if (prev == relocate[loc]) {
					//cout << relocate.size() << " == " << loc << endl;
					if (relocate.size() == loc + 1) {
						//cout << "string is over!" << endl;
						if (curr != '_') {
							fout << relocate << curr;
						} else {
							doneFind = true;
						}
						inFind = false;
						inBlock = false;
						loc = 0;
					} else {
						if (curr != relocate[loc + 1]) {
							string back = relocate.substr(0, loc + 1);
							//cout << back << " <<" << endl;
							inFind = false;
							inBlock = false;
							loc = 0;
							fout << back << curr;
						} else {
							//cout << "char " << curr << " consumed!" << endl;
							++loc;
						}
					}
				} else {
					//cout << "Problem, sir?" << endl << prev << " == " << relocate[loc] << endl;
					return;
				}
			} else {
				if (curr == relocate[0]) {
					inFind = true;
				} else {
					inBlock = false;
					fout << curr;
				}
			}
			prev = curr;
		} else if (doneFind) {
			//cout << "Match!" << endl;
			if (isalnum(curr)) {
				//cout << "o.o" << endl;
				fout << curr;
			} else {
				++matches;
				doneFind = false;
				fout << "_" << relocate << curr;
			}
		} else if (curr == '_') {
			inBlock = true;
			fout << curr;
		} else {
			fout << curr;
		}
    }
}

int main(int argc, char *argv[])
{
    if (argc < 4) {
        cerr << "Usage:\t" << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

	string sfin = argv[1];
	string sfout = argv[2];
	string tfile = "";
	int replacer = 3;
	while (replacer < argc) {
		string relocate = argv[replacer++];

		ifstream fin(sfin.c_str());
		ofstream fout;
		if (replacer == argc) {
			fout.open(sfout.c_str());
		} else {
			tfile = "removeME" + lexical_cast<string>(replacer);
			fout.open(tfile.c_str());
		}
		if (!fin) {
			cerr << "Error:\t\"" << argv[1] << "\" - no such file\n";
			return 1;
		}

		parse(fin, fout, relocate);

		fin.close();
		if (replacer > 4) {
			remove(sfin.c_str());
		}
		fout.close();
		sfin = tfile;

		cout << "Matches: " << matches << endl << "Partial matches: " << partials << endl;
		matches = partials = 0;
	}

    return 0;
}
