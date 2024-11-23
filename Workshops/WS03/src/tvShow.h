#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include "mediaItem.h"
#include "settings.h"

namespace seneca
{
	class TvShow : public MediaItem
	{
	private:
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

		TvShow(unsigned int id, const std::string &title, unsigned short year, const std::string &summary);

	public:
		const unsigned int getId() const;

		void display(std::ostream &out) const override;

		static TvShow *createItem(const std::string &strShow);

		double getEpisodeAverageLength() const;

		std::list<std::string> getLongEpisodes() const;

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

			TvShow *show = nullptr;
			for (size_t i = 0; i < col.size(); ++i)
			{
				auto *item = col[i];
				if (auto *castedShow = dynamic_cast<TvShow *>(item); castedShow && castedShow->getId() == id)
				{
					show = castedShow;
					break;
				}
			}

			if (show)
			{
				TvEpisode episode{show, episodeNumber, season, numberInSeason, airDate, length, title, summary};
				show->m_episodes.push_back(episode);
			}
		}
	};
}

#endif // SENECA_TVSHOW_H
