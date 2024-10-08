#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <iostream>
#include <cstring>
#include "character.h"
#include <string>

namespace seneca
{
	class Guild
	{
	private:
		Character **m_members;
		size_t m_size;
		std::string m_name = "";

	public:
		Guild(const char *name);
		~Guild();
		Guild(const Guild &other);
		Guild &operator=(const Guild &other);
		Guild(Guild &&other);
		Guild &operator=(Guild &&other);

		void addMember(Character *c);
		void removeMember(const std::string &name);
		Character *operator[](size_t idx) const;
		void showMembers() const;
	};
}

#endif
