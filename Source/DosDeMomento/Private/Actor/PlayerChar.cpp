// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PlayerChar.h"

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	PlayerMesh->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(RootComponent);
	PlayerCamera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (LocalPlayerSubsystem)
		{
			LocalPlayerSubsystem->AddMappingContext(MovementContext, 0);
		}
	}

	AnimInst = Cast<UPlayerAnimInstance>(PlayerMesh->GetAnimInstance());
	
}

void APlayerChar::PlayerMove(const FInputActionValue& Value)
{
	const FVector2D MovementDirection = Value.Get<FVector2D>();
	
	AddMovementInput(GetActorForwardVector(), MovementDirection.X);
	
	bool FaceDirection = MovementDirection.X < 0 ? true : false;

	switch (FaceDirection)
	{
	case true: // left
		PlayerMesh->SetRelativeRotation(FRotator(0, 90, 0));
		break;
	case false: // right
		PlayerMesh->SetRelativeRotation(FRotator(0, -90, 0));
		break;
	}
}

void APlayerChar::Sprint(const FInputActionValue& Value)
{
	if (!AnimInst->bIsCrouching && !AnimInst->bIsInAir)
	{
		AnimInst->bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 1000;
	} 
	/*else if (AnimInst->bIsInAir && !AnimInst->bIsAirDash)
	{
		AnimInst->PlayAirDash();
		AnimInst->bIsAirDash = true;
	}*/
}

void APlayerChar::ReleaseSprint(const FInputActionValue& Value)
{
	AnimInst->bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void APlayerChar::Crouch(const FInputActionValue& Value)
{
	AnimInst->bIsCrouching = true;
	GetCharacterMovement()->MaxWalkSpeed = 300;
}

void APlayerChar::ReleaseCrouch(const FInputActionValue& Value)
{
	AnimInst->bIsCrouching = false;
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetMovementComponent()->IsMovingOnGround())
	{
		AnimInst->bIsInAir = true;
	}
	else
	{
		AnimInst->bIsInAir = false;
	}
}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerChar::PlayerMove);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &APlayerChar::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerChar::ReleaseSprint);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APlayerChar::Crouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &APlayerChar::ReleaseCrouch);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerChar::Jump);
	}
}

void APlayerChar::Jump()
{
	Super::Jump();

	if (!GetMovementComponent()->IsFalling())
	{
		AnimInst->PlayJump();
		bCanDoubleJump = true;
	}
	else if (GetMovementComponent()->IsFalling() && bCanDoubleJump)
	{
		AnimInst->PlayDoubleJump();
		bCanDoubleJump = false;
	}
}

