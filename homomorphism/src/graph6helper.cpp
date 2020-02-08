#include "homomorphism/graph6helper.h"
#include <sstream>

char Graph6helper::R(size_t x) {
	return (char) (x & 0x3F) + 63;
}

std::string Graph6helper::N(size_t x) {
	std::ostringstream str;
	if (x <= 62) {
		str << (char) (x + 63);
	}
	else if (x <= 258047) {
		str << (char) 126 << R(x >> 12) << R(x >> 6) << R(x);
	}
	else {
		str << (char) 126 << (char) 126 << R(x >> 30) << R(x >> 24)
			<< R(x >> 18) << R(x >> 12) << R(x >> 6)  << R(x);
	}
	return str.str();
}

size_t Graph6helper::readN(std::stringstream& in) {
	unsigned char c;
	in >> c;
	if (c != 126) {
		// n <= 62
		return c - 63;
	} 

	in >> c;
	size_t size, out = 0;
	if (c != 126) {
		// 63 <= n <= 258047
		out = c - 63; 
		size = 2;
	}
	else {
		// 258047 < n
		size = 6;
	}
	
	// Read the remaining values
	for (size_t i = 0; i < size; i++)
	{
		out <<= 6;
		in >> c;
		out += c - 63;
	}

	return out;
}
