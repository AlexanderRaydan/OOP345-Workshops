#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include <iostream>
#include "character_tpl.h"
#include "health.h"

namespace seneca
{
	template <typename Weapon_t>
	class Archer : public CharacterTpl<seneca::SuperHealth>
	{
	private:
		int m_baseDefense;
		int m_baseAttack;
		Weapon_t m_weapon;

	public:
		Archer(const char *name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon);

		int getAttackAmnt() const override;
		int getDefenseAmnt() const override;
		Character *clone() const override;
		void attack(Character *enemy) override;
		void takeDamage(int dmg) override;
	};

	template <typename Weapon_t>
	Archer<Weapon_t>::Archer(const char *name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
		: CharacterTpl<seneca::SuperHealth>(name, healthMax),
		  m_baseDefense(baseDefense),
		  m_baseAttack(baseAttack),
		  m_weapon(weapon) {}

	template <typename Weapon_t>
	int Archer<Weapon_t>::getAttackAmnt() const
	{
		return static_cast<int>(1.3 * m_baseAttack); // Calculate attack amount
	}

	template <typename Weapon_t>
	int Archer<Weapon_t>::getDefenseAmnt() const
	{
		return static_cast<int>(1.2 * m_baseDefense); // Calculate defense amount
	}

	template <typename Weapon_t>
	Character *Archer<Weapon_t>::clone() const
	{
		return new Archer<Weapon_t>(*this); // Create a copy of the current instance
	}

	template <typename Weapon_t>
	void Archer<Weapon_t>::attack(Character *enemy)
	{
		std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

		int damage = this->getAttackAmnt(); // Get calculated damage

		std::cout << "    Archer deals " << damage << " ranged damage!" << std::endl;

		enemy->takeDamage(damage); // Apply damage to the enemy
	}

	template <typename Weapon_t>
	void Archer<Weapon_t>::takeDamage(int dmg)
	{
		std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;

		std::cout << "    Archer has a defense of " << this->getDefenseAmnt() << ". Reducing damage received." << std::endl;
		dmg -= this->getDefenseAmnt(); // Reduce damage by defense

		if (dmg < 0)
		{
			dmg = 0; // Ensure damage does not go below zero
		}

		CharacterTpl<seneca::SuperHealth>::takeDamage(dmg); // Call base class takeDamage
	}
}
#endif
