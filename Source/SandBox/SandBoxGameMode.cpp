// Copyright Epic Games, Inc. All Rights Reserved.

#include "SandBoxGameMode.h"
#include "SandBoxCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASandBoxGameMode::ASandBoxGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}