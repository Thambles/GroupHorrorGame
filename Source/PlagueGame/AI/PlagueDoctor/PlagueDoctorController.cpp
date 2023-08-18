// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable All
#include "PlagueGame/AI/PlagueDoctor/PlagueDoctorController.h"
#include "PlagueDoctor.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

APlagueDoctorController::APlagueDoctorController()
{
	PrimaryActorTick.bCanEverTick = true;
	BBC = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTree");

	//Creating Senses Configs
	MyPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("Perception Component");
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
	HearingConfig->HearingRange = 500.f;
	
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	
	//Adds Senses to perception
	if(MyPerceptionComp!=nullptr)
	{
		MyPerceptionComp->SetDominantSense(*SightConfig->GetSenseImplementation());
		MyPerceptionComp->ConfigureSense(*HearingConfig);
		MyPerceptionComp->ConfigureSense(*SightConfig);
	}
}

void APlagueDoctorController::OnPossess(APawn* MyPawn)
{
	Super::OnPossess(MyPawn);

	APlagueDoctor* MyCharacter = Cast<APlagueDoctor>(MyPawn);
	if (MyCharacter && MyCharacter->TreeAsset)
	{
		BBC->InitializeBlackboard(*MyCharacter->TreeAsset->BlackboardAsset);
		BTC->StartTree(*MyCharacter->TreeAsset);
		UE_LOG(LogTemp, Warning, TEXT("Tree started"));
	}
}

void APlagueDoctorController::Tick(float DeltaSeconds)
{
}

void APlagueDoctorController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APlagueDoctorController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Beginplay Called"));
	if(MyPerceptionComp!=nullptr)
	{
		MyPerceptionComp->OnPerceptionUpdated.AddDynamic(this, &APlagueDoctorController::OnPawnDetected);
		UE_LOG(LogTemp, Warning, TEXT("Perception Binding has worked"));
	}
}

void APlagueDoctorController::OnPawnDetected(const TArray<AActor*>& UpdatedActors)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Detected"));
	TArray<AActor*> heardActors;
	PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Hearing::StaticClass(),heardActors);
	if(heardActors.Num()>0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString("I heard you"));
	}
}
