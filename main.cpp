#include <iostream>

using namespace std;

template <typename T>
void print(T &val)
{
    std::cout << "I-value:" << val << std::endl;
}
template <typename T>
void print(T &&val)
{
    std::cout << "r-value:" << val << std::endl;
}

// example of template specialization
template <>
void print(string &val)
{
    std::cout << "r-value:" << val << std::endl;
}

int main()
{

    int xyz = 10;
    int *ptr{&xyz};
    int &&gg(std::move(xyz));
    print(int(*++--ptr += 10)); // r-value:20
    print(*ptr);                // I-value:20, memory location
    // xyz++;
    print(gg++); // r-value:20, I dont remember but is temporary value, right side
    print(++gg); // I-value:22, I dont remember but is a memory location
    print(gg);   // I-value:22, memory location
    return 0;
}