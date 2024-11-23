// Algorithms - Transform - Unary Operation
// transform_u.cpp
#include <string>
#include <iostream>

using namespace std;

void trim(std::string &str)
{
    size_t i = 0u;
    for (i = 0u; i < str.length() && str[i] == ' '; ++i)
        ;
    str = str.substr(i);

    for (i = str.length(); i > 0 && str[i - 1] == ' '; --i)
        ;
    str = str.substr(0, i);
}

string extractToken(const std::string &str, size_t &next_pos, bool &more)
{

    int delimiterPosition = str.find('|');

    if (delimiterPosition == str.length())
        more = false;

    string subString = str.substr(next_pos, delimiterPosition);
    next_pos = delimiterPosition + 1;
    trim(subString);

    return subString;
}

int main()
{

    string str = "Cornel B. | 1-Room Home Office             | Office Chair|Desk|Bookcase|Bookcase|Filing Cabinet";
    size_t nextPosition = 0;
    bool more = true;
    const string delimiter = "|";

    while (more)
    {
        cout << extractToken(str, nextPosition, more) << endl;
    }

    return 0;
}