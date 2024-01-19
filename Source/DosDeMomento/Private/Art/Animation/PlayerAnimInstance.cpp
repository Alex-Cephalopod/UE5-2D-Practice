// Fill out your copyright notice in the Description page of Project Settings.


#include "Art/Animation/PlayerAnimInstance.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		Speed = Pawn->GetVelocity().Size();
		Direction = UKismetAnimationLibrary::CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
		//Direction = CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
	}
}
