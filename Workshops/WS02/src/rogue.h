#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include <iostream>
#include "character_tpl.h"
#include "weapons.h"

namespace seneca
{
	template <typename T, typename FirstAbility_t, typename SecondAbility_t>
	class Rogue : public CharacterTpl<T>
	{
	private:
		int m_baseDefense;
		int m_baseAttack;
		FirstAbility_t m_firstAbility;
		SecondAbility_t m_secondAbility;
		seneca::Dagger m_weapon;

	public:
		Rogue(const char *name, int healthMax, int baseAttack, int baseDefense);

		int getAttackAmnt() const override;
		int getDefenseAmnt() const override;
		Character *clone() const override;
		void attack(Character *enemy) override;
		void takeDamage(int dmg) override;
	};

	template <typename T, typename FirstAbility_t, typename SecondAbility_t>
	Rogue<T, FirstAbility_t, SecondAbility_t>::Rogue(const char *name, int healthMax, int baseAttack, int baseDefense)
		: CharacterTpl<T>(name, healthMax),
		  m_baseDefense(baseDefense),
		  m_baseAttack(baseAttack) {}

	template <typename T, typename FirstAbility_t, typename SecondAbility_t>
	int Rogue<T, FirstAbility_t, SecondAbility_t>::getAttackAmnt() const
	{
		return m_baseAttack + (2 * static_cast<double>(m_weapon));
	}

	template <typename T, typename FirstAbility_t, typename SecondAbility_t>
	int Rogue<T, FirstAbility_t, SecondAbility_t>::getDefenseAmnt() const
	{
		return m_baseDefense;
	}

	template <typename T, typename FirstAbility_t, typename SecondAbility_t>
	Character *Rogue<T, FirstAbility_t, SecondAbility_t>::clone() const
	{
		return new Rogue<T, FirstAbility_t, SecondAbility_t>(*this);
	}

	template <typename T, typename FirstAbility_t, typename SecondAbility_t>
	void Rogue<T, FirstAbility_t, SecondAbility_t>::attack(Character *enemy)
	{
		std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

		m_firstAbility.useAbility(this);
		m_secondAbility.useAbility(this);

		int damage = this->getAttackAmnt();

		m_firstAbility.transformDamageDealt(damage);
		m_secondAbility.transformDamageDealt(damage);

		std::cout << "Rogue deals " << damage << " melee damage!" << std::endl;

		enemy->takeDamage(damage);
	}

	template <typename T, typename FirstAbility_t, typename SecondAbility_t>
	void Rogue<T, FirstAbility_t, SecondAbility_t>::takeDamage(int dmg)
	{
		std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;

		std::cout << "Rogue has a defense of " << this->getDefenseAmnt() << ". Reducing damage received." << std::endl;
		dmg -= this->getDefenseAmnt();

		if (dmg < 0)
		{
			dmg = 0;
		}

		m_firstAbility.transformDamageReceived(dmg);
		m_secondAbility.transformDamageReceived(dmg);

		CharacterTpl<T>::takeDamage(dmg);
	}
}
#endif
