#include <stdio.h>
#include <stdlib.h>
#include "sim.h"

int main(int argc, char **argv){
	sim::Message msg;
	msg.set_type("ok");
	msg.set(34,1);
	msg.set(35,"A");
	msg.set(49,"CLIENT 06\nhi");
	msg.set(56, "SERVER");
	msg.set(52,"20150424");
	
	std::string s = msg.encode();
	printf("%s \n", s.c_str());

	sim::Decoder decoder;
	for(int i= 0 ;i< 300; i++){
		decoder.push(s.data() + (i%s.size()),1);

		while(1){
			sim::Message tmp;
			int ret = decoder.parse(&tmp);
			if(ret == -1){
				printf("error! ret = %d\n", ret);
				exit(0);
			}else if(ret == 0){
				break;
			}

			printf("%s\n", tmp.get(49)->c_str());
			printf("%s", tmp.encode().c_str());
		}
	}

	return 0;
}
