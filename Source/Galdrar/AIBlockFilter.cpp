// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "AIBlockFilter.h"
#include "AIDeterrentArea.h"

UAIBlockFilter::UAIBlockFilter()
{
	AddExcludedArea(UAIDeterrentArea::StaticClass());
}

