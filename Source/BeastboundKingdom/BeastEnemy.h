#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BeastEnemy.generated.h"

UCLASS()
class BEASTBOUNDKINGDOM_API ABeastEnemy : public ACharacter
{
    GENERATED_BODY()

public:
    ABeastEnemy();

    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beast")
    float MaxHealth = 50.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Beast")
    float Health = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beast")
    float AttackDamage = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beast")
    int32 BeastPowerReward = 1;
};
