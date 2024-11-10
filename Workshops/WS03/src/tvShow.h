#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <sstream>
#include <stdio.h>

#include "mediaItem.h"
#include "settings.h"

namespace seneca
{

	class TvShow : public MediaItem
	{

		struct TvEpisode
		{
			const TvShow *m_show{};
			unsigned short m_numberOverall{};
			unsigned short m_season{};
			unsigned short m_numberInSeason{};
			std::string m_airDate{};
			unsigned int m_length{};
			std::string m_title{};
			std::string m_summary{};
		};

		unsigned int m_id{};
		std::list<TvEpisode> m_episodes;

		TvShow(unsigned int id, const std::string &title, unsigned short year, const std::string &summary)
			: MediaItem(title, summary, year), m_id(id) {}

	public:
		const unsigned int getId() const { return m_id; }

		// Display function override
		void display(std::ostream &out) const override
		{
			// Implementation as described in the question
			if (g_settings.m_tableView)
			{
				out << "S | ";
				out << std::left << std::setfill('.');
				out << std::setw(50) << this->getTitle() << " | ";
				out << std::right << std::setfill(' ');
				out << std::setw(2) << this->m_episodes.size() << " | ";
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

		// Class function to create a TvShow from CSV
		static TvShow *createItem(const std::string &strShow)
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

		template <typename Collection_t>
		static void addEpisode(Collection_t &col, const std::string &strEpisode)
		{
			if (strEpisode.empty() || strEpisode[0] == '#')
			{
				throw "Not a valid episode.";
			}

			std::string tokens[8];
			size_t index = 0, start = 0, end = strEpisode.find(',');

			while (end != std::string::npos && index < 7)
			{
				std::string token = strEpisode.substr(start, end - start);
				MediaItem::trim(token);
				tokens[index++] = token;
				start = end + 1;
				end = strEpisode.find(',', start);
			}
			MediaItem::trim(tokens[index++] = strEpisode.substr(start));

			unsigned int id = static_cast<unsigned int>(std::stoi(tokens[0]));
			unsigned short episodeNumber = static_cast<unsigned short>(std::stoi(tokens[1]));
			unsigned short season = tokens[2].empty() ? 1 : static_cast<unsigned short>(std::stoi(tokens[2]));
			unsigned short numberInSeason = static_cast<unsigned short>(std::stoi(tokens[3]));
			std::string airDate = tokens[4];

			int hours = 0, minutes = 0, seconds = 0;
			sscanf(tokens[5].c_str(), "%2d:%2d:%2d", &hours, &minutes, &seconds);

			unsigned int length = hours * 3600 + minutes * 60 + seconds;

			std::string title = tokens[6];
			std::string summary = tokens[7];

			auto it = std::find_if(col.begin(), col.end(),
								   [id](auto *item)
								   {
									   auto *show = dynamic_cast<TvShow *>(item);
									   return show && show->getId() == id;
								   });

			if (it != col.end())
			{
				auto *show = dynamic_cast<TvShow *>(*it);
				TvEpisode episode{show, episodeNumber, season, numberInSeason, airDate, length, title, summary};
				show->m_episodes.push_back(episode);
			}
		}

		double getEpisodeAverageLength() const
		{
			return m_episodes.empty() ? 0 : std::accumulate(m_episodes.begin(), m_episodes.end(), 0.0, [](double sum, const TvEpisode &ep)
															{ return sum + ep.m_length; }) /
												m_episodes.size();
		}

		std::list<std::string> getLongEpisodes() const
		{
			std::list<std::string> longEpisodes;
			std::for_each(m_episodes.begin(), m_episodes.end(), [&](const TvEpisode &ep)
						  {
            if (ep.m_length >= 3600) longEpisodes.push_back(ep.m_title); });
			return longEpisodes;
		}
	};
}

#endif