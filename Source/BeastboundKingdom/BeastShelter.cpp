#include "BeastShelter.h"

ABeastShelter::ABeastShelter()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ABeastShelter::UpgradeShelter()
{
    ++ShelterLevel;
    ShelterHealth += HealthPerLevel;
}
