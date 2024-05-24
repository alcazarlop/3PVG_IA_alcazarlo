#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ESH_BTaskFindSpot.generated.h"

UCLASS()
class ESATSURVIVALHORROR_API UESH_BTaskFindSpot : public UBTTaskNode {
	GENERATED_BODY()
	
public:
	UESH_BTaskFindSpot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* MemoryNode) override;
	virtual void TickTask(UBehaviorTreeComponent& Owner, uint8* MemoryNode, float DeltaSeconds) override;

	class AESH_Character* SelfActor;
	class AESH_Character* Target;

};
