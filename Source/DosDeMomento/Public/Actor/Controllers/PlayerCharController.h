// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharController.generated.h"

/**
 * 
 */
UCLASS()
class DOSDEMOMENTO_API APlayerCharController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	//call the tick function every frame
	virtual void Tick(float DeltaTime) override;
	
};
