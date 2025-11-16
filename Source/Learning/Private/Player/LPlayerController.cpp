// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/LAbilitySystemComponent.h"
#include "EnhancedInput/LEnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"
#include "Player/LPlayerState.h"
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
	
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem)) return;
	
	const FGameplayTags& GameplayTags = FGameplayTags::Get();
	
	InputSubsystem->AddMappingContext(InputConfig->DefaultMappingContext, 0);

	EnhancedInputComponent->BindNativeAction(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ALPlayerController::HandleMove);
	EnhancedInputComponent->BindNativeAction(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ALPlayerController::HandleLook);
	EnhancedInputComponent->BindNativeAction(InputConfig, GameplayTags.InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ALPlayerController::HandleLook);

	EnhancedInputComponent->BindAbilityAction(InputConfig, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased);
	
}

void ALPlayerController::HandleMove(const FInputActionValue& InputActionValue)
{
	if (!IsValid(GetPawn())) return;

	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
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
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	TurnAtRate(LookAxisVector.X);
	LookUpAtRate(LookAxisVector.Y);
}

void ALPlayerController::AbilityInputPressed(FGameplayTag InputTag)
{
	if (ALPlayerState* PS = GetPlayerState<ALPlayerState>())
	{
		ULAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		if (!ASC) return;

		ASC->OnAbilityInputPressed(InputTag);
	}
}

void ALPlayerController::AbilityInputReleased(FGameplayTag InputTag)
{
	if (ALPlayerState* PS = GetPlayerState<ALPlayerState>())
	{
		ULAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		if (!ASC) return;

		ASC->OnAbilityInputReleased(InputTag);
	}
}
