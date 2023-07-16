// Fill out your copyright notice in the Description page of Project Settings.
#include "PlagueGame/AI/PlagueDoctor/PlagueDoctorAIController.h"
#include "PlagueDoctor.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

APlagueDoctorAIController::APlagueDoctorAIController()
{
	BBC = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTree");
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