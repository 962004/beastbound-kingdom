#pragma once

#include "CoreMinimal.h"
#include "BeastPlayerProfile.generated.h"

USTRUCT(BlueprintType)
struct FBeastPlayerProfile
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, SaveGame)
    int32 Level = 1;

    UPROPERTY(BlueprintReadWrite, SaveGame)
    int32 BeastPower = 0;

    UPROPERTY(BlueprintReadWrite, SaveGame)
    int32 XP = 0;

    UPROPERTY(BlueprintReadWrite, SaveGame)
    int32 PerformanceScore = 0;

    UPROPERTY(BlueprintReadWrite, SaveGame)
    float BestSurvivalTime = 0.0f;

    UPROPERTY(BlueprintReadWrite, SaveGame)
    int32 BestBeastTier = 0;

    UPROPERTY(BlueprintReadWrite, SaveGame)
    int32 ShelterLevel = 1;

    UPROPERTY(BlueprintReadWrite, SaveGame)
    int32 TotalBeastsDefeated = 0;

    UPROPERTY(BlueprintReadWrite, SaveGame)
    int32 TotalDeaths = 0;
};
