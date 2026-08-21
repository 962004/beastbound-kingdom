#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BeastPlayerCharacter.generated.h"

UCLASS()
class BEASTBOUNDKINGDOM_API ABeastPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ABeastPlayerCharacter();

    UFUNCTION(BlueprintCallable, Category="Beastbound|Combat")
    void PerformAxeAttack();

    UFUNCTION(BlueprintPure, Category="Beastbound|Progression")
    int32 GetBeastPower() const { return BeastPower; }

    UFUNCTION(BlueprintCallable, Category="Beastbound|Progression")
    void AddBeastPower(int32 Amount = 1);

    UFUNCTION(BlueprintPure, Category="Beastbound|Stats")
    float GetHealth() const { return Health; }

    UFUNCTION(BlueprintCallable, Category="Beastbound|Stats")
    void ReceiveDamage(float Amount);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beastbound|Stats")
    float MaxHealth = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Beastbound|Stats")
    float Health = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Beastbound|Progression")
    int32 BeastPower = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beastbound|Combat")
    float AxeDamage = 25.0f;
};
