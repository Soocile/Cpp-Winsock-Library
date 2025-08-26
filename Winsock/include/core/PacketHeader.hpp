#ifndef PACKETHEADER_HPP
#define PACKETHEADER_HPP

#include<iostream>

namespace Net {


#pragma pack(push,1)

	struct packetheader {

		uint16_t packet_type; //defines the type of message by ID
		uint32_t payloadsize;// size of the payload in bytes


	};
#pragma pack(pop)




}





#endif // PACKETHEADER_HPP