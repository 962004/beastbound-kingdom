#include "BeastProgressionComponent.h"

UBeastProgressionComponent::UBeastProgressionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UBeastProgressionComponent::AddBeastPower(int32 Amount)
{
    if (Amount <= 0) return;
    BeastPower += Amount;
    OnBeastPowerChanged.Broadcast(BeastPower);
}

void UBeastProgressionComponent::AddExperience(int32 Amount)
{
    if (Amount <= 0) return;
    Experience += Amount;
    while (Experience >= Level * 100)
    {
        Experience -= Level * 100;
        ++Level;
    }
}
