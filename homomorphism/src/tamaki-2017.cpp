//
//  tamaki-2017.cpp
//  homomorphism
//
//  Created by Jonas Mortensen on 04/02/2020.
//

#include "homomorphism/tamaki-2017.h"
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <sstream>
#include <iostream>

std::shared_ptr<TreeDecomposition> Tamaki2017::decompose(std::shared_ptr<Graph> g)
{
    //Create pipes for read and write
    int inp[2], outp[2];
    pipe(inp);
    pipe(outp);

    //Fork
    switch (fork()) {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        //child Process
        close( inp[0]); close(1); dup( inp[1]); close( inp[1]);
        close(outp[1]); close(0); dup(outp[0]); close(outp[0]);

        execlp("java", "-cp /Users/jonasmortensen/Documents/Thesis/SubgraphThesis/build/test/Debug -Xmx30g -Xms30g -Xss10m", "tw.exact.MainDecomposer", (const char*)NULL);

        perror("exec");
        exit(EXIT_FAILURE);
    }
        
    // parent process
    
    // write to outp[1]; read from inp[0]
    FILE* fin  = fdopen(inp[0], "r");
    FILE* fout = fdopen(outp[1], "w");
    
    fprintf(fout, "p tw 4 4\n1 2\n2 3\n3 4\n4 1\n");
    
    fclose(fout);
    
    char buffer [256];
    if (fin == NULL) perror ("Error opening file");
    else
    {
        size_t bagN, width, n;
        std::shared_ptr <EdgeSetGraph> G;
        
        std::vector<std::unordered_set<size_t>> bags;
        
        int i = -1;
        size_t u, v;
        while ( ! feof (fin) )
        {
            if ( fgets (buffer , 256 , fin) == NULL ) break;
            std::string line = buffer;
            if(i < 0) { //Read header
                if (!std::sscanf(line.c_str(), "s td %zd %zd %zd", &bagN, &width, &n)) return nullptr;
                i = 0;
                bags.resize(bagN);
                G = std::make_shared<EdgeSetGraph>(n);
                continue;
            } else if (i < n) { //Read bag
                int bagI = -1;
                std::stringstream ss;
                ss << line;
                std::string temp;
                size_t util;
                while(!ss.eof())
                {
                    ss >> temp;
                    
                    if(std::stringstream(temp) >> util)
                    {
                        if(bagI < 0) bagI = util - 1;
                        else bags[bagI].insert(util);
                    }
                    
                    temp="";
                }
                bagI = -1;
                i++;
            } else { //Read edge
                if (!std::sscanf(line.c_str(), "%zd %zd", &u, &v)) {
                    std::cout << line << std::endl;
                    return nullptr;
                }

                G->addEdge(u - 1, v - 1);
            }
            
        }
        fclose (fin);
        return std::make_shared<TreeDecomposition>(G, bags, width);
    }
    std::cout << "This is wrong" << std::endl;
    return nullptr;
}
