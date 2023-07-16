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


protected:
	UBehaviorTree* BTree;
	UBlackboardComponent* BBC;
};
