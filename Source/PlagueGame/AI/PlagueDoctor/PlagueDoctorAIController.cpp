// Fill out your copyright notice in the Description page of Project Settings.
#include "PlagueGame/AI/PlagueDoctor/PlagueDoctorAIController.h"
#include "PlagueDoctor.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

APlagueDoctorAIController::APlagueDoctorAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	BBC = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTree");

	//Creating Senses Configs
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hearing Config");

	//Sight Setup
	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	//Hearing Setup
	HearingConfig->HearingRange = INFINITY;
	//HearingConfig->LoSHearingRange = 300.f;
	
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	//Adds Senses to perception
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &APlagueDoctorAIController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->ConfigureSense(*HearingConfig);
}

void APlagueDoctorAIController::OnPossess(APawn* MyPawn)
{
	Super::OnPossess(MyPawn);

	APlagueDoctor* MyCharacter = Cast<APlagueDoctor>(MyPawn);
	if(MyCharacter && MyCharacter->TreeAsset)
	{
		BBC->InitializeBlackboard(*MyCharacter->TreeAsset->BlackboardAsset);
		BTC->StartTree(*MyCharacter->TreeAsset);
	}
}

void APlagueDoctorAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(DistanceToPlayer>AISightRadius)
	{
		BBC->SetValue<UBlackboardKeyType_Bool>("See Player", false);
		BBC->ClearValue("Player");
	}
}

void APlagueDoctorAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	/*TArray<AActor*> heardActors;
	PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Hearing::StaticClass(),heardActors);
	if(heardActors.Num()>0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString("I heard you"));
	}*/
}