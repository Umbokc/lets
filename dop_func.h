#ifndef DOP_FINC_H
#define DOP_FINC_H

void dbg (std::string s){	std::cout << "debug: " << s << std::endl; }
void dbg (char s){	std::cout << "debug: " << s << std::endl; }


void dbg (double s){	std::cout << "debug: " << s << std::endl; }
void dbg (int s){	std::cout << "debug: " << s << std::endl; }

void error (std::string s){	std::cout << "Error: " << s << std::endl; exit(1); }

constexpr unsigned int s2i(const char* str, int h = 0) { // str2int
    return !str[h] ? 5381 : (s2i(str, h+1) * 33) ^ str[h];
}

int compareTo(std::string const & s1, std::string const & s2) {
	return (s1 > s2) ? 1 : (s1 < s2) ? -1 : 0;
}

std::string appendctos(std::string const & s, char a) {
	return s + a;
}

std::string ctos(char a) {
	std::string s = "";
	return appendctos(s,a);
}

std::string strToLower (std::string str) {
	std::locale loc;
	std::string str_new;

	for(auto elem : str){
		str_new = appendctos(str_new, std::tolower(elem,loc));
	}

	return str_new;
}

std::string dtos (double d) {
	std::ostringstream strs;
	strs << d;
	return strs.str();
	// return "lol";
}

int find_c(std::string s, char c){
	for (int i = 0; i < s.length(); i++)
		if (s[i] == c)
			return i;
		
	return -1;		
}
#endif