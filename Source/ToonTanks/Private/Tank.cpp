// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
	: mSpringArm(CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm")))
	, mCamera(CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")))
	, mSpeed(200.f)
	, mTurnRate(200.f)
	, bAlive(true)
{
	mSpringArm->SetupAttachment(RootComponent);
	mCamera->SetupAttachment(mSpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	mPlayerController = Cast<APlayerController>(GetController());
	
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mPlayerController)
	{
		FHitResult hitResult;
		mPlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			hitResult);

	/*	DrawDebugSphere(
			GetWorld(),
			hitResult.ImpactPoint,
			25.f,
			12,
			FColor::Blue,
			false
		);*/

		RotateTurret(hitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

APlayerController* ATank::GetPlayerController() const
{
	return mPlayerController;
}

bool ATank::IsAlive() const
{
	return bAlive;
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float value)
{
	FVector deltaLocation = FVector::ZeroVector;
	deltaLocation.X = value * mSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	//두 번째 매개변수는 충돌감지를 하는 boolean
	//루트 컴포넌트만 콜리전 설정을 해주면 됨
	AddActorLocalOffset(deltaLocation, true);
}

void ATank::Turn(float value)
{
	FRotator deltaRotation = FRotator::ZeroRotator;
	deltaRotation.Yaw = value * mTurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(deltaRotation, true);
}
