

#include "MyProject22GameMode.h"
#include "MyProject22Character.h"
#include "UObject/ConstructorHelpers.h"

AMyProject22GameMode::AMyProject22GameMode()
{

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
