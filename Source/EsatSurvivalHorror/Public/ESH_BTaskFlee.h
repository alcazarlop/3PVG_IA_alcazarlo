#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ESH_BTaskFlee.generated.h"

UCLASS()
class ESATSURVIVALHORROR_API UESH_BTaskFlee : public UBTTaskNode {
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* MemoryNode) override;
	
};
