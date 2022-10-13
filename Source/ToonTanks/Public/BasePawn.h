// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	class UHPWidget* GetProgressBar() const;

protected:
	virtual void RotateTurret(FVector Target);
	void Fire();
	void BeginPlay() override;

	virtual void HandleDestruction();

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* mTurretMesh;

private:
	UPROPERTY(VisibleDefaultsOnly)
	class UCapsuleComponent* mCapsule;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* mBaseMesh;

	UPROPERTY(VisibleDefaultsOnly)
		//USceneComponent는 위치정보만을 지닌 가벼운 컴포넌트
		USceneComponent* mProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* mHPWidget;

	class UHPWidget* mProgressBar;

	UPROPERTY(VisibleAnywhere, Category = "HP")
		class UHealthComponent* mHealthComponent;

	//블루프린트 기반의 개체 생성
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> mProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		class UParticleSystem* mDeathParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		class USoundBase* mDeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
		class USoundBase* mLaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
		TSubclassOf<class UCameraShakeBase> mDeathCameraShakeClass;

	class AToonTanksGameMode* mGameMode;
};