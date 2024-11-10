#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include "mediaItem.h"
#include "settings.h"
#include <iomanip>
#include <stdexcept>
#include <sstream>

namespace seneca
{
	class Movie : public MediaItem
	{
	private:
		Movie(const std::string &title, unsigned short year, const std::string &summary)
			: MediaItem(title, summary, year) {}

	public:
		void display(std::ostream &out) const override
		{
			if (g_settings.m_tableView)
			{
				out << "M | ";
				out << std::left << std::setfill('.');
				out << std::setw(50) << getTitle() << " | ";
				out << std::right << std::setfill(' ');
				out << std::setw(9) << getYear() << " | ";
				out << std::left;

				if (g_settings.m_maxSummaryWidth > -1)
				{
					if (static_cast<short>(getSummary().size()) <= g_settings.m_maxSummaryWidth)
						out << getSummary();
					else
						out << getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
				}
				else
				{
					out << getSummary();
				}
				out << std::endl;
			}
			else
			{
				size_t pos = 0;
				out << getTitle() << " [" << getYear() << "]\n";
				out << std::setw(getTitle().size() + 7) << std::setfill('-') << "" << '\n';
				while (pos < getSummary().size())
				{
					out << "    " << getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
					pos += g_settings.m_maxSummaryWidth;
				}
				out << std::setw(getTitle().size() + 7) << std::setfill('-') << ""
					<< std::setfill(' ') << '\n';
			}
		}

		static Movie *createItem(const std::string &strMovie)
		{
			if (strMovie.empty() || strMovie[0] == '#')
			{
				throw "Not a valid movie.";
			}

			std::string tokens[3];
			size_t index = 0;
			size_t start = 0;
			size_t end = strMovie.find(',');

			while (end != std::string::npos && index < 2)
			{
				std::string token = strMovie.substr(start, end - start);
				MediaItem::trim(token);
				tokens[index++] = token;

				start = end + 1;
				end = strMovie.find(',', start);
			}

			std::string token = strMovie.substr(start);
			MediaItem::trim(token);
			tokens[index] = token;

			std::string title = tokens[0];
			unsigned short year = static_cast<unsigned short>(std::stoi(tokens[1]));
			std::string summary = tokens[2];

			return new Movie(title, year, summary);
		}
	};
}

#endif
