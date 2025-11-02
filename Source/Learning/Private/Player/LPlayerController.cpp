// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LPlayerController.h"

#include "EnhancedInput/LEnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Tags/LGameplayTags.h"

void ALPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ALPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ALPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void ALPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	ULEnhancedInputComponent* EnhancedInputComponent = Cast<ULEnhancedInputComponent>(InputComponent);

	ensureMsgf(EnhancedInputComponent, TEXT("Enhanced Input Component is null!"));

	const FGameplayTags& GameplayTags = FGameplayTags::Get();

	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ALPlayerController::HandleMove);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ALPlayerController::HandleLook);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ALPlayerController::HandleLook);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Fire, ETriggerEvent::Triggered, this, &ALPlayerController::HandleAttack);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Jump, ETriggerEvent::Triggered, this, &ALPlayerController::HandleJump);
}

void ALPlayerController::HandleMove(const FInputActionValue& InputActionValue)
{
	if (this != nullptr)
	{
		const FVector2D MoveValue = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, this->GetControlRotation().Yaw, 0.0f);
 
		if (MoveValue.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			GetPawn()->AddMovementInput(MovementDirection, MoveValue.X);
		}
 
		if (MoveValue.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			GetPawn()->AddMovementInput(MovementDirection, MoveValue.Y);
		}
	}
}

void ALPlayerController::TurnAtRate(float Rate)
{
	GetPawn()->AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ALPlayerController::LookUpAtRate(float Rate)
{
	GetPawn()->AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ALPlayerController::HandleLook(const FInputActionValue& InputActionValue)
{
	if (this != nullptr)
	{
		const FVector2D LookValue = InputActionValue.Get<FVector2D>();
 
		if (LookValue.X != 0.0f)
		{
			TurnAtRate(LookValue.X);
		}
 
		if (LookValue.Y != 0.0f)
		{
			LookUpAtRate(LookValue.Y);
		}
	}
}

void ALPlayerController::HandleJump(const FInputActionValue& InputActionValue)
{
	ACharacter* PlayerCharacter = Cast<ACharacter>(GetPawn());
	PlayerCharacter->Jump();	
}
//@TODO: Implement after ability system setup
void ALPlayerController::HandleAttack(UGameplayAbility* GameplayAbility)
{
	
}