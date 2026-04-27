// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"


ATank::ATank()
{
	UE_LOG(LogTemp, Display, TEXT("ATank was created! Called the constructor!"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent); // RootCompoment -> CapsuleComponent

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) {
		
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			
			if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = 
					ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer)) {
				InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (APlayerController* APController = Cast<APlayerController>(Controller)) {
		FHitResult HitResultOut;
		
		APController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResultOut);
		//HitResultOut.ImpactPoint
		DrawDebugSphere(GetWorld(), HitResultOut.ImpactPoint, 25.0f, 12, FColor::Red, false, -1.0f);

		if (HitResultOut.ImpactPoint != FVector::ZeroVector) {
			RotateTurret(HitResultOut.ImpactPoint);
		}
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);
		EnhancedInputComp->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATank::RotateInput);
		EnhancedInputComp->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);
	}
}

void ATank::MoveInput(const FInputActionValue& value)
{
	float InputValue = value.Get<float>();

	FVector DeltaLocation = FVector(0.0f, 0.0f, 0.0f);
	DeltaLocation.X = InputValue * Speed * GetWorld()->GetDeltaSeconds();

	FHitResult* ActorHitResult = new FHitResult();

	AddActorLocalOffset(DeltaLocation, true, ActorHitResult);
	
	AActor* CollidedActor = ActorHitResult->GetActor();

}

void ATank::RotateInput(const FInputActionValue& value)
{
	FRotator DeltaRotation = FRotator(0.0f, 0.0f, 0.0f);
	
	float InputValue = value.Get<float>();
	DeltaRotation.Yaw = InputValue * RotationSpeed * GetWorld()->GetDeltaSeconds();

	AddActorLocalRotation(DeltaRotation, true);

}
void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	IsAlive = false;
	UE_LOG(LogTemp, Display, TEXT("ATank HandleDestruction called for %s"), *GetName());
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetPlayerEnabled(false);
	SetActorEnableCollision(false);
}

void ATank::SetPlayerEnabled(bool enabled)
{
	if (PlayerController) {
		if (enabled) {
			EnableInput(PlayerController);
		}
		else {
			DisableInput(PlayerController);
		}
	}
}
