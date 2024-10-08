#include <iostream>
#include <cstring>
#include "character.h"
#include "guild.h"
#include <string>

namespace seneca
{
	Guild::Guild(const char *name)
		: m_size(0)
	{
		m_members = nullptr;
		m_name = name;
	}

	Guild::~Guild()
	{
		delete[] m_members;
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
		for (size_t i = 0; i < m_size; i++)
		{
			m_members[i] = other.m_members[i];
		}

		other.m_members = nullptr;
		other.m_size = 0;
		other.m_name = "";
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
			other.m_name = "";
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

		Character **new_members = new Character *[m_size + 1];

		for (size_t i = 0; i < m_size; i++)
		{
			new_members[i] = m_members[i];
		}

		delete[] m_members;
		m_members = new_members;

		int maxHealth = c->getHealthMax();
		c->setHealthMax(maxHealth + 300);
		c->setHealth(c->getHealthMax());

		m_members[m_size++] = c;
	}

	// Remove a character by name
	void Guild::removeMember(const std::string &name)
	{
		size_t indexToRemove = m_size;
		for (size_t i = 0; i < m_size; i++)
		{
			if (m_members[i]->getName() == name)
			{

				int maxHealth = m_members[i]->getHealthMax();
				int health = m_members[i]->getHealth();

				m_members[i]->setHealthMax(maxHealth - 300);
				m_members[i]->setHealth(health - 300);

				indexToRemove = i; // Found the index to remove
				break;
			}
		}

		if (indexToRemove == m_size)
		{
			return;
		}

		m_members[indexToRemove] = nullptr;

		for (size_t i = indexToRemove; i < m_size - 1; i++)
		{
			m_members[i] = m_members[i + 1];
		}

		m_members[m_size - 1] = nullptr;

		m_size--;
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
		if (m_name == "")
		{
			std::cout << "No guild." << std::endl;
			return;
		}

		std::cout << "[Guild] " << m_name << std::endl;
		for (size_t i = 0; i < m_size; i++)
		{
			std::cout << "    " << (i + 1) << ": " << *(m_members[i]) << std::endl;
		}
	}
}