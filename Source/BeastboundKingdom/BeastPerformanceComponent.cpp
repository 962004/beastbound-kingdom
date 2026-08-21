#include "BeastPerformanceComponent.h"

UBeastPerformanceComponent::UBeastPerformanceComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UBeastPerformanceComponent::AddBeastKill(int32 BeastTier, int32 BaseXP)
{
    const int32 SafeTier = FMath::Max(1, BeastTier);
    Profile.BeastPower += 1;
    Profile.TotalBeastsDefeated += 1;
    Profile.BestBeastTier = FMath::Max(Profile.BestBeastTier, SafeTier);
    Profile.XP += FMath::Max(1, BaseXP) * SafeTier;
    RecalculateLevel();
}

void UBeastPerformanceComponent::RecordDeath()
{
    Profile.TotalDeaths += 1;
    RecalculateLevel();
}

void UBeastPerformanceComponent::RecordShelterUpgrade()
{
    Profile.ShelterLevel += 1;
    RecalculateLevel();
}

int32 UBeastPerformanceComponent::CalculatePerformanceScore() const
{
    const int32 KillScore = Profile.TotalBeastsDefeated * 100;
    const int32 PowerScore = Profile.BeastPower * 50;
    const int32 TierScore = Profile.BestBeastTier * 250;
    const int32 ShelterScore = Profile.ShelterLevel * 100;
    const int32 DeathPenalty = Profile.TotalDeaths * 50;
    return FMath::Max(0, KillScore + PowerScore + TierScore + ShelterScore - DeathPenalty);
}

void UBeastPerformanceComponent::RecalculateLevel()
{
    Profile.PerformanceScore = CalculatePerformanceScore();
    Profile.Level = FMath::Max(1, 1 + Profile.XP / 100);
}
