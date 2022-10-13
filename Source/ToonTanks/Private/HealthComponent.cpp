// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "HPWidget.h"
#include "BasePawn.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
	: mMaxHealth(100.f)
	, mHealth(0.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	mHealth = mMaxHealth;

	//component를 소유한 액터의 포인터
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	mGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType, AController* Instigator, AActor* damageCauser)
{
	if (damage <= 0.f)
	{
		return;
	}

	mHealth -= damage;

	ABasePawn* pawn = Cast<ABasePawn>(damagedActor);
	UHPWidget* widget = pawn->GetProgressBar();
	widget->SetPercent(mHealth / mMaxHealth);

	UE_LOG(LogTemp, Warning, TEXT("Health : %f"), mHealth);
	if (mHealth <= 0.f && mGameMode)
	{
		mGameMode->ActorDied(damagedActor);
	}
}

