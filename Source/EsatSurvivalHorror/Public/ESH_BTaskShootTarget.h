#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ESH_BTaskShootTarget.generated.h"

UCLASS()
class ESATSURVIVALHORROR_API UESH_BTaskShootTarget : public UBTTaskNode {
	GENERATED_BODY()

public:
	UESH_BTaskShootTarget(const FObjectInitializer&);

	UPROPERTY(EditAnywhere, Category = "Blackboard Key")
	struct FBlackboardKeySelector Key;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* MemoryNode) override;
	
};
