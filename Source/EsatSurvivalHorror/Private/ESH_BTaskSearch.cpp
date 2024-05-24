#include "ESH_BTaskSearch.h"
#include "ESH_Character.h"
#include "ESH_AIController.h"
#include "NavigationSystem.h"

UESH_BTaskSearch::UESH_BTaskSearch() {

}

EBTNodeResult::Type UESH_BTaskSearch::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* MemoryNode) {
	Super::ExecuteTask(Owner, MemoryNode);

	UBlackboardComponent* Blackboard = Owner.GetBlackboardComponent();

	AESH_AIController* BotController = Cast<AESH_AIController>(Owner.GetAIOwner());
	AESH_Character* OwnerPawn = Cast<AESH_Character>(BotController->GetPawn());

	float offset = 200.0f;
	float RandomX = FMath::FRandRange(-OwnerPawn->NavMesh.X + offset, OwnerPawn->NavMesh.X - offset);
	float RandomY = FMath::FRandRange(-OwnerPawn->NavMesh.Y + offset, OwnerPawn->NavMesh.Y - offset);

	FVector RandomNewPosition = FVector(RandomX, RandomY, OwnerPawn->GetActorLocation().Z);

	Blackboard->SetValueAsVector("NewLocation", RandomNewPosition);
	return EBTNodeResult::Succeeded;
}

