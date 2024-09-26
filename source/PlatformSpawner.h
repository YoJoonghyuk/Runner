#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProject22Character.h" 
#include "PlatformSpawner.generated.h"

UCLASS()
class MYPROJECT22_API APlatformSpawner : public AActor
{
    GENERATED_BODY()

public:
    APlatformSpawner();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "Platforms")
        TArray<TSubclassOf<AActor>> PlatformClasses; 

    UPROPERTY(EditAnywhere, Category = "Spawn Settings")
        float SpawnDistance = 500.0f;

    UPROPERTY(EditAnywhere, Category = "Spawn Settings")
        float MinimumDistanceBetweenPlatforms = 700.0f; 

    UPROPERTY(EditAnywhere, Category = "Spawn Settings")
        float SpawnLimitDistance = 500.0f; 

    UPROPERTY(EditAnywhere, Category = "Spawn Settings")
        int32 MaxPlatforms = 50; 

    UPROPERTY(EditAnywhere, Category = "Spawn Settings")
        float PlatformHeightOffset = 0.0f; 

    UPROPERTY(EditAnywhere, Category = "Spawn Settings")
        float OffsetBehindPlayer = 500.0f; 

private:
    FVector LastSpawnLocation; 
    AMyProject22Character* PlayerCharacter; 
    TArray<AActor*> ActivePlatforms; 

    void SpawnPlatform(int32 PlatformIndex = -1); 
    void RemoveBehindPlatforms(); 
};
