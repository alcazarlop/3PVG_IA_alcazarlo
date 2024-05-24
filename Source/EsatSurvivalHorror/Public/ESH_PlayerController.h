#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "ESH_UnitController.h"
#include "ESH_PlayerController.generated.h"

UCLASS()
class ESATSURVIVALHORROR_API AESH_PlayerController : public APlayerController {
	GENERATED_BODY()

public:
	FORCEINLINE AESH_UnitController* GetUnitController() { return UnitControllerReference;  }

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	class AESH_Camera* CameraReference;

	UPROPERTY()
	class AESH_UnitController* UnitControllerReference;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Air Camera Settings")
	TSubclassOf<class AESH_Camera> CameraBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Air Camera Settings")
	TSubclassOf<AESH_UnitController> UnitControllerBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Input Settings")
	class UInputMappingContext* ControlMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Input Settings")
	class UInputAction* IA_MoveCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Input Settings")
	class UInputAction* IA_RotateCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Input Settings")
	class UInputAction* IA_ZoomCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Input Settings")
	class UInputAction* IA_MoveAndAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Input Settings")
	class UInputAction* IA_StartSelection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Input Settings")
	class UInputAction* IA_Selection;

};
