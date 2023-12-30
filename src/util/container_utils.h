#ifndef CONTAINER_UTILS_H
#define CONTAINER_UTILS_H


class ArrayUtils
{
public:
    template<class Input, class Output>
    static Output Chunk(const Input& input, const int& chuckSize)
    {
        Output output;
        for (size_t i = 0; i < input.size(); i += chuckSize) {
            auto last = std::min(input.size(), i + chuckSize);
            output.emplace_back(input.begin() + i, input.begin() + last);
        }
        return output;
    }
};

#endif // CONTAINER_UTILS_H
