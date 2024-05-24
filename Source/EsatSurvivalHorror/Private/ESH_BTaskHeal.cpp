#include "ESH_BTaskHeal.h"
#include "ESH_Character.h"
#include "EngineUtils.h"

EBTNodeResult::Type UESH_BTaskHeal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* MemoryNode) {
	Super::ExecuteTask(OwnerComp, MemoryNode);

	return EBTNodeResult::Succeeded;
}
