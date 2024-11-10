#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <iostream>
#include <string>
#include <iomanip>
#include "mediaItem.h"
#include "settings.h"
namespace seneca
{

	class Book : public MediaItem
	{

	private:
		std::string m_author;
		std::string m_country;
		double m_price;

		Book(const std::string &author, const std::string &title, const std::string &country,
			 double price, unsigned short year, const std::string &summary)
			: MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) {}

	public:
		void display(std::ostream &out) const override
		{
			if (g_settings.m_tableView)
			{
				out << "B | ";
				out << std::left << std::setfill('.');
				out << std::setw(50) << this->getTitle() << " | ";
				out << std::right << std::setfill(' ');
				out << std::setw(2) << this->m_country << " | ";
				out << std::setw(4) << this->getYear() << " | ";
				out << std::left;
				if (g_settings.m_maxSummaryWidth > -1)
				{
					if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
						out << this->getSummary();
					else
						out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
				}
				else
				{
					out << this->getSummary();
				}
				out << std::endl;
			}
			else
			{
				size_t pos = 0;
				out << this->getTitle() << " [" << this->getYear() << "] [";
				out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
				out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
				while (pos < this->getSummary().size())
				{
					out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
					pos += g_settings.m_maxSummaryWidth;
				}
				out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
					<< std::setfill(' ') << '\n';
			}
		}

		static Book *createItem(const std::string &strBook)
		{
			if (strBook.empty() || strBook[0] == '#')
				throw "Not a valid book.";

			std::string tokens[6];
			size_t index = 0;
			size_t start = 0;
			size_t end = strBook.find(',');

			while (end != std::string::npos)
			{
				std::string token = strBook.substr(start, end - start);
				MediaItem::trim(token);

				tokens[index++] = token;

				start = end + 1;

				if (index == 5)
				{
					end = strBook.length();
					continue;
				}

				end = strBook.find(',', start);
			}

			std::string author = tokens[0];
			std::string title = tokens[1];
			std::string country = tokens[2];
			double price = std::stod(tokens[3]);
			unsigned short year = static_cast<unsigned short>(std::stoi(tokens[4]));
			std::string summary = tokens[5];

			return new Book(author, title, country, price, year, summary);
		}
	};
}

#endif
