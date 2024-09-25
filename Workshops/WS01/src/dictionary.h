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

}

#endif
