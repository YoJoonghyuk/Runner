#include "MyProject22Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"

AMyProject22Character::AMyProject22Character()
{

    
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    
    CameraYaw = 0.0f;
    CurrentSpeed = 0.0f;
    bIsInAir = false; 

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    GetCharacterMovement()->JumpZVelocity = 2200.0f;

    TargetLocation = GetActorLocation();
    bHasShield = true; 

    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP(TEXT("AnimBlueprint'/Game/Geometry/Meshes/mainCharacter.mainCharacter_C'"));
    if (AnimBP.Succeeded())
    {
        GetMesh()->SetAnimInstanceClass(AnimBP.Class);
    }
}

void AMyProject22Character::BeginPlay()
{
    Super::BeginPlay();

    StartJump();

    GetWorldTimerManager().SetTimer(MoveLeftTimerHandle, this, &AMyProject22Character::StartMoveLeft, 0.5f, false);
}

void AMyProject22Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyProject22Character::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyProject22Character::StopJump);
    PlayerInputComponent->BindAxis("Turn", this, &AMyProject22Character::TurnCamera);

    PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &AMyProject22Character::StartMoveLeft);
    PlayerInputComponent->BindAction("MoveLeft", IE_Released, this, &AMyProject22Character::StopMoveLeft);

    PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &AMyProject22Character::StartMoveRight);
    PlayerInputComponent->BindAction("MoveRight", IE_Released, this, &AMyProject22Character::StopMoveRight);
}

void AMyProject22Character::TurnCamera(float Rate)
{
    CameraYaw += Rate;
}

void AMyProject22Character::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CurrentSpeed = GetVelocity().Size();

    CameraBoom->SetWorldRotation(FRotator(0.0f, CameraYaw, 0.0f));

    FVector CurrentLocation = GetActorLocation();
    CurrentLocation += GetActorForwardVector() * ForwardSpeed * DeltaTime;
    SetActorLocation(CurrentLocation, true);

    if (GetCharacterMovement()->IsFalling())
    {
        bIsInAir = true;
    }
    else
    {
        bIsInAir = true;
    }

    if (CurrentLocation.Z < 20.0f)
    {
        UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
    }

    if (bIsMovingLeft || bIsMovingRight)
    {
        if (bIsMovingLeft)
        {
            TargetLocation = CurrentLocation - FVector(0.0f, MoveDistance, 0.0f);
        }
        else if (bIsMovingRight)
        {
            TargetLocation = CurrentLocation + FVector(0.0f, MoveDistance, 0.0f);
        }

        FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime * (MoveSpeed / MoveDistance), 2.0f);
        SetActorLocation(NewLocation, true);
    }
}

void AMyProject22Character::StartJump()
{
    Jump();
    bIsInAir = true;  
}

void AMyProject22Character::StopJump()
{
    StopJumping();
}

void AMyProject22Character::StartMoveLeft()
{
    bIsMovingLeft = true;
    bIsMovingRight = false;

    GetWorldTimerManager().SetTimer(MoveLeftTimerHandle, this, &AMyProject22Character::StopMoveLeft, 0.5f, false);
}

void AMyProject22Character::StopMoveLeft()
{
    bIsMovingLeft = false;
}

void AMyProject22Character::StartMoveRight()
{
    bIsMovingRight = true;
    bIsMovingLeft = false; 
}

void AMyProject22Character::StopMoveRight()
{
    bIsMovingRight = false;
}
