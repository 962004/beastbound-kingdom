#include "BeastEnemy.h"
#include "BeastPlayerCharacter.h"

ABeastEnemy::ABeastEnemy()
{
    PrimaryActorTick.bCanEverTick = false;
    Health = MaxHealth;
}

float ABeastEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    const float AppliedDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    Health = FMath::Clamp(Health - FMath::Max(0.0f, AppliedDamage), 0.0f, MaxHealth);

    if (Health <= 0.0f)
    {
        if (ABeastPlayerCharacter* Player = Cast<ABeastPlayerCharacter>(DamageCauser))
        {
            Player->AddBeastPower(BeastPowerReward);
        }
        Destroy();
    }

    return AppliedDamage;
}
