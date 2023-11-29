#ifndef ABILITYCARD_H
#define ABILITYCARD_H

class AbilityCard {
    bool usedAbility;
    int abilityID;
    public:
    virtual bool isUsed() = 0;
    virtual int getAbilityId() = 0;
    virtual void activate() = 0; // TO DO: implement all the activate() functions for diff cards
};

#endif

