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
		std::string m_name;

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

	Guild::Guild(const char *name)
		: m_size(0)
	{
		m_members = nullptr;
		m_name = name;
	}

	Guild::~Guild()
	{
		delete[] m_members; // Free the array; members are not deleted
	}

	// Copy constructor
	Guild::Guild(const Guild &other)
		: m_size(other.m_size)
	{
		m_members = new Character *[m_size];
		for (size_t i = 0; i < m_size; i++)
		{
			m_members[i] = other.m_members[i];
		}
		m_name = other.m_name;
	}

	// Copy assignment operator
	Guild &Guild::operator=(const Guild &other)
	{
		if (this != &other)
		{
			for (size_t i = 0; i < m_size; i++)
			{
				delete m_members[i];
			}
			delete[] m_members;

			m_size = other.m_size;
			m_members = new Character *[other.m_size];
			for (size_t i = 0; i < m_size; i++)
			{
				m_members[i] = other.m_members[i];
			}
			m_name = other.m_name;
		}
		return *this;
	}

	// Move constructor
	Guild::Guild(Guild &&other)
		: m_members(other.m_members), m_size(other.m_size), m_name(other.m_name)
	{
		other.m_members = nullptr;
		other.m_size = 0;
		other.m_name = nullptr;
	}

	// Move assignment operator
	Guild &Guild::operator=(Guild &&other)
	{
		if (this != &other)
		{
			// Clean up current resources
			for (size_t i = 0; i < m_size; i++)
			{
				delete m_members[i];
			}
			delete[] m_members;

			// Move data from other
			m_members = other.m_members;
			m_size = other.m_size;
			m_name = other.m_name;

			other.m_members = nullptr;
			other.m_size = 0;
			other.m_name = nullptr;
		}
		return *this;
	}

	// Add a character to the team
	void Guild::addMember(Character *c)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			if (m_members[i]->getName() == c->getName())
			{
				return;
			}
		}

		Character **new_members = new Character *[m_size + 1]; // Allocate new array

		for (size_t i = 0; i < m_size; i++)
		{
			new_members[i] = m_members[i];
		}

		delete[] m_members;
		m_members = new_members;

		m_members[m_size++] = c;
	}

	// Remove a character by name
	void Guild::removeMember(const std::string &name)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			if (m_members[i]->getName() == name)
			{
				delete m_members[i];
				m_members[i] = m_members[m_size - 1];
				m_size--;
				return;
			}
		}
		std::cout << "Character " << name << " not found!" << std::endl;
	}

	Character *Guild::operator[](size_t idx) const
	{
		if (idx < m_size)
		{
			return m_members[idx];
		}
		return nullptr;
	}

	void Guild::showMembers() const
	{
		if (m_size == 0)
		{
			std::cout << "No team." << std::endl;
			return;
		}

		std::cout << "[" << m_name << "] TEAM" << std::endl;
		for (size_t i = 0; i < m_size; i++)
		{
			std::cout << (i + 1) << ": " << *(m_members[i]) << std::endl;
		}
	}
}

#endif
