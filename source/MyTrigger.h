#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTrigger.generated.h"

UCLASS()
class MYPROJECT22_API AMyTrigger : public AActor
{
    GENERATED_BODY()

public:
    AMyTrigger();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
        class UBoxComponent* TriggerBox;

    UPROPERTY(VisibleAnywhere)
        class UStaticMeshComponent* SpikeMesh; 
    UFUNCTION()
        void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
            class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
            bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
        void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
            class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
