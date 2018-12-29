#include "sim.h"
#include <string>

namespace sim{

static const std::string hex = "0123456789abcdef";

std::string encode(const std::string& str){
	std::string result;
	int size = (int)str.size();
	for(int i= 0;i<size;i++){
		char c = str[i];
		switch(c){
			case ' ':
				result.append("\\s");
				break;
			case '\t':
				result.append("\\t");
				break;
			case '\r':
				result.append("\\r");
				break;
			case '\n':
				result.append("\\n");
				break;
			case '\\':
				result.append("\\\\");
				break;
			default:
				if(c >= '!' && c <= '~'){
					result.push_back(c);
				}else{
					result.append("\\x");
					unsigned char d = c;
					result.push_back(hex[d >> 4]);
					result.push_back(hex[d & 0x0f]);
				}
				break;
		}
	}
	return result;
}

inline static int hex_int(char c){
if(c >= '0' && c <= '9'){
return c - '0';
}else{
return c - 'a' + 10;
}
}

std::string decode(const std::string& str){
	std::string ret;
	int size = (int)str.size();
	char c;
	for(int i= 0;i<size;i++){
		 c = str[i];
		if(c != '\\'){
		ret.push_back(c);
		continue;
		}
		 c = str[++i];
		switch(c){
			case 's':
				ret.push_back(' ');
				break;
			case 't':
				ret.push_back('\t');
				break;
			case 'r':
				ret.push_back('\r');
				break;
			case 'n':
				ret.push_back('\n');
				break;
			case '\\':
				ret.push_back('\\');
				break;
			case 'x':
				if(i < size - 2){
				char c3 = str[++i];
				char c4 = str[++i];
				ret.push_back((char)((hex_int(c3) << 4) + hex_int(c4)));
				}
				break;
			default:
				ret.push_back(c);
				break;
		}
	}
	return ret;
}


};
