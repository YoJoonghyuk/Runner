#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyProject22Character.generated.h"

UCLASS(config = Game)
class AMyProject22Character : public ACharacter
{
    GENERATED_BODY()

public:
    AMyProject22Character();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
        USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
        UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
        float CameraYaw;

    void MoveForward();
    void StartJump();
    void StopJump();
    void TurnCamera(float Rate);
    void MoveLeft();
    void MoveRight();

    void StartMoveLeft();
    void StopMoveLeft();
    void StartMoveRight();
    void StopMoveRight();

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(BlueprintReadWrite, Category = "Shield")
        bool bHasShield; 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
        float CurrentSpeed;
    UPROPERTY(BlueprintReadOnly, Category = "Animation")
        bool bIsInAir; 

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
        float MoveDistance = 1000.0f; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
        float MoveSpeed = 2500.0f; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
        float ForwardSpeed = 800.0f; 

private:
    FVector TargetLocation;
    bool bIsMovingLeft = false;
    bool bIsMovingRight = false;

    FTimerHandle MoveLeftTimerHandle;

protected:
    virtual void BeginPlay() override;
};
