#include "CollisionActor.h"
#include "Components/BoxComponent.h"

ACollisionActor::ACollisionActor()
{
    PrimaryActorTick.bCanEverTick = true;
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;
    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionBox->SetCollisionObjectType(ECC_WorldDynamic); 
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Block); 
    CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f)); 
    CollisionBox->SetHiddenInGame(true); 
}

void ACollisionActor::BeginPlay()
{
    Super::BeginPlay();
}

void ACollisionActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
