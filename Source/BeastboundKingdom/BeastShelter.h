#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeastShelter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShelterLevelChanged, int32, NewLevel);

UCLASS()
class BEASTBOUNDKINGDOM_API ABeastShelter : public AActor
{
    GENERATED_BODY()
public:
    ABeastShelter();
    UFUNCTION(BlueprintCallable, Category="Shelter") bool UpgradeShelter();
    UFUNCTION(BlueprintCallable, Category="Shelter") void Repair(float Amount);
    UFUNCTION(BlueprintCallable, Category="Shelter") void DamageShelter(float Amount);
    UFUNCTION(BlueprintPure, Category="Shelter") int32 GetShelterLevel() const { return ShelterLevel; }
    UFUNCTION(BlueprintPure, Category="Shelter") float GetShelterHealth() const { return ShelterHealth; }
    UPROPERTY(BlueprintAssignable, Category="Shelter") FShelterLevelChanged OnLevelChanged;
protected:
    UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadOnly, Category="Shelter") int32 ShelterLevel = 1;
    UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category="Shelter") float ShelterHealth = 100.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shelter") float HealthPerLevel = 100.0f;
};
