// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetActive(bool IsActive);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	UStaticMeshComponent* mProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	class UProjectileMovementComponent* mMovement;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);

	UPROPERTY(EditAnywhere)
	float mDamage;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
		class UParticleSystemComponent* mTrailParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
		class UParticleSystem* mHitParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* mLaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* mHitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
		TSubclassOf<class UCameraShakeBase> mHitCameraShakeClass;

	class AToonTanksGameMode* mGameMode;

	float mSpeed;
};
