#include <iostream>
#include <cstring>
#include "character.h"
#include "team.h"
#include <string>

namespace seneca
{

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
		other.m_name = "";
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
			other.m_name = "";
		}
		return *this;
	}

	// Add a character to the team
	void Team::addMember(Character *c)
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
		size_t indexToRemove = m_size;
		for (size_t i = 0; i < m_size; i++)
		{
			if (m_members[i]->getName() == name)
			{
				indexToRemove = i;
				break;
			}
		}

		if (indexToRemove == m_size)
		{
			return;
		}

		delete m_members[indexToRemove];

		for (size_t i = indexToRemove; i < m_size - 1; i++)
		{
			m_members[i] = m_members[i + 1];
		}

		m_members[m_size - 1] = nullptr;

		m_size--;
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
		if (m_name == "")
		{
			std::cout << "No team." << std::endl;
			return;
		}

		std::cout << "[Team] " << m_name << std::endl;
		for (size_t i = 0; i < m_size; i++)
		{
			std::cout << "    " << (i + 1) << ": " << *(m_members[i]) << std::endl;
		}
	}
}