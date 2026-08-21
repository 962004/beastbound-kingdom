#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BeastGameSave.generated.h"

UCLASS()
class BEASTBOUNDKINGDOM_API UBeastGameSave : public USaveGame
{
    GENERATED_BODY()
public:
    UPROPERTY(SaveGame, BlueprintReadWrite) FString PlayerName;
    UPROPERTY(SaveGame, BlueprintReadWrite) int32 Level = 1;
    UPROPERTY(SaveGame, BlueprintReadWrite) int32 Experience = 0;
    UPROPERTY(SaveGame, BlueprintReadWrite) int32 BeastPower = 0;
    UPROPERTY(SaveGame, BlueprintReadWrite) int32 BeastsDefeated = 0;
    UPROPERTY(SaveGame, BlueprintReadWrite) int32 Deaths = 0;
    UPROPERTY(SaveGame, BlueprintReadWrite) int32 StrongestBeastTier = 0;
    UPROPERTY(SaveGame, BlueprintReadWrite) int32 ShelterLevel = 1;
    UPROPERTY(SaveGame, BlueprintReadWrite) int32 KingdomPopulation = 1;
    UPROPERTY(SaveGame, BlueprintReadWrite) float BestSurvivalSeconds = 0.0f;
    UPROPERTY(SaveGame, BlueprintReadWrite) int64 PerformanceScore = 0;
};
