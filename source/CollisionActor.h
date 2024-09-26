#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollisionActor.generated.h"

UCLASS()
class MYPROJECT22_API ACollisionActor : public AActor
{
    GENERATED_BODY()

public:
    ACollisionActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Collision")
        class UBoxComponent* CollisionBox; 
};
