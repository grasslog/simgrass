#ifndef SIM_DECODER_H_
#define SIM_DECODER_H_

#include <string>
#include "message.h"

namespace sim{

class Decoder
{
private:
	std::string buffer_;
public:
	int push(const char *buff, int len);
	int parse(Message *msg);
};

};

#endif
