#ifndef HOMOMORPHISM_MAPPINGITERATOR_H_
#define HOMOMORPHISM_MAPPINGITERATOR_H_

#include <vector>
#include <memory>

class MappingIterator
{
public:
	MappingIterator(int n, int k) : n_(n), mapping(std::vector<size_t>(k, 0)) {}

	static std::shared_ptr<MappingIterator> makeIterator(int n, int k);

	std::vector<size_t> mapping;
	size_t idx = 0;

	bool next();
private:
	size_t n_;
};

#endif