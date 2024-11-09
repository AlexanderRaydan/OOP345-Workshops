// Algorithms - Transform - Unary Operation
// transform_u.cpp
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <numeric>

using namespace std;
int main()
{
    std::vector<int> v = {1, 2, 4, 5, 7, 8, 10, 13, 17, 21, 43};
    std::vector<int> c(11);
    std::transform(v.begin(), v.end(), c.begin(), [](int i)
                   { return 3 * i; });
    for (auto i : c)
        std::cout << i << std::endl;
    cout << "****************************************************************" << endl;

    std::vector<function<void()>> funcs;
    for (int i = 0; i < 10; ++i)
        funcs.push_back([i]
                        { cout << i << endl; });
    for (auto f : funcs)
        f();

    cout << "****************************************************************" << endl;
    int a[] = {1, 2, 4, 5, 8, 9, 12, 13, 16, 18, 22};
    int n = std::count_if(a, a + 10, [](int i)
                          { return !(i & 1); });
    std::cout << n << std::endl;

    cout << "****************************************************************" << endl;

    int aa[] = {3, 2, 4, 1}, b[] = {1, 2, 3, 4}, s;
    s = std::inner_product(aa, &aa[4], b, (int)0);
    std::cout << s << std::endl;
    s = std::inner_product(aa, &aa[4], b, (int)0, std::plus<int>(), [](int x, int y)
                           { return (x - y) * (x - y); });
    std::cout << s << std::endl;
}