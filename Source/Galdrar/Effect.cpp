// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Effect.h"

Effect::Effect(CharacterStats* stats)
{
	this->stats = stats;
	duration = 5.f;
	timeLeft = 5.f;
	damageType = DamageType::PHYSICAL;
}
void Effect::Tick(float delta)
{
	time += delta;
	if (time > 5)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "ASDASD");
		timeLeft -= 0.5f;
		stats->health -= 1.f;
		//oldTime = time;
	}
	/*
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(time));
	if (time > 0.5f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "ASDASD");
		timeLeft -= 0.5f;
		time -= 0.5f;
		stats->health -= 10.f;
	}*/
}