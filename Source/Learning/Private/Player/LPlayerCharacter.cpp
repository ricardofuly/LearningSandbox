// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LPlayerCharacter.h"

#include "Components/CapsuleComponent.h"


// Sets default values
ALPlayerCharacter::ALPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	Camera->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ALPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

