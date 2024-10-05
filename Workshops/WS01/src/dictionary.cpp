#include "dictionary.h"
#include "settings.h"
#include <fstream>   // For file handling
#include <sstream>   // For string parsing
#include <stdexcept> // For exceptions

namespace seneca
{

    // Default constructor
    Dictionary::Dictionary() : words(nullptr), wordCount(0) {}

    // Destructor
    Dictionary::~Dictionary()
    {
        delete[] words;
        words = nullptr;
    }

    // Move constructor
    Dictionary::Dictionary(Dictionary &&other)
        : words(other.words), wordCount(other.wordCount)
    {
        other.words = nullptr;
        other.wordCount = 0;
    }

    // Move assignment operator
    Dictionary &Dictionary::operator=(Dictionary &&other)
    {
        if (this != &other)
        {
            delete[] words;

            words = other.words;
            wordCount = other.wordCount;

            other.words = nullptr;
            other.wordCount = 0;
        }
        return *this;
    }

    // Copy operator: transfers ownership of resources
    Dictionary &Dictionary::operator=(const Dictionary &other)
    {
        if (this != &other)
        {
            wordCount = other.wordCount;
            delete[] words;
            words = new Word[wordCount];

            for (size_t i = 0; i < wordCount; i++)
            {
                words[i] = other.words[i];
            }
        }
        return *this;
    }

    // Copy constructor
    Dictionary::Dictionary(const Dictionary &other)
        : wordCount(other.wordCount)
    {
        words = new Word[wordCount];
        for (size_t i = 0; i < wordCount; i++)
        {
            words[i] = other.words[i];
        }
    }

    PartOfSpeech parsePartOfSpeech(const std::string &posString)
    {
        if (posString == "n." || posString == "n. pl.")
            return PartOfSpeech::Noun;
        if (posString == "adv.")
            return PartOfSpeech::Adverb;
        if (posString == "a.")
            return PartOfSpeech::Adjective;
        if (posString == "v." || posString == "v. i." || posString == "v. t." || posString == "v. t. & i.")
            return PartOfSpeech::Verb;
        if (posString == "prep.")
            return PartOfSpeech::Preposition;
        if (posString == "pron.")
            return PartOfSpeech::Pronoun;
        if (posString == "conj.")
            return PartOfSpeech::Conjunction;
        if (posString == "interj.")
            return PartOfSpeech::Interjection;
        return PartOfSpeech::Unknown;
    }

    std::string partOfSpeechToString(PartOfSpeech pos)
    {
        if (pos == PartOfSpeech::Unknown)
            return "Unknown";
        else if (pos == PartOfSpeech::Noun)
            return "noun";
        else if (pos == PartOfSpeech::Pronoun)
            return "pronoun";
        else if (pos == PartOfSpeech::Adjective)
            return "adjective";
        else if (pos == PartOfSpeech::Adverb)
            return "adverb";
        else if (pos == PartOfSpeech::Verb)
            return "verb";
        else if (pos == PartOfSpeech::Preposition)
            return "preposition";
        else if (pos == PartOfSpeech::Conjunction)
            return "conjunction";
        else if (pos == PartOfSpeech::Interjection)
            return "interjection";
        else
            return "invalid";
    }

    Dictionary::Dictionary(const char *filename) : words(nullptr), wordCount(0)
    {
        std::ifstream file(filename);
        if (!file)
        {
            return;
        }

        std::string line;
        size_t lineCount = 0;

        // Count the number of lines in the file
        while (std::getline(file, line))
        {
            lineCount++;
        }

        // Allocate the array
        words = new Word[lineCount];

        file.clear();
        file.seekg(0, std::ios::beg);

        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string word, pos, definition;

            std::getline(iss, word, ',');
            std::getline(iss, pos, ',');
            std::getline(iss, definition);

            words[wordCount].m_word = word;
            words[wordCount].m_pos = parsePartOfSpeech(pos);
            words[wordCount].m_definition = definition;
            wordCount++;
        }

        file.close();
    }

    void Dictionary::searchWord(const char *word) const
    {
        bool wordFound = false;
        for (size_t i = 0; i < wordCount; i++)
        {
            if (words[i].m_word == word)
            {
                if (!wordFound)
                {
                    std::cout << words[i].m_word << " - ";
                    wordFound = true;
                }
                else
                {
                    std::cout << std::string(words[i].m_word.size(), ' ') << " - ";
                }

                if (g_settings.m_verbose && words[i].m_pos != PartOfSpeech::Unknown)
                {
                    std::cout << "(" << partOfSpeechToString(words[i].m_pos) << ") ";
                }

                std::cout << words[i].m_definition << std::endl;

                if (!g_settings.m_show_all)
                {
                    return;
                }
            }
        }

        if (!wordFound)
        {
            std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
        }
    }

}
