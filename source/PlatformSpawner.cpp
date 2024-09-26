#include "PlatformSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject22Character.h" // Подключаем класс персонажа

APlatformSpawner::APlatformSpawner()
{
    PrimaryActorTick.bCanEverTick = true;
    LastSpawnLocation = FVector::ZeroVector; // Инициализация
}

void APlatformSpawner::BeginPlay()
{
    Super::BeginPlay();

    PlayerCharacter = Cast<AMyProject22Character>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (PlayerCharacter)
    {
        LastSpawnLocation = PlayerCharacter->GetActorLocation(); // Начальная позиция спавна

        // Спавним первые три платформы с нулевых индексов
        for (int32 i = 0; i < 3; i++)
        {
            SpawnPlatform(i); // Используем индекс для выбора нужного элемента массива
        }

        // Спавним остальные платформы случайным образом
        for (int32 i = 3; i < MaxPlatforms; i++)
        {
            SpawnPlatform(); // Случайный выбор платформ
        }
    }
}

void APlatformSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PlayerCharacter)
    {
        float DistanceToPlayer = FVector::Dist(PlayerCharacter->GetActorLocation(), LastSpawnLocation);

        // Проверяем, нужно ли спавнить новую платформу
        if (DistanceToPlayer > SpawnDistance)
        {
            SpawnPlatform();  // Спавн случайной платформы
            RemoveBehindPlatforms(); // Удаляем платформы сзади
        }
    }
}

void APlatformSpawner::SpawnPlatform(int32 PlatformIndex)
{
    // Проверяем, не превышает ли количество активных платформ максимальное значение
    if (ActivePlatforms.Num() < MaxPlatforms)
    {
        // Проверяем расстояние до последней спавненной платформы
        if (FVector::Dist(LastSpawnLocation, GetActorLocation() + FVector(SpawnDistance, 0, 0)) > MinimumDistanceBetweenPlatforms)
        {
            // Если передан индекс, выбираем платформу по индексу, иначе случайно
            TSubclassOf<AActor> SelectedPlatformClass;
            if (PlatformIndex >= 0 && PlatformIndex < PlatformClasses.Num())
            {
                SelectedPlatformClass = PlatformClasses[PlatformIndex];
            }
            else
            {
                // Выбираем случайный индекс, если PlatformIndex не задан
                int32 RandomIndex = FMath::RandRange(0, PlatformClasses.Num() - 1);
                SelectedPlatformClass = PlatformClasses[RandomIndex];
            }

            // Получаем позицию для спавна
            FVector SpawnLocation = LastSpawnLocation + FVector(SpawnDistance, 0, PlatformHeightOffset);

            // Спавним платформу
            AActor* SpawnedPlatform = GetWorld()->SpawnActor<AActor>(SelectedPlatformClass, SpawnLocation, FRotator::ZeroRotator);
            ActivePlatforms.Add(SpawnedPlatform); // Добавляем платформу в массив активных
            LastSpawnLocation = SpawnLocation; // Обновляем последнюю позицию спавна
        }
    }
}

void APlatformSpawner::RemoveBehindPlatforms()
{
    FVector PlayerLocation = PlayerCharacter->GetActorLocation();

    for (int32 i = ActivePlatforms.Num() - 1; i >= 0; i--)
    {
        AActor* Platform = ActivePlatforms[i];
        if (Platform && Platform->GetActorLocation().X < PlayerLocation.X - OffsetBehindPlayer) // Учитываем OffsetBehindPlayer
        {
            Platform->Destroy(); // Удаляем платформу
            ActivePlatforms.RemoveAt(i); // Удаляем из массива активных
        }
    }
}
