// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "MessureDistance_BTTaskNode.h"

UMessureDistance_BTTaskNode::UMessureDistance_BTTaskNode()
{
	NodeName = "Measure Distance To Target";
}

EBTNodeResult::Type
UMessureDistance_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackComp = OwnerComp.GetBlackboardComponent();

	if (!BlackComp)
	{
		return EBTNodeResult::Failed;
	}

	AActor* Target = Cast<AActor>(BlackComp->GetValueAsObject("Target"));

	APawn* AIPawn = OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr;

	if (!Target || !AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	float Distance = FVector::Dist(AIPawn->GetActorLocation(), Target->GetActorLocation());

	BlackComp->SetValueAsFloat("Distance", Distance);
	return EBTNodeResult::Succeeded;
}