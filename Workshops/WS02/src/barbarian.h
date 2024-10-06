#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include <iostream>
#include "character_tpl.h"

namespace seneca
{
	template <typename T, typename Ability_t, typename Weapon_t>
	class Barbarian : public CharacterTpl<T>
	{

	private:
		int m_baseDefense;
		int m_baseAttack;
		Ability_t m_ability;
		Weapon_t m_weapon[2];
		T m_health;

	public:
		Barbarian(
			const char *name,
			int healthMax,
			int baseAttack,
			int baseDefense,
			Weapon_t primaryWeapon,
			Weapon_t secondaryWeapon);

		int getAttackAmnt() const override;
		int getDefenseAmnt() const override;
		Character *clone() const override;
		void attack(Character *enemy) override;
		void takeDamage(int dmg) override;
	};

	// Definitions
	template <typename T, typename Ability_t, typename Weapon_t>
	Barbarian<T, Ability_t, Weapon_t>::Barbarian(
		const char *name,
		int healthMax,
		int baseAttack,
		int baseDefense,
		Weapon_t primaryWeapon,
		Weapon_t secondaryWeapon)
		: CharacterTpl<T>(name, healthMax),
		  m_baseDefense(baseDefense),
		  m_baseAttack(baseAttack)
	{
		m_weapon[0] = primaryWeapon;
		m_weapon[1] = secondaryWeapon;
	};

	template <typename T, typename Ability_t, typename Weapon_t>
	int Barbarian<T, Ability_t, Weapon_t>::getAttackAmnt() const
	{
		return int(m_baseAttack + ((double(m_weapon[0]) + double(m_weapon[1])) / 2));
	}

	template <typename T, typename Ability_t, typename Weapon_t>
	int Barbarian<T, Ability_t, Weapon_t>::getDefenseAmnt() const
	{
		return m_baseDefense;
	}

	template <typename T, typename Ability_t, typename Weapon_t>
	Character *Barbarian<T, Ability_t, Weapon_t>::clone() const
	{
		return new Barbarian<T, Ability_t, Weapon_t>(*this);
	}

	template <typename T, typename Ability_t, typename Weapon_t>
	void Barbarian<T, Ability_t, Weapon_t>::attack(Character *enemy)
	{
		std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

		m_ability.useAbility(this);

		int damage = this->getAttackAmnt();

		m_ability.transformDamageDealt(damage);

		std::cout << "Barbarian deals " << damage << " melee damage!" << std::endl;

		enemy->takeDamage(damage);
	}

	template <typename T, typename Ability_t, typename Weapon_t>
	void Barbarian<T, Ability_t, Weapon_t>::takeDamage(int dmg)
	{

		std::cout << this->getName() << " is attacked for " << dmg << "." << std::endl;

		std::cout << "Barbarian has a defense of " << m_baseDefense << "Reducing damage received." << std::endl;

		dmg -= m_baseDefense;

		if (dmg < 0)
		{
			dmg = 0;
		}

		m_ability.transformDamageReceived(dmg);
		CharacterTpl<T>::takeDamage(dmg);
	}

}
#endif
