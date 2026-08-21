#include "BeastPlayerCharacter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ABeastPlayerCharacter::ABeastPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    Health = MaxHealth;
}

void ABeastPlayerCharacter::PerformAxeAttack()
{
    const FVector Start = GetActorLocation() + GetActorForwardVector() * 50.0f;
    const FVector End = Start + GetActorForwardVector() * 150.0f;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    if (GetWorld() && GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, Params))
    {
        if (AActor* Target = Hit.GetActor())
        {
            Target->TakeDamage(AxeDamage, FDamageEvent(), GetController(), this);
        }
    }
}

void ABeastPlayerCharacter::AddBeastPower(int32 Amount)
{
    BeastPower = FMath::Max(0, BeastPower + Amount);
}

void ABeastPlayerCharacter::ReceiveDamage(float Amount)
{
    Health = FMath::Clamp(Health - FMath::Max(0.0f, Amount), 0.0f, MaxHealth);
    if (Health <= 0.0f)
    {
        // Respawn/game-over flow will be added in a later milestone.
    }
}
