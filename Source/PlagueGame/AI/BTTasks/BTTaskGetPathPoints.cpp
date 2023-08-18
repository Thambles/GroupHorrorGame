// Fill out your copyright notice in the Description page of Project Settings.


#include "PlagueGame/AI/BTTasks/BTTaskGetPathPoints.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "PlagueGame/AI/Pathing/PatrolPath.h"
#include "PlagueGame/AI/PlagueDoctor/PlagueDoctor.h"

UBTTaskGetPathPoints::UBTTaskGetPathPoints()
{
	bCreateNodeInstance = true;
	NodeName = "GetPathPoints";
}

EBTNodeResult::Type UBTTaskGetPathPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	AAIController* MyController = OwnerComp.GetAIOwner();

	if(!MyController)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI invalid"));

	}
	if(!MyBlackboard)
	{
		UE_LOG(LogTemp, Warning, TEXT("Blackboard invalid"));
		return EBTNodeResult::Failed;
	}

	APlagueDoctor* MyCharacter = Cast<APlagueDoctor>(MyController->GetPawn());
	if(!MyCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character invalid"));
		return EBTNodeResult::Failed;
	}
	
	APatrolPath* PathRef = Cast<APatrolPath>(MyCharacter->PatrolPath);
	if(!PathRef || PathRef->Locations.Num()<1)
	{
		UE_LOG(LogTemp, Warning, TEXT("PatrolPath invalid"));
		return EBTNodeResult::Succeeded;
	}

	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>("MoveLocation", PathRef->Locations[Index]);
	if(Index <PathRef->Locations.Num()-1)
	{
		Index++;
		return EBTNodeResult::Succeeded;
	}
	
	Index=1;
	return EBTNodeResult::Succeeded;
}
