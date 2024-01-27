// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Controllers/PlayerCharController.h"

void APlayerCharController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = true;
	
}

void APlayerCharController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}
