#ifndef NICE_TREE_PIPEHANDLER_H_
#define NICE_TREE_PIPEHANDLER_H_

#include <sstream>

class PipeHandler
{
public:
	PipeHandler(std::istringstream& tt) : tmpstring(tt) {};

	void write(std::string str);
	void writeLine(std::string str);
	std::string nextLine();
	void nextLine(std::ostream& os);
	bool close();

private:
	std::istringstream& tmpstring;
};

#endif 
