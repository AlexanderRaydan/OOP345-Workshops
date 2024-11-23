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
		Movie(const std::string &title, unsigned short year, const std::string &summary);

	public:
		void display(std::ostream &out) const override;

		static Movie *createItem(const std::string &strMovie);
	};
}

#endif // SENECA_MOVIE_H
