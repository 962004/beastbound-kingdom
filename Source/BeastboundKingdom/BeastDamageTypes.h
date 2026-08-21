#pragma once
#include "CoreMinimal.h"
#include "BeastDamageTypes.generated.h"

USTRUCT(BlueprintType)
struct FBeastCombatResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly) float DamageApplied = 0.0f;
    UPROPERTY(BlueprintReadOnly) bool bTargetKilled = false;
    UPROPERTY(BlueprintReadOnly) int32 BeastPowerGained = 0;
};
