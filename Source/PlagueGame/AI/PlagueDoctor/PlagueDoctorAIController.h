// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlagueDoctorAIController.generated.h"

/**
 * 
 */
UCLASS()
class PLAGUEGAME_API APlagueDoctorAIController : public AAIController
{
	GENERATED_BODY()


public:
	APlagueDoctorAIController();
	virtual void OnPossess(APawn* MyPawn) override;
	virtual void Tick(float DeltaSeconds) override;

	//Behaviour Tree Reference
	UPROPERTY(transient)
		class UBehaviorTreeComponent* BTC;
	UPROPERTY(transient)
		class UBlackboardComponent* BBC;

	//Detection
	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*>& DetectedPawns);

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector SoundLocation;
};
