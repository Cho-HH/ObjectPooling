// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower final : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATower();
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

private:
	class ATank* mPlayerTank;

	UPROPERTY(EditAnywhere)
	float  mFireRange;

	FTimerHandle mFireRateTimerHandle;
	float mFireRate;
	void CheckFireCondition();

	bool IsInFireRange() const;
};
