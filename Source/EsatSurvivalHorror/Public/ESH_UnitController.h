#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputActionValue.h"
#include "ESH_UnitController.generated.h"

UCLASS()
class ESATSURVIVALHORROR_API AESH_UnitController : public AActor {
	GENERATED_BODY()
	
public:	
	AESH_UnitController();

	void MoveAndAttack(const FInputActionValue& Value);
	void StartSelection(const FInputActionValue& Value);
	void Selection(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, Category = "Unit Control")
	TArray<class AESH_Character*> SelectedUnits;

	FVector2D InitialMouseScreenPosition;
	FVector2D CurrentMouseScreenPosition;
	bool bIsSelecting;

protected:
	virtual void BeginPlay() override;

private:	

	UPROPERTY()
	class AESH_PlayerController* PlayerControllerReference;

};
