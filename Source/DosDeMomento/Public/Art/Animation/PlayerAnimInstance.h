// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DOSDEMOMENTO_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintNativeEvent)
		void PersonaUpdate();

#pragma region Debug Bools

#pragma endregion

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Animation")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Animation")
		float Direction;
};
