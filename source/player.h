#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "character.h"

class Item;

class Player: public Character {
	int boostAtk;
	int boostDef;
    double gold;
	bool hasBarrierSuit;
    bool hasCompass;

	int getBoostAtk() const override;
	int getBoostDef() const override;
    
public:
	Player(int HP, int Atk, int Def);
	virtual ~Player();

	void addHP(int hp);
	void addAtk(int atk);
	void addDef(int def);
	virtual void addGold(double g) override;
    // this method is called each time player upstairs
    // resets temporary potion effects and compass
	void reset();
	void equipBarrierSuit();
    void equipCompass();
    bool ownCompass() const;
	bool isMovable(const Cell &c) const override;
    
    double getGold() const;
	virtual double getScore() const;
	virtual bool attack(Character &c) override;
	virtual void defense(Character &c) override;
    
    virtual std::string getRace() const = 0;
    
    bool isGeneratable(const Normal &t) const override;
    bool isGeneratable(const SmallHorde &t) const override;
};


#endif
