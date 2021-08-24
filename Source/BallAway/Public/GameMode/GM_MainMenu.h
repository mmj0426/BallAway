
#pragma once

#include "../BallAway.h"
#include "GameFramework/GameModeBase.h"
#include "GM_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class BALLAWAY_API AGM_MainMenu : public AGameModeBase
{
	GENERATED_BODY()

public:

	AGM_MainMenu();

	float LoadScore();

	float BestScore;
};
