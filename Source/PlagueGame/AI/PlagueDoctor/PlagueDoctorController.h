// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlagueDoctorController.generated.h"

/**
 * 
 */
UCLASS()
class PLAGUEGAME_API APlagueDoctorController : public AAIController
{
	GENERATED_BODY()
	

public:
	APlagueDoctorController();
	virtual void OnPossess(APawn* MyPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	//BT References
	UPROPERTY(transient)
		class UBehaviorTreeComponent* BTC;
	UPROPERTY(transient)
		class UBlackboardComponent* BBC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAIPerceptionComponent* MyPerceptionComp;

	//Detection
	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*>& UpdatedActors);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector SoundLocation;
	//Sight
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float AISightRadius = 500.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float AISightAge = 5.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float AILoseSightRadius = AISightRadius + 50.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float AIFieldOfView = 90.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UAISenseConfig_Sight* SightConfig;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float DistanceToPlayer = 0.0f;
	
	//Hearing
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UAISenseConfig_Hearing* HearingConfig;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HearingRange = 5000000.f;
};
