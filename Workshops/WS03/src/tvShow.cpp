#include "tvShow.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <iomanip>

namespace seneca
{
	TvShow::TvShow(unsigned int id, const std::string &title, unsigned short year, const std::string &summary)
		: MediaItem(title, summary, year), m_id(id) {}

	const unsigned int TvShow::getId() const { return m_id; }

	void TvShow::display(std::ostream &out) const
	{
		if (g_settings.m_tableView)
		{
			out << "S | " << std::left << std::setfill('.') << std::setw(50) << this->getTitle()
				<< " | " << std::right << std::setfill(' ') << std::setw(2) << this->m_episodes.size()
				<< " | " << std::setw(4) << this->getYear() << " | " << std::left;

			if (g_settings.m_maxSummaryWidth > -1)
			{
				if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
					out << this->getSummary();
				else
					out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
			}
			else
				out << this->getSummary();
			out << std::endl;
		}
		else
		{
			size_t pos = 0;
			out << this->getTitle() << " [" << this->getYear() << "]\n";
			out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
			while (pos < this->getSummary().size())
			{
				out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
				pos += g_settings.m_maxSummaryWidth;
			}
			for (auto &item : m_episodes)
			{
				out << std::setfill('0') << std::right;
				out << "    " << 'S' << std::setw(2) << item.m_season
					<< 'E' << std::setw(2) << item.m_numberInSeason << ' ';
				if (item.m_title != "")
					out << item.m_title << '\n';
				else
					out << "Episode " << item.m_numberOverall << '\n';

				pos = 0;
				while (pos < item.m_summary.size())
				{
					out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
					pos += g_settings.m_maxSummaryWidth - 8;
				}
			}
			out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
				<< std::setfill(' ') << '\n';
		}
	}

	TvShow *TvShow::createItem(const std::string &strShow)
	{
		if (strShow.empty() || strShow[0] == '#')
		{
			throw "Not a valid show.";
		}

		std::string tokens[4];
		size_t index = 0, start = 0, end = strShow.find(',');

		while (end != std::string::npos && index < 3)
		{
			std::string token = strShow.substr(start, end - start);
			MediaItem::trim(token);
			tokens[index++] = token;
			start = end + 1;
			end = strShow.find(',', start);
		}
		MediaItem::trim(tokens[index++] = strShow.substr(start));

		unsigned int id = static_cast<unsigned int>(std::stoi(tokens[0]));
		std::string title = tokens[1];
		unsigned short year = static_cast<unsigned short>(std::stoi(tokens[2]));
		std::string summary = tokens[3];

		return new TvShow(id, title, year, summary);
	}

	double TvShow::getEpisodeAverageLength() const
	{
		return m_episodes.empty() ? 0 : std::accumulate(m_episodes.begin(), m_episodes.end(), 0.0, [](double sum, const TvEpisode &ep)
														{ return sum + ep.m_length; }) /
											m_episodes.size();
	}

	std::list<std::string> TvShow::getLongEpisodes() const
	{
		std::list<std::string> longEpisodes;
		std::for_each(m_episodes.begin(), m_episodes.end(), [&](const TvEpisode &ep)
					  {
                          if (ep.m_length >= 3600)
                              longEpisodes.push_back(ep.m_title); });
		return longEpisodes;
	}
}
