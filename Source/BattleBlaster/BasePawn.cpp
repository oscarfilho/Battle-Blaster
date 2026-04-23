// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	SetRootComponent(CapsuleComp);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh of turret"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	//TurretMesh->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(TurretMesh->GetComponentLocation(), LookAtTarget));
	FVector DirectionToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f, DirectionToTarget.Rotation().Yaw, 0.0f);
	FRotator InterpolatedRotation = FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		LookAtRotation,
		GetWorld()->GetDeltaSeconds(),
		TurretRotationSpeed
	);

	TurretMesh->SetWorldRotation(InterpolatedRotation);
}

void ABasePawn::Fire()
{
	UE_LOG(LogTemp, Display, TEXT("Fire was called at BasePawn Class!"));

	FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

	//DrawDebugSphere(GetWorld(), SpawnLocation, 25.0f, 12, FColor::Red, false, 3.0f);

	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);

	UE_LOG(LogTemp, Display, TEXT("Spawn Location: %s"), *SpawnLocation.ToCompactString());
	UE_LOG(LogTemp, Display, TEXT("Spawn Rotation: %s"), *SpawnRotation.ToCompactString());
}
