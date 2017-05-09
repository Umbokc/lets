#ifndef MATH_LETS
#define MATH_LETS
#include "math.h"

using namespace std;

void Lets(string);

int main(int argc, char const *argv[]) {

	if(argc <= 1){
		error("Give me code!");
	}

	string input = "";

	cout << "math: " << endl;
	for (int i = 1; i < argc; i++) {
		switch(s2i(argv[i])){
			case s2i("-func") :
				input += argv[i+1];
				input += " ";
				break;
		}
	}

	Lets(input);

	return 0;
}


void Lets(string input){

}

#endif