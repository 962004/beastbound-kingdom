#include "BeastShelter.h"

ABeastShelter::ABeastShelter()
{
    PrimaryActorTick.bCanEverTick = false;
}

bool ABeastShelter::UpgradeShelter()
{
    if (ShelterHealth <= 0.0f) return false;
    ++ShelterLevel;
    ShelterHealth = ShelterLevel * HealthPerLevel;
    OnLevelChanged.Broadcast(ShelterLevel);
    return true;
}

void ABeastShelter::Repair(float Amount)
{
    ShelterHealth = FMath::Clamp(ShelterHealth + FMath::Max(0.0f, Amount), 0.0f, ShelterLevel * HealthPerLevel);
}

void ABeastShelter::DamageShelter(float Amount)
{
    ShelterHealth = FMath::Clamp(ShelterHealth - FMath::Max(0.0f, Amount), 0.0f, ShelterLevel * HealthPerLevel);
}
