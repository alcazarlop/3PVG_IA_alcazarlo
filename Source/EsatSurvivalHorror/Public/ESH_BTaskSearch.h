#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ESH_BTaskSearch.generated.h"

UCLASS()
class ESATSURVIVALHORROR_API UESH_BTaskSearch : public UBTTaskNode {
	GENERATED_BODY()

public:
	UESH_BTaskSearch();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* MemoryNode) override;

};
