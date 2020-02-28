#ifndef HOMOMORPHISM_PIPEHANDLER_H_
#define HOMOMORPHISM_PIPEHANDLER_H_

#include <sstream>

class PipeHandler
{
public:
    PipeHandler(FILE* input, FILE* output)
            : input_(input), output_(output) {}

	static PipeHandler openNauty();
	static PipeHandler openTamaki();

	void write(const std::string& str);
	void writeLine(const std::string& str);
	std::string nextLine();
	void nextLine(std::ostream& os);
	bool closePipes();

private:
	FILE *input_, *output_;

    static PipeHandler open(const char* file, const char* argv, ...);
};

#endif 
