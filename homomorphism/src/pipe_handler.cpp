#include "homomorphism/pipe_handler.h"

#include <iostream>
#include <unistd.h>

PipeHandler PipeHandler::open(bool tamaki) //const char* file, const char* argv ...)
{
    //Create pipes for read and write
    int inp[2], outp[2];
    pipe(inp);
    pipe(outp);   
    
    //Fork
    switch (fork()) {
        case -1:
            perror("could not fork");
            exit(EXIT_FAILURE);

        case 0:
            //child process starts external code
            close(inp[0]); close(1); dup(inp[1]); close(inp[1]);
            close(outp[1]); close(0); dup(outp[0]); close(outp[0]);


            if(tamaki) {
                execlp("java", "-Xmx30g -Xms30g -Xss10m", "tw.exact.MainDecomposer", (const char*)NULL);
            } else {
                execlp("./dreadnaut", (const char*) NULL);
            }

            //TODO: Fix!
            //execlp(file, argv, (const char*) nullptr);

            perror("exec");
            exit(EXIT_FAILURE);
    }

    // parent process

    // write to outp[1]; read from inp[0]
    FILE* output = fdopen(inp[0], "r");
    FILE* input = fdopen(outp[1], "w");

    return PipeHandler(input, output);
}

PipeHandler PipeHandler::openNauty()
{
    return open(false);
    //return open("./dreadnaut", "./dreadnaut");
}

PipeHandler PipeHandler::openTamaki()
{
    return open(true);
    //return open("java", "-Xmx30g -Xms30g -Xss10m", "tw.exact.MainDecomposer");
}

void PipeHandler::write(const std::string& str)
{
    fprintf(input_, "%s", str.c_str());
    std::fflush(input_);
}

void PipeHandler::writeLine(const std::string& str)
{
    fprintf(input_, "%s\n", str.c_str());
    std::fflush(input_);
}

std::string PipeHandler::nextLine() 
{
    if(feof(output_)) return "";

    char buffer [256];
    fgets(buffer, 256, output_);

    return buffer;
}

void PipeHandler::nextLine(std::ostream& os) 
{
    char buffer [256];
    fgets(buffer, 256, output_);

    os << buffer;
}

bool PipeHandler::closePipes()
{
	return fclose(input_) + fclose(output_);
}
