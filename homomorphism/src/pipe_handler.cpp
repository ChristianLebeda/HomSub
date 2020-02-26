#include "homomorphism/pipe_handler.h"

void PipeHandler::write(std::string str)
{
}

void PipeHandler::writeLine(std::string str) 
{
}

std::string PipeHandler::nextLine() 
{
	std::string str;

	std::getline(tmpstring, str);

	return str;

}

void PipeHandler::nextLine(std::ostream& os) 
{
}

bool PipeHandler::close() 
{
	return false;
}
