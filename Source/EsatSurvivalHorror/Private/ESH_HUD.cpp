#include "ESH_HUD.h"
#include "ESH_PlayerController.h"
#include "ESH_Character.h"


void AESH_HUD::BeginPlay() {
	Super::BeginPlay();
	PlayerControllerReference = Cast<AESH_PlayerController>(GetOwningPlayerController());
}

void AESH_HUD::DrawHUD() {
	Super::DrawHUD();

	AESH_UnitController* UC = PlayerControllerReference->GetUnitController();

	if (PlayerControllerReference->GetUnitController()->bIsSelecting) {
		FVector2D FinalMouseScreenPosition;
		FinalMouseScreenPosition.X = UC->CurrentMouseScreenPosition.X - UC->InitialMouseScreenPosition.X;
		FinalMouseScreenPosition.Y = UC->CurrentMouseScreenPosition.Y - UC->InitialMouseScreenPosition.Y;
		DrawRect(DragColor, UC->InitialMouseScreenPosition.X, UC->InitialMouseScreenPosition.Y, FinalMouseScreenPosition.X, FinalMouseScreenPosition.Y);

		TArray<AESH_Character*> FilterArray;
		GetActorsInSelectionRectangle<AESH_Character>(UC->InitialMouseScreenPosition, UC->CurrentMouseScreenPosition, FilterArray);

		for (AESH_Character* unit : FilterArray) {
			if (!UC->SelectedUnits.Contains(unit)) {
				UC->SelectedUnits.Add(unit);
			}
		}

		FilterArray.Empty();
		PlayerControllerReference->GetUnitController()->bIsSelecting = false;
	}

}