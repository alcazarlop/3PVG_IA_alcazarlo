#include "ESH_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ESH_Camera.h"

void AESH_PlayerController::BeginPlay() {
	Super::BeginPlay();

	SetViewTargetWithBlend(CameraReference);

	bShowMouseCursor = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		Subsystem->AddMappingContext(ControlMappingContext, 0);
	}
}

void AESH_PlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	CameraReference = GetWorld()->SpawnActor<AESH_Camera>(CameraBlueprint);
	UnitControllerReference = GetWorld()->SpawnActor<AESH_UnitController>(UnitControllerBlueprint);

	EnableInput(this);
	if (UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		EIC->BindAction(IA_MoveCamera, ETriggerEvent::Triggered, CameraReference, &AESH_Camera::MoveCamera);
		EIC->BindAction(IA_RotateCamera, ETriggerEvent::Triggered, CameraReference, &AESH_Camera::RotateCamera);
		EIC->BindAction(IA_ZoomCamera, ETriggerEvent::Triggered, CameraReference, &AESH_Camera::ZoomCamera);
		
		EIC->BindAction(IA_MoveAndAttack, ETriggerEvent::Triggered, UnitControllerReference, &AESH_UnitController::MoveAndAttack);
		EIC->BindAction(IA_StartSelection, ETriggerEvent::Triggered, UnitControllerReference, &AESH_UnitController::StartSelection);
		EIC->BindAction(IA_Selection, ETriggerEvent::Triggered, UnitControllerReference, &AESH_UnitController::Selection);
	}
}