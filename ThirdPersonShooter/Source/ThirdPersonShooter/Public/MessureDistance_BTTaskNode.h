// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MessureDistance_BTTaskNode.generated.h"
 
UCLASS()
class THIRDPERSONSHOOTER_API UMessureDistance_BTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UMessureDistance_BTTaskNode();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
