#include "ShieldTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyProject22Character.h" 

AShieldTrigger::AShieldTrigger()
{
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AShieldTrigger::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AShieldTrigger::OnOverlapEnd);
    ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
    ShieldMesh->SetupAttachment(RootComponent); 
    ShieldMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    ShieldMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AShieldTrigger::BeginPlay()
{
    Super::BeginPlay();
}

void AShieldTrigger::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AShieldTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        AMyProject22Character* PlayerCharacter = Cast<AMyProject22Character>(OtherActor);
        if (PlayerCharacter)
        {
            PlayerCharacter->bHasShield = true; 
            Destroy(); 
        }
    }
}

void AShieldTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
   
}
