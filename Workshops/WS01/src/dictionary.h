#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <string>
#include <iostream>
#include "settings.h"

namespace seneca
{

    enum PartOfSpeech
    {
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection
    };

    struct Word
    {
        std::string m_word = "";
        std::string m_definition = "";
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };

    class Dictionary
    {
        Word *words;
        size_t wordCount;

    public:
        // Default constructor
        Dictionary();

        // Constructor loads from file
        Dictionary(const char *filename);

        // Destructor
        ~Dictionary();

        // copy operations
        Dictionary(const Dictionary &);
        Dictionary &operator=(const Dictionary &);

        // Move operations
        Dictionary(Dictionary &&other);
        Dictionary &operator=(Dictionary &&other);

        void searchWord(const char *word) const;
    };

    template <typename T>
    T extract(const T array[], int len, int index)
    {

        if (index > len)
        {
            index = len;
        }
        T sum = 0;
        for (int i = 0; i < index; i++)
        {
            sum += array[i];
        }

        return sum;
    }

    template <>
    std::string extract<std::string>(const std::string array[], int len, int index)
    {
        if (index > len)
        {
            index = len;
        }
        std::string element = array[index];

        return array[index].substr(0, index);
    }

}

#endif
