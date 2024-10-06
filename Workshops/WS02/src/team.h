#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <iostream>
#include <cstring>
#include "character.h"
#include <string>

namespace seneca
{
	class Team
	{
	private:
		Character **m_members;
		size_t m_size;
		std::string m_name;

	public:
		Team(const char *name);
		~Team();
		Team(const Team &other);
		Team &operator=(const Team &other);
		Team(Team &&other);
		Team &operator=(Team &&other);

		void addMember(const Character *c);
		void removeMember(const std::string &name);
		Character *operator[](size_t idx) const;
		void showMembers() const;
	};

	Team::Team(const char *name)
		: m_size(0)
	{
		m_members = nullptr;
		m_name = name;
	}

	Team::~Team()
	{
		for (size_t i = 0; i < m_size; i++)
		{
			delete m_members[i];
		}
		delete[] m_members;
	}

	// Copy constructor
	Team::Team(const Team &other)
		: m_size(other.m_size)
	{
		m_members = new Character *[m_size];
		for (size_t i = 0; i < m_size; i++)
		{
			m_members[i] = other.m_members[i]->clone();
		}
		m_name = other.m_name;
	}

	// Copy assignment operator
	Team &Team::operator=(const Team &other)
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
				m_members[i] = other.m_members[i]->clone();
			}
			m_name = other.m_name;
		}
		return *this;
	}

	// Move constructor
	Team::Team(Team &&other)
		: m_members(other.m_members), m_size(other.m_size), m_name(other.m_name)
	{
		other.m_members = nullptr;
		other.m_size = 0;
		other.m_name = nullptr;
	}

	// Move assignment operator
	Team &Team::operator=(Team &&other)
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
	void Team::addMember(const Character *c)
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

		m_members[m_size++] = c->clone();
	}

	// Remove a character by name
	void Team::removeMember(const std::string &name)
	{

		// acá hay un peo
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

	Character *Team::operator[](size_t idx) const
	{
		if (idx < m_size)
		{
			return m_members[idx];
		}
		return nullptr;
	}

	void Team::showMembers() const
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
