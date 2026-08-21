#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BeastProgressionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBeastPowerChanged, int32, NewPower);

UCLASS(ClassGroup=(Beastbound), meta=(BlueprintSpawnableComponent))
class BEASTBOUNDKINGDOM_API UBeastProgressionComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UBeastProgressionComponent();

    UFUNCTION(BlueprintCallable, Category="Progression") void AddBeastPower(int32 Amount);
    UFUNCTION(BlueprintPure, Category="Progression") int32 GetBeastPower() const { return BeastPower; }
    UFUNCTION(BlueprintCallable, Category="Progression") void AddExperience(int32 Amount);
    UFUNCTION(BlueprintPure, Category="Progression") int32 GetLevel() const { return Level; }
    UFUNCTION(BlueprintPure, Category="Progression") int32 GetExperience() const { return Experience; }

    UPROPERTY(BlueprintAssignable, Category="Progression") FBeastPowerChanged OnBeastPowerChanged;

protected:
    UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category="Progression") int32 BeastPower = 0;
    UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category="Progression") int32 Experience = 0;
    UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite, Category="Progression") int32 Level = 1;
};
