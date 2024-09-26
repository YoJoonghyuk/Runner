#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeAccelerator.generated.h"

UCLASS()
class MYPROJECT22_API ATimeAccelerator : public AActor
{
    GENERATED_BODY()

public:
    ATimeAccelerator();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "Time Settings")
        float AccelerationFactor = 1.0f; 

    UPROPERTY(EditAnywhere, Category = "Time Settings")
        float MaxTimeScale = 5.0f;

private:
    float CurrentTimeScale; 
    float TimeIncreaseRate = 0.005f;
};
