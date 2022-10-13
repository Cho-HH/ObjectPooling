// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank final : public ABasePawn  
{
	GENERATED_BODY()

public:
	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;
	
	APlayerController* GetPlayerController() const;

	bool IsAlive() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class USpringArmComponent* mSpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class UCameraComponent* mCamera;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float mSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float mTurnRate;

	void Move(float value);
	void Turn(float value);

	APlayerController* mPlayerController;

	bool bAlive;
};
