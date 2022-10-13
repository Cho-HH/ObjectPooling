// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "Projectile.h"

AToonTanksGameMode::AToonTanksGameMode()
	: mStartDelay(3.f)
	, mTowersCount(0)
{
}

void AToonTanksGameMode::ActorDied(AActor* deadActor)
{
	if (deadActor == mPlayerTank)
	{
		mPlayerTank->HandleDestruction();
		if (mPlayerController != nullptr)
		{
			mPlayerController->SetPlayerEnableState(false);
		}
		GameOver(false);
	}
	else
	{
		ATower* tower = Cast<ATower>(deadActor);
		tower->HandleDestruction();
		mTowersCount--;
		UpdateLeftTowerCount();
		if (mTowersCount == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	TArray<class AActor*> towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), towers);
	mTowersCount = towers.Num();
	UpdateLeftTowerCount();
	mPlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	mPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (mPlayerController != nullptr)
	{
		mPlayerController->SetPlayerEnableState(false);
	
		FTimerHandle playerEnbleTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(playerEnbleTimerHandle, FTimerDelegate::CreateLambda([this]()
			{
				mPlayerController->SetPlayerEnableState(true);
			}
		), mStartDelay, false);
	
	}
}

void AToonTanksGameMode::ReturnPooledObejct(AProjectile* projectile)
{
	UE_LOG(LogTemp, Warning, TEXT("Return Object"));
	projectile->SetActive(false);
	mProjectilePool.Push(projectile);
}

AProjectile* AToonTanksGameMode::SpawnPooledObject(FVector spawnLocation, FRotator spawnRotation, AActor* owner)
{
	AProjectile* proj = nullptr;
	if (mProjectilePool.IsEmpty())
	{
		proj = GetWorld()->SpawnActor<AProjectile>(mProjectileClass, spawnLocation, spawnRotation);
		UE_LOG(LogTemp, Warning, TEXT("Create New Projectile"));
	}
	else
	{
		proj = mProjectilePool.Pop();
		proj->TeleportTo(spawnLocation, spawnRotation);
		UE_LOG(LogTemp, Warning, TEXT("Object Pooling"));
	}
	proj->SetOwner(owner);
	proj->SetActive(true);
	return proj;
}

