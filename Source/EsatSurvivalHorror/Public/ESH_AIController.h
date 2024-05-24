#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "ESH_AIController.generated.h"

UCLASS()
class ESATSURVIVALHORROR_API AESH_AIController : public AAIController {
	GENERATED_BODY()
	
public:
	AESH_AIController();

	UPROPERTY(VisibleAnywhere, Category = "AI Settings")
	class UBehaviorTreeComponent* AI_BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = "AI Settings")
	UBlackboardComponent* AI_Blackboard;

	UPROPERTY(VisibleAnywhere, Category = "AI Settings")
	UAIPerceptionComponent* PerceptionComp;

	FGenericTeamId GetGenericTeamId() const override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* actor, FAIStimulus stimulus);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AI Settings")
	FGenericTeamId TeamId;

	class UAISenseConfig_Sight* SightSense;

	class AESH_Character* PossessedPawn;
};
