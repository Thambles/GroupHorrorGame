// Fill out your copyright notice in the Description page of Project Settings.


#include "PlagueGame/AI/PlagueDoctor/PlagueDoctor.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlagueDoctor::APlagueDoctor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	//Sets rotation rotate and rotate to move
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(.0f, 200.f, .0f);
}

// Called when the game starts or when spawned
void APlagueDoctor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Player called"));
	
}

// Called every frame
void APlagueDoctor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlagueDoctor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

