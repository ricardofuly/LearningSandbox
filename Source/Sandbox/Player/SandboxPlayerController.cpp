// Copyright Epic Games, Inc. All Rights Reserved.


#include "SandboxPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "SPlayerState.h"
#include "AbilitySystem/SAbilitySystemComponent.h"
#include "Input/SEnhancedInputComponent.h"
#include "Tags/SGameplayTags.h"

void ASandboxPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASandboxPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem)) return;
	
	InputSubsystem->AddMappingContext(InputConfig->DefaultMappingContext, 0);
	
	
	USEnhancedInputComponent* EnhancedInputComponent = Cast<USEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;
	
	EnhancedInputComponent->BindNativeAction(InputConfig, Sandbox::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::HandleMoveInput);
	EnhancedInputComponent->BindNativeAction(InputConfig, Sandbox::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::HandleLookInput);

	EnhancedInputComponent->BindAbilityAction(InputConfig, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased);
}

void ASandboxPlayerController::HandleMoveInput(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

void ASandboxPlayerController::HandleLookInput(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ASandboxPlayerController::AbilityInputPressed(FGameplayTag InInputTag)
{
	if (ASPlayerState* PS = GetPlayerState<ASPlayerState>())
	{
		USAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		if (!IsValid(ASC)) return;
		ASC->OnAbilityInputPressed(InInputTag);
	};		
}

void ASandboxPlayerController::AbilityInputReleased(FGameplayTag InInputTag)
{
	if (ASPlayerState* PS = GetPlayerState<ASPlayerState>())
	{
		USAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		if (!IsValid(ASC)) return;
		ASC->OnAbilityInputReleased(InInputTag);
	};	
}
