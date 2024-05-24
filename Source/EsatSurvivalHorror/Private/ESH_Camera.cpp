#include "ESH_Camera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


AESH_Camera::AESH_Camera() {
	AirCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Air Camera"));
	CameraBoon = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boon"));
	AnchorPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Anchor"));

	RootComponent = AnchorPoint;
	AirCamera->SetupAttachment(CameraBoon);
	CameraBoon->SetupAttachment(RootComponent);

	CameraBoon->TargetArmLength = 1000.0f;
	CameraBoon->bDoCollisionTest = false;

	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = true;

	SetActorHiddenInGame(true);
}

void AESH_Camera::MoveCamera(const FInputActionValue& Value) {
	FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetActorRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddActorWorldOffset(MovementVector.Y * ForwardDirection * AirCameraSpeed * GetWorld()->GetDeltaSeconds());
	AddActorWorldOffset(MovementVector.X * RightDirection * AirCameraSpeed * GetWorld()->GetDeltaSeconds());
}

void AESH_Camera::RotateCamera(const FInputActionValue& Value) {
	float Rotation = Value.Get<float>();
	const FRotator Rotator(0.0f, GetActorRotation().GetComponentForAxis(EAxis::Y) - Rotation * AirCameraRotationSpeed * GetWorld()->GetDeltaSeconds(), 0.0f);
	AddActorLocalRotation(Rotator);
}

void AESH_Camera::ZoomCamera(const FInputActionValue& Value) {
	float Zoom = Value.Get<float>();
	CameraBoon->TargetArmLength = FMath::Clamp(CameraBoon->TargetArmLength - Zoom * AirCameraZoomSpeed * GetWorld()->GetDeltaSeconds(), MinZoomDst, MaxZoomDst);
}
