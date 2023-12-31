#ifndef CONTAINER_UTILS_H
#define CONTAINER_UTILS_H

#include <range/v3/view/chunk.hpp>

class ArrayUtils
{
public:
    template<class Input, class Output>
    static Output Chunk(const Input& input, const int& chuckSize)
    {
        return input | ranges::views::chunk(chuckSize);
    }
};

#endif // CONTAINER_UTILS_H
