// Copyright Spruce Hill, All rights reserved.

#pragma once

/**
 * 
 */
class GALDRAR_API BaseBloodVial
{
public:
	BaseBloodVial();
	BaseBloodVial(UCharacterStatsComponent* stats);
	~BaseBloodVial();

	virtual void Activate();

	int32 GetMaxCharges() { return maxCharges; }
	int32 GetCharges() { return charges; }
	int32 GetID() { return ID; };

	void AddCharges(int32 nbrOfCharges)
	{
		if (charges + nbrOfCharges >= maxCharges)
		{
			charges = maxCharges;
		}
		else
		{
			charges += nbrOfCharges;
		}
	}

protected:
	int32 ID;
	
	// Number of charges that can be spent
	int32 maxCharges;
	// Current amount
	int32 charges;

	UCharacterStatsComponent* stats;
};
