#include "ESH_BTaskFindSpot.h"
#include "ESH_Character.h"
#include "ESH_AIController.h"

UESH_BTaskFindSpot::UESH_BTaskFindSpot() {
	bNotifyTick = 1;
}

EBTNodeResult::Type UESH_BTaskFindSpot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* MemoryNode) {
	Super::ExecuteTask(OwnerComp, MemoryNode);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AESH_Character* TargetActor = Cast<AESH_Character>(Blackboard->GetValueAsObject("TargetActor"));

	AESH_AIController* BotController = Cast<AESH_AIController>(OwnerComp.GetAIOwner());
	AESH_Character* OwnerPawn = Cast<AESH_Character>(BotController->GetPawn());

	if (!OwnerPawn || !TargetActor)
		return EBTNodeResult::Failed;

	SelfActor = OwnerPawn;
	Target = TargetActor;

	float radius = 1000.0f;
	int32 points = 12;
	for (int32 i = 0; i < points; ++i) {
		float angle = (360.0f / points) * i;
		float x = TargetActor->GetActorLocation().X + (FMath::Cos(FMath::DegreesToRadians(angle)) * radius);
		float y = TargetActor->GetActorLocation().Y + (FMath::Sin(FMath::DegreesToRadians(angle)) * radius);
		FVector EndPosition = FVector(x, y, TargetActor->GetActorLocation().Z);

		FHitResult Hit;
		GetWorld()->DebugDrawTraceTag = "Raycast";
		FCollisionQueryParams TraceParams(TEXT("Raycast"), false);
		TraceParams.AddIgnoredActor(TargetActor);

		if (!GetWorld()->LineTraceSingleByChannel(Hit, TargetActor->GetActorLocation(), EndPosition, ECC_WorldStatic, TraceParams)) {
			for (int j = 0; j < 2; ++j) {
				float fi = FMath::Atan2(y - TargetActor->GetActorLocation().Y, x - TargetActor->GetActorLocation().X);
				float final_x = TargetActor->GetActorLocation().X + ((radius * 0.5f) * (float)(j + 1)) * FMath::Cos(fi);
				float final_y = TargetActor->GetActorLocation().Y + ((radius * 0.5f) * (float)(j + 1)) * FMath::Sin(fi);

				FVector Location = FVector(final_x, final_y, TargetActor->GetActorLocation().Z);
				SelfActor->ShotPositions.Add(Location);

				DrawDebugSphere(GetWorld(), Location, 20.0f, 10, FColor::Red, false, 1.0f, 0, 2.0f);
			}
		}
	}

	return EBTNodeResult::InProgress;
}

void UESH_BTaskFindSpot::TickTask(UBehaviorTreeComponent& Owner, uint8* MemoryNode, float DeltaSeconds) {
	Super::TickTask(Owner, MemoryNode, DeltaSeconds);

	FVector ClosestPosition;
	float PrevDist = 0.0f;
	float LesserDist = 0.0f;
	for (FVector position : SelfActor->ShotPositions) {
		float AuxDist = PrevDist;
		PrevDist = FVector::Distance(position, Target->GetActorLocation());
		if (PrevDist < AuxDist) {
			LesserDist = PrevDist;
			ClosestPosition = position;
		}
	}
	SelfActor->ShotPositions.Empty();
	SelfActor->UnitBlackboard->SetValueAsVector("NewLocation", ClosestPosition);
	DrawDebugBox(GetWorld(), ClosestPosition, FVector(60.0f, 60.0f, 60.0f), FColor::Green, true, 10.0f, 1, 4.0f);
	//Target->UnitBlackboard->SetValueAsBool("IsTargetBlocked", false);

	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
}
