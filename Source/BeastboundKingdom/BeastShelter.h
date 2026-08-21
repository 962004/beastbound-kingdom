#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeastShelter.generated.h"

UCLASS()
class BEASTBOUNDKINGDOM_API ABeastShelter : public AActor
{
    GENERATED_BODY()

public:
    ABeastShelter();

    UFUNCTION(BlueprintCallable, Category="Shelter")
    void UpgradeShelter();

    UFUNCTION(BlueprintPure, Category="Shelter")
    int32 GetShelterLevel() const { return ShelterLevel; }

    UFUNCTION(BlueprintPure, Category="Shelter")
    float GetShelterHealth() const { return ShelterHealth; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Shelter")
    int32 ShelterLevel = 1;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Shelter")
    float ShelterHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shelter")
    float HealthPerLevel = 100.0f;
};
