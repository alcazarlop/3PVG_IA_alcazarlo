#include "ESH_UnitController.h"
#include "ESH_Character.h"
#include "ESH_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

AESH_UnitController::AESH_UnitController() {
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = true;

	SetActorHiddenInGame(true);
}

void AESH_UnitController::BeginPlay() {
	Super::BeginPlay();

	PlayerControllerReference = Cast<AESH_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
}

void AESH_UnitController::MoveAndAttack(const FInputActionValue& Value) {
	FHitResult Hit;
	PlayerControllerReference->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, true, Hit);
	if (!SelectedUnits.IsEmpty()) {
		AESH_Character* Target = Cast<AESH_Character>(Hit.GetActor());
		if (Target && Target->IsBot) {
			for (int i = 0; i < SelectedUnits.Num(); ++i) {
				SelectedUnits[i]->UnitBlackboard->SetValueAsObject("TargetActor", Hit.GetActor());
				float Distance = FVector::Distance(SelectedUnits[i]->GetActorLocation(), Target->GetActorLocation());
				if (Distance > 800.0f) {
					SelectedUnits[i]->UnitBlackboard->SetValueAsBool("IsAwayFromTarget", true);
					SelectedUnits[i]->UnitBlackboard->SetValueAsVector("NewLocation", Target->GetActorLocation());
					SelectedUnits[i]->UnitBlackboard->SetValueAsBool(TEXT("ForceMove"), true);
				}
			}
			return;
		}

		for (int i = 0; i < SelectedUnits.Num(); ++i) {
			SelectedUnits[i]->UnitBlackboard->SetValueAsVector(TEXT("NewLocation"), Hit.Location);
			SelectedUnits[i]->UnitBlackboard->SetValueAsBool(TEXT("ForceMove"), true);
		}
	}
}

void AESH_UnitController::StartSelection(const FInputActionValue& Value) {
	FHitResult Hit;
	PlayerControllerReference->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, Hit);
	PlayerControllerReference->GetMousePosition(InitialMouseScreenPosition.X, InitialMouseScreenPosition.Y);
	SelectedUnits.Empty();
	if (AESH_Character* Unit = Cast<AESH_Character>(Hit.GetActor())) {
		if (!SelectedUnits.Contains(Unit)) {
			SelectedUnits.Add(Unit);
		}
	}
}

void AESH_UnitController::Selection(const FInputActionValue& Value) {
	bIsSelecting = Value.Get<bool>();
	FHitResult Hit;
	PlayerControllerReference->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, Hit);
	PlayerControllerReference->GetMousePosition(CurrentMouseScreenPosition.X, CurrentMouseScreenPosition.Y);
}

