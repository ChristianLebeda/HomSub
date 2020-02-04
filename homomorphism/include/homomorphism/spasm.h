#ifndef HOMOMORPHISM_SPASM_H_
#define HOMOMORPHISM_SPASM_H_

class Spasm
{
public:
    Spasm(std::vector<std::tuple<Graph, int>> g) : graphs_(g) {};

    static std::shared_ptr<Spasm> fromFile(std::string path);
    static std::shared_ptr<Spasm> createSpasm(Graph H);
    static std::shared_ptr<Spasm> testSpasm();

    std::size_t size();
    std::tuple<Graph, int>& operator[](std::size_t position);
    std::string toString();

private:
    std::vector<std::tuple<Graph, int>> graphs_;
};

#endif