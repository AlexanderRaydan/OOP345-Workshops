#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>

namespace seneca
{

	class SpellChecker
	{
		static const int SIZE = 6;
		std::string m_badWords[SIZE];
		std::string m_goodWords[SIZE];
		int m_replacements[SIZE] = {0};

	public:
		SpellChecker(const char *filename)
		{
			std::ifstream file(filename);
			if (!file)
			{
				throw "Bad file name!";
			}

			std::string line;
			int index = 0;
			while (std::getline(file, line) && index < SIZE)
			{
				std::istringstream iss(line);
				iss >> m_badWords[index] >> m_goodWords[index];
				++index;
			}

			if (index < SIZE)
			{
				throw std::runtime_error("Insufficient data in file.");
			}
		}

		void operator()(std::string &text)
		{
			for (int i = 0; i < SIZE; ++i)
			{
				size_t pos = 0;
				while ((pos = text.find(m_badWords[i], pos)) != std::string::npos)
				{
					text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
					++m_replacements[i];
					pos += m_goodWords[i].length();
				}
			}
		}

		void showStatistics(std::ostream &out) const
		{
			out << "Spellchecker Statistics" << std::endl;
			for (int i = 0; i < SIZE; ++i)
			{
				out << std::left << std::setw(15) << m_badWords[i]
					<< ": " << m_replacements[i] << " replacements" << std::endl;
			}
		}
	};
}

#endif
