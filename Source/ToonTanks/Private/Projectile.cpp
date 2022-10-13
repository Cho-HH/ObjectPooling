#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "ToonTanksGameMode.h"

// Sets default values
AProjectile::AProjectile()
	: mProjectileMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh")))
	, mMovement(CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement")))
	, mDamage(50.f)
	, mTrailParticles(CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail")))
	, mSpeed(1000.f)
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = mProjectileMesh;
	mTrailParticles->SetupAttachment(RootComponent);

	mMovement->InitialSpeed = mSpeed;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	mProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if (mLaunchSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, mLaunchSound, GetActorLocation());
	}
	mGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

void AProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	//BasePawn에서 SetOwner를 해줬기 때문에 GetOwner()가 가능
	AActor* myOwner = GetOwner();
	if (myOwner == nullptr)
	{
		return;
	}
	
	AController* myOwnerController = myOwner->GetInstigatorController();
	UClass* damageTypeClass = UDamageType::StaticClass();

	if (otherActor != nullptr && otherActor != this && otherActor != myOwner)
	{
		UGameplayStatics::ApplyDamage(otherActor, mDamage, myOwnerController, this, damageTypeClass);
		if (mHitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, mHitParticles, GetActorLocation(), GetActorRotation());
		}
		if (mHitSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, mHitSound, GetActorLocation());
		}
		if (mHitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(mHitCameraShakeClass);
		}
		mGameMode->ReturnPooledObejct(this);
	}
}

void AProjectile::SetActive(bool IsActive)
{
	if (IsActive)
	{
		mMovement->SetUpdatedComponent(RootComponent);
		mMovement->Velocity = FVector(GetActorRotation().Vector() * mSpeed);
	}
	SetActorHiddenInGame(!IsActive);
	SetActorEnableCollision(IsActive);
	mTrailParticles->SetActive(IsActive);
}
