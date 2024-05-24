#include "ESH_BTaskShootTarget.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Kismet/KismetMathLibrary.h"
#include "ESH_Character.h"
#include "ESH_AIController.h"


UESH_BTaskShootTarget::UESH_BTaskShootTarget(const FObjectInitializer& Object) : Super(Object) {
	Key.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UESH_BTaskShootTarget, Key), AESH_Character::StaticClass());
}

EBTNodeResult::Type UESH_BTaskShootTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* MemoryNode) {
	Super::ExecuteTask(OwnerComp, MemoryNode);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	UObject* object = Blackboard->GetValueAsObject("TargetActor");
	AESH_Character* TargetActor = Cast<AESH_Character>(object);

	AESH_AIController* AIcontroller = Cast<AESH_AIController>(OwnerComp.GetAIOwner());
	AESH_Character* SelfActor = Cast<AESH_Character>(AIcontroller->GetPawn());

	if (!SelfActor || !TargetActor)
		return EBTNodeResult::Failed;

	SelfActor->NextShoot += GetWorld()->GetDeltaSeconds() * 2.0f;
	float Distance = FVector::Distance(SelfActor->GetActorLocation(), TargetActor->GetActorLocation());

	if (SelfActor->NextShoot >= SelfActor->FireRate && Distance <= 800.0f) {
		SelfActor->NextShoot = 0.0f;

		GetWorld()->DebugDrawTraceTag = "Raycast";
		FCollisionQueryParams TraceParams(TEXT("Raycast"), false);
		TraceParams.AddIgnoredActor(SelfActor);

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, SelfActor->GetActorLocation(), TargetActor->GetActorLocation(), ECC_WorldStatic, TraceParams)) {
			if (Cast<AESH_Character>(Hit.GetActor()) == TargetActor) {
				Blackboard->SetValueAsBool("IsTargetBlocked", false);
				SelfActor->Weapon->Fire(SelfActor->GetActorForwardVector());
				return EBTNodeResult::Succeeded;
			}
			Blackboard->SetValueAsBool("IsTargetBlocked", true);
			return EBTNodeResult::Failed;
		}
	}

	return EBTNodeResult::Failed;
}
