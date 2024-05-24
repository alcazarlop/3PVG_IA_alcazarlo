#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputActionValue.h"
#include "ESH_Camera.generated.h"

UCLASS()
class ESATSURVIVALHORROR_API AESH_Camera : public AActor {
	GENERATED_BODY()
	
public:	
	AESH_Camera();

	void MoveCamera(const FInputActionValue& value);
	void RotateCamera(const FInputActionValue& value);
	void ZoomCamera(const FInputActionValue& value);

private:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Air Camera Settings")
	float AirCameraSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Air Camera Settings")
	float AirCameraRotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Air Camera Settings")
	float AirCameraZoomSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Air Camera Settings")
	float MinZoomDst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Air Camera Settings")
	float MaxZoomDst;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Attributes")
	class USpringArmComponent* CameraBoon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Attributes")
	class UCameraComponent* AirCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Attributes")
	class USceneComponent* AnchorPoint;

};
