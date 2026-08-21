#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BeastPlayerProfile.h"
#include "BeastPerformanceComponent.generated.h"

UCLASS(ClassGroup=(Beastbound), Blueprintable, meta=(BlueprintSpawnableComponent))
class BEASTBOUNDKINGDOM_API UBeastPerformanceComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBeastPerformanceComponent();

    UPROPERTY(BlueprintReadOnly, Category="Performance")
    FBeastPlayerProfile Profile;

    UFUNCTION(BlueprintCallable, Category="Performance")
    void AddBeastKill(int32 BeastTier, int32 BaseXP = 10);

    UFUNCTION(BlueprintCallable, Category="Performance")
    void RecordDeath();

    UFUNCTION(BlueprintCallable, Category="Performance")
    void RecordShelterUpgrade();

    UFUNCTION(BlueprintPure, Category="Performance")
    int32 CalculatePerformanceScore() const;

private:
    void RecalculateLevel();
};
