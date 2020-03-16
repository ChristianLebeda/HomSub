#ifndef HOMOMORPHISM_MAPPINGITERATOROLD_H_
#define HOMOMORPHISM_MAPPINGITERATOROLD_H_

#include <memory>
#include <vector>

class MappingIteratorOld
{
public:
	MappingIteratorOld(int n, int k) : n_(n), mapping(std::vector<size_t>(k, 0)) {}

	static std::shared_ptr<MappingIteratorOld> makeIterator(int n, int k);

	std::vector<size_t> mapping;
	size_t idx = 0;

	bool next();
private:
	size_t n_;
};

#endif