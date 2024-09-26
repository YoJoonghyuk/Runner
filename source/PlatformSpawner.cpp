#include "PlatformSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject22Character.h" // ���������� ����� ���������

APlatformSpawner::APlatformSpawner()
{
    PrimaryActorTick.bCanEverTick = true;
    LastSpawnLocation = FVector::ZeroVector; // �������������
}

void APlatformSpawner::BeginPlay()
{
    Super::BeginPlay();

    PlayerCharacter = Cast<AMyProject22Character>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (PlayerCharacter)
    {
        LastSpawnLocation = PlayerCharacter->GetActorLocation(); // ��������� ������� ������

        // ������� ������ ��� ��������� � ������� ��������
        for (int32 i = 0; i < 3; i++)
        {
            SpawnPlatform(i); // ���������� ������ ��� ������ ������� �������� �������
        }

        // ������� ��������� ��������� ��������� �������
        for (int32 i = 3; i < MaxPlatforms; i++)
        {
            SpawnPlatform(); // ��������� ����� ��������
        }
    }
}

void APlatformSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PlayerCharacter)
    {
        float DistanceToPlayer = FVector::Dist(PlayerCharacter->GetActorLocation(), LastSpawnLocation);

        // ���������, ����� �� �������� ����� ���������
        if (DistanceToPlayer > SpawnDistance)
        {
            SpawnPlatform();  // ����� ��������� ���������
            RemoveBehindPlatforms(); // ������� ��������� �����
        }
    }
}

void APlatformSpawner::SpawnPlatform(int32 PlatformIndex)
{
    // ���������, �� ��������� �� ���������� �������� �������� ������������ ��������
    if (ActivePlatforms.Num() < MaxPlatforms)
    {
        // ��������� ���������� �� ��������� ���������� ���������
        if (FVector::Dist(LastSpawnLocation, GetActorLocation() + FVector(SpawnDistance, 0, 0)) > MinimumDistanceBetweenPlatforms)
        {
            // ���� ������� ������, �������� ��������� �� �������, ����� ��������
            TSubclassOf<AActor> SelectedPlatformClass;
            if (PlatformIndex >= 0 && PlatformIndex < PlatformClasses.Num())
            {
                SelectedPlatformClass = PlatformClasses[PlatformIndex];
            }
            else
            {
                // �������� ��������� ������, ���� PlatformIndex �� �����
                int32 RandomIndex = FMath::RandRange(0, PlatformClasses.Num() - 1);
                SelectedPlatformClass = PlatformClasses[RandomIndex];
            }

            // �������� ������� ��� ������
            FVector SpawnLocation = LastSpawnLocation + FVector(SpawnDistance, 0, PlatformHeightOffset);

            // ������� ���������
            AActor* SpawnedPlatform = GetWorld()->SpawnActor<AActor>(SelectedPlatformClass, SpawnLocation, FRotator::ZeroRotator);
            ActivePlatforms.Add(SpawnedPlatform); // ��������� ��������� � ������ ��������
            LastSpawnLocation = SpawnLocation; // ��������� ��������� ������� ������
        }
    }
}

void APlatformSpawner::RemoveBehindPlatforms()
{
    FVector PlayerLocation = PlayerCharacter->GetActorLocation();

    for (int32 i = ActivePlatforms.Num() - 1; i >= 0; i--)
    {
        AActor* Platform = ActivePlatforms[i];
        if (Platform && Platform->GetActorLocation().X < PlayerLocation.X - OffsetBehindPlayer) // ��������� OffsetBehindPlayer
        {
            Platform->Destroy(); // ������� ���������
            ActivePlatforms.RemoveAt(i); // ������� �� ������� ��������
        }
    }
}
