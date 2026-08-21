#include "BeastSaveSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UBeastSaveSubsystem::SavePlayer(const UBeastGameSave* State)
{
    if (!State) return;
    UGameplayStatics::SaveGameToSlot(const_cast<UBeastGameSave*>(State), GetSaveSlot(), 0);
}

UBeastGameSave* UBeastSaveSubsystem::LoadPlayer() const
{
    if (!UGameplayStatics::DoesSaveGameExist(GetSaveSlot(), 0)) return nullptr;
    return Cast<UBeastGameSave>(UGameplayStatics::LoadGameFromSlot(GetSaveSlot(), 0));
}

void UBeastSaveSubsystem::ClearPlayerSave()
{
    if (UGameplayStatics::DoesSaveGameExist(GetSaveSlot(), 0))
        UGameplayStatics::DeleteGameInSlot(GetSaveSlot(), 0);
}
