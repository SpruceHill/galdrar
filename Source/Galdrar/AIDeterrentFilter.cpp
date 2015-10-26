// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "AIDeterrentFilter.h"
#include "AIDeterrentArea.h"

UAIDeterrentFilter::UAIDeterrentFilter()
{
	this->AddEnteringCostOverride(UAIDeterrentArea::StaticClass(), 10000.f);
}
