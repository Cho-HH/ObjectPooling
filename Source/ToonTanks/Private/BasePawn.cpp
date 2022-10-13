// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "HealthComponent.h"
#include "HPWidget.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "ToonTanksGameMode.h"

// Sets default values
ABasePawn::ABasePawn()
	: mCapsule(CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider")))
	, mBaseMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh")))
	, mTurretMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh")))
	, mProjectileSpawnPoint(CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point")))
	, mHealthComponent(CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component")))
	, mHPWidget(CreateDefaultSubobject<UWidgetComponent>(TEXT("HP BAR")))
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = mCapsule;
	mBaseMesh->SetupAttachment(mCapsule);
	mTurretMesh->SetupAttachment(mBaseMesh);
	mProjectileSpawnPoint->SetupAttachment(mTurretMesh);
	mHPWidget->SetupAttachment(RootComponent);
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	mProgressBar = Cast<UHPWidget>(mHPWidget->GetUserWidgetObject());
	mGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

void ABasePawn::HandleDestruction()
{
	//TODO : 파괴기능 / 파괴소리 이펙트
	if (mDeathParticles != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, mDeathParticles, GetActorLocation(), GetActorRotation());
	}
	if (mDeathSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, mDeathSound, GetActorLocation());
	}
	if (mDeathCameraShakeClass != nullptr)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(mDeathCameraShakeClass);
	}
}

void ABasePawn::RotateTurret(FVector Target)
{
	//Yaw기준으로만 회전, 월드 좌표
	FVector toTarget = Target - mTurretMesh->GetComponentLocation();
	//mTurretMesh->GetComponentLocation() == GetActorLocation()

	FRotator lookAtRotation = FRotator(0.f, toTarget.Rotation().Yaw, 0.f);
	mTurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			mTurretMesh->GetComponentRotation(),
			lookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			10.f)
	);
}

void ABasePawn::Fire()
{
	FRotator rotation = mProjectileSpawnPoint->GetComponentRotation();
	FVector location = mProjectileSpawnPoint->GetComponentLocation();
	if (mLaunchSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, mLaunchSound, GetActorLocation());
	}
	mGameMode->SpawnPooledObject(location, rotation, this);
}

UHPWidget* ABasePawn::GetProgressBar() const
{
	return mProgressBar;
}