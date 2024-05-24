#include "ESH_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "ESH_Character.h"


AESH_AIController::AESH_AIController() {
	AI_BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree"));
	AI_Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));

	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightSense"));

	PerceptionComp->ConfigureSense(*SightSense);
	PerceptionComp->SetDominantSense(SightSense->GetSenseImplementation());

	FAISenseID DominantSense = PerceptionComp->GetDominantSenseID();
	UAISenseConfig* SenseConfig = PerceptionComp->GetSenseConfig(DominantSense);
	UAISenseConfig_Sight* SightConfig = Cast< UAISenseConfig_Sight>(SenseConfig);
	SightConfig->SightRadius = 800.0f;
	SightConfig->LoseSightRadius = 1000.0f;

	RootComponent->AddRelativeLocation(FVector(-100000.0f, -100000.0f, -100000.0f));

	PrimaryActorTick.bCanEverTick = true;
}


void AESH_AIController::BeginPlay() {
	Super::BeginPlay();
	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AESH_AIController::OnPerceptionUpdated);
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(GetWorld(), UAISense_Sight::StaticClass(), this);
}

void AESH_AIController::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	PerceptionComp->OnTargetPerceptionUpdated.RemoveDynamic(this, &AESH_AIController::OnPerceptionUpdated);
}

void AESH_AIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	AESH_Character* BaseUnit = Cast<AESH_Character>(InPawn);
	if (BaseUnit->IsValidLowLevel()) {
		if (nullptr != BaseUnit->UnitBehaviorTree && BaseUnit->UnitBehaviorTree->BlackboardAsset) {
			AI_Blackboard->InitializeBlackboard(*BaseUnit->UnitBehaviorTree->BlackboardAsset);
			BaseUnit->UnitBlackboard = AI_Blackboard;
			PossessedPawn = BaseUnit;
		}
		AI_BehaviorTree->StartTree(*BaseUnit->UnitBehaviorTree);
	}
}

void AESH_AIController::OnUnPossess() {
	Super::OnUnPossess();

	AI_BehaviorTree->StopTree();
}

ETeamAttitude::Type AESH_AIController::GetTeamAttitudeTowards(const AActor& Other) const {
	const AESH_Character* OtherPawn = Cast<AESH_Character>(&Other);
	if (OtherPawn) {
		if (OtherPawn->ID == PossessedPawn->ID) {
			return ETeamAttitude::Friendly; 
		}
	}
	return ETeamAttitude::Hostile;
}

FGenericTeamId AESH_AIController::GetGenericTeamId() const {
	return TeamId;
}


void AESH_AIController::OnPerceptionUpdated(AActor* actor, FAIStimulus stimulus) {
	if (PossessedPawn->IsBot) {
		if (stimulus.WasSuccessfullySensed()) {
			AESH_Character* Target = Cast<AESH_Character>(actor);
			if (Target) {
				AI_Blackboard->SetValueAsObject("TargetActor", Target);
				AI_Blackboard->SetValueAsBool("IsAwayFromTarget", false);
			}
		}
	}
	else {
		if (stimulus.WasSuccessfullySensed()) {
			AESH_Character* Target = Cast<AESH_Character>(actor);
			if (Target) {
				if (AI_Blackboard->GetValueAsBool("ForceMove")) {
					AI_Blackboard->SetValueAsObject("TargetActor", Target);
					return;
				}
				AI_Blackboard->SetValueAsBool("IsAwayFromTarget", false);
				AI_Blackboard->SetValueAsVector("NewLocation", PossessedPawn->GetActorLocation());
			}
		}
	}
}
