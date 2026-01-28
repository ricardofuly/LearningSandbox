// Fill out your copyright notice in the Description page of Project Settings.


#include "SSpawnArea.h"

#include "Components/SplineComponent.h"


// Sets default values
ASSpawnArea::ASSpawnArea()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;
	
	Spline->SetClosedLoop(true);
	Spline->bDrawDebug = true;
}

void ASSpawnArea::BeginPlay()
{
	Super::BeginPlay();
}

void ASSpawnArea::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}