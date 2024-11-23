#include "spellChecker.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

namespace seneca
{
	SpellChecker::SpellChecker(const char *filename)
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

	void SpellChecker::operator()(std::string &text)
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

	void SpellChecker::showStatistics(std::ostream &out) const
	{
		out << "Spellchecker Statistics" << std::endl;
		for (int i = 0; i < SIZE; ++i)
		{
			out << std::left << std::setw(15) << m_badWords[i]
				<< ": " << m_replacements[i] << " replacements" << std::endl;
		}
	}
}
