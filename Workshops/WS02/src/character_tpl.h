#ifndef SENECA_CHARACTER_TPL_H
#define SENECA_CHARACTER_TPL_H
#include <iostream>
#include "character.h"
#include "health.h"

namespace seneca
{
	template <typename T>
	class CharacterTpl : public Character
	{

	private:
		int m_healthMax;
		T m_health;

	public:
		CharacterTpl(const char *name, int healthMax);

		void takeDamage(int dmg) override;
		int getHealth() const override;
		int getHealthMax() const override;
		void setHealthMax(int health) override;
		void setHealth(int health) override;
	};

	// Definitions

	template <typename T>
	CharacterTpl<T>::CharacterTpl(const char *name, int healthMax)
		: Character(name), m_healthMax(healthMax)
	{
		m_health = healthMax;
	}

	template <typename T>
	void CharacterTpl<T>::takeDamage(int dmg)
	{
		m_health -= dmg;

		if (!isAlive())
		{
			std::cout << getName() << " has been defeated!" << std::endl;
			return;
		}

		std::cout << getName() << " took " << dmg << " damage, " << getHealth() << " health remaining." << std::endl;
	}

	template <typename T>
	int CharacterTpl<T>::getHealth() const
	{
		return int(m_health);
	}

	template <typename T>
	int CharacterTpl<T>::getHealthMax() const
	{
		return m_healthMax;
	}

	template <typename T>
	void CharacterTpl<T>::setHealthMax(int health)
	{
		m_healthMax = health;
	}

	template <typename T>
	void CharacterTpl<T>::setHealth(int health)
	{
		m_health = health;
	}
}
#endif
