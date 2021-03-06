// Fill out your copyright notice in the Description page of Project Settings.

#include "Shape.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UShape::UShape()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShape::BeginPlay()
{
	Super::BeginPlay();
	auto pos = GetOwner()->GetActorLocation();
	auto me = GetOwner()->FindComponentByClass<UShape>();
	// ...
	
}


// Called every frame
void UShape::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

