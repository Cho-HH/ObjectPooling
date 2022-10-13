// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AToonTanksGameMode();
	void ActorDied(AActor* deadActor);

protected:
	virtual void BeginPlay() override;
	
	//블루프린트에서 구현할 함수 (본문이 없어도 됨)
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateLeftTowerCount();

private:
	class ATank* mPlayerTank;
	class AToonTanksPlayerController* mPlayerController;

	float mStartDelay;

	void HandleGameStart();

	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	int32 mTowersCount;

	//ObjectPooling
public:
	void ReturnPooledObejct(class AProjectile* projectile);
	class AProjectile* SpawnPooledObject(FVector spawnLocation, FRotator spawnRotation, AActor* owner);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<class AProjectile> mProjectileClass;

	TArray<class AProjectile*> mProjectilePool;
};
