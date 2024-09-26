#include "TimeAccelerator.h"
#include "Kismet/GameplayStatics.h" 
#include "GameFramework/Actor.h" 
#include "Engine/World.h" 

ATimeAccelerator::ATimeAccelerator()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentTimeScale = 1.0f; 
}

void ATimeAccelerator::BeginPlay()
{
    Super::BeginPlay();
}

void ATimeAccelerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CurrentTimeScale < MaxTimeScale)
    {
        CurrentTimeScale += TimeIncreaseRate * DeltaTime; 
        CurrentTimeScale = FMath::Min(CurrentTimeScale, MaxTimeScale); 
    }

    UGameplayStatics::SetGlobalTimeDilation(GetWorld(), CurrentTimeScale);
}
