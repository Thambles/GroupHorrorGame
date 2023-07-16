// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskGetPathPoints.generated.h"

/**
 * 
 */
UCLASS()
class PLAGUEGAME_API UBTTaskGetPathPoints : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTaskGetPathPoints();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	int32 Index=0;
};
