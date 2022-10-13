// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()	
	: mFireRange(1000.f)
	, mFireRate(2.f)	
{
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsInFireRange())
	{
		RotateTurret(mPlayerTank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	mPlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); 
	GetWorld()->GetTimerManager().SetTimer(mFireRateTimerHandle, this, &ATower::CheckFireCondition ,mFireRate, true);	
}

void ATower::CheckFireCondition()
{
	if (IsInFireRange() && mPlayerTank->IsAlive())
	{
		Fire();
	}
}

bool ATower::IsInFireRange() const
{
	if (mPlayerTank)
	{
		float dist = FVector::Dist(mPlayerTank->GetActorLocation(), GetActorLocation());
		if (dist <= mFireRange)
		{
			return true;
		}
	}
	return false;
}
