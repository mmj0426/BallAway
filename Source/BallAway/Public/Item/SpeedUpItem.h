
#pragma once

#include "../BallAway.h"
#include "Item/ItemBase.h"
#include "SpeedUpItem.generated.h"

UCLASS()
class BALLAWAY_API ASpeedUpItem : public AItemBase
{
	GENERATED_BODY()
	
public : 
	ASpeedUpItem();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
