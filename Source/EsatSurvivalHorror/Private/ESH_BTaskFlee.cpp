#include "ESH_BTaskFlee.h"
#include "ESH_Character.h"
#include "ESH_AIController.h"

EBTNodeResult::Type UESH_BTaskFlee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* MemoryNode) {
	Super::ExecuteTask(OwnerComp, MemoryNode);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	UObject* Object = Blackboard->GetValueAsObject("TargetActor");
	AESH_Character* TargetActor = Cast<AESH_Character>(Object);

	AESH_AIController* AIcontroller = Cast<AESH_AIController>(OwnerComp.GetAIOwner());
	AESH_Character* SelfActor = Cast<AESH_Character>(AIcontroller->GetPawn());

	if (!TargetActor || !SelfActor)
		return EBTNodeResult::Failed;

	float Distance = FVector::Distance(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), TargetActor->GetActorLocation());
	if (Distance < 800.0f) {
		
		
		FVector FleeLocation = FVector();
		Blackboard->SetValueAsVector("NewLocation", FleeLocation);
	}
	else {
		Blackboard->SetValueAsObject("TargetActor", nullptr);

	}

	return EBTNodeResult::Succeeded;
}
