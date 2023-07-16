// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPath.generated.h"

UCLASS()
class PLAGUEGAME_API APatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolPath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBillboardComponent* Billboard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UArrowComponent* FacingDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USplineComponent* Path;
	TArray<FVector> Locations;

};
