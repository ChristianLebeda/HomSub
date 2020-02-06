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
