
#pragma once

#include "../BallAway.h"
#include "Item/ItemBase.h"
#include "SpeedUpItem.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnGetItemDelegate);

UCLASS()
class BALLAWAY_API ASpeedUpItem : public AItemBase
{
	GENERATED_BODY()
	
public : 
	ASpeedUpItem();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FOnGetItemDelegate OnGetItem;
};
