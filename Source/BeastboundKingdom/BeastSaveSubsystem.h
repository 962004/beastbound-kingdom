#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BeastGameSave.h"
#include "BeastSaveSubsystem.generated.h"

UCLASS()
class BEASTBOUNDKINGDOM_API UBeastSaveSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Save") void SavePlayer(const UBeastGameSave* State);
    UFUNCTION(BlueprintCallable, Category="Save") UBeastGameSave* LoadPlayer() const;
    UFUNCTION(BlueprintCallable, Category="Save") void ClearPlayerSave();
    UFUNCTION(BlueprintPure, Category="Save") FString GetSaveSlot() const { return TEXT("BeastboundPlayer"); }
};
