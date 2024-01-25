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
	}
	else
	{
		PersonaUpdate();
	}
}

void UPlayerAnimInstance::PlayJump()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Jump"));
	PlaySlotAnimationAsDynamicMontage(JumpAnim, "Jump"); // fix this later. not playing anim
}

void UPlayerAnimInstance::PlayDoubleJump()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Double Jump"));
	PlaySlotAnimationAsDynamicMontage(DoubleJumpAnim, "Jump");
}

void UPlayerAnimInstance::PersonaUpdate_Implementation()
{
	//UE_LOG(LogTemp, Warning, TEXT("PersonaUpdate"));
	if (bDebugJump)
	{
		PlayJump();
		bDebugJump = false;
	}
	else if (bDebugDJump)
	{
		PlayDoubleJump();
		bDebugDJump = false;
	}
}
