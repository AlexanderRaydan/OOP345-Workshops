#include <iostream>
#include <cstring>
#include <string>

using namespace std;

namespace seneca
{
    class StringSet
    {
    private:
        string *m_strings = nullptr;
        int m_size = 0;

    public:
        StringSet(const string *name);
        ~StringSet();
        StringSet(const StringSet &other);
        StringSet &operator=(const StringSet &other);
        StringSet(StringSet &&other);
        StringSet &operator=(StringSet &&other);
    };

    StringSet::StringSet(const string *name)
    {
    }

    StringSet::~StringSet()
    {
        delete[] m_strings;
    }

    StringSet::StringSet(const StringSet &other)
    {
        *this = other;
    }

    StringSet &StringSet::operator=(const StringSet &other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] m_strings;
        m_strings = nullptr;

        m_size = other.m_size;
        m_strings = new string[m_size];

        for (int i = 0; i < m_size; i++)
        {
            m_strings[i] = other.m_strings[i];
        }

        return *this;
    }

    StringSet::StringSet(StringSet &&other)
    {
        *this = std::move(other);
    }

    StringSet &StringSet::operator=(StringSet &&other)
    {

        if (this == &other)
        {
            return *this;
        }

        delete[] m_strings;

        m_size = other.m_size;
        m_strings = other.m_strings;

        other.m_strings = nullptr;
        other.m_size = 0;

        return *this;
    }
}
