#include "ESH_Character.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIModule/Classes/Perception/AIPerceptionStimuliSourceComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EngineUtils.h"
#include "ESH_NavMesh.h"
#include "ESH_HealthBar.h"
#include "ESH_Bullet.h"
#include "ESH_AIController.h"


AESH_Character::AESH_Character() {
	Stimuli = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimuli Source"));
	SelectableBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Selectable Box"));
	SelectableBox->SetupAttachment(RootComponent);

	CharacterWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	CharacterWidget->SetupAttachment(RootComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 700.0f);

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AESH_Character::BeginPlay() {
	Super::BeginPlay();

	Weapon = GetWorld()->SpawnActor<AESH_Weapon>(WeaponBlueprint);
	Weapon->Attach(this);

	UUserWidget* WClass = CharacterWidget->GetWidget();
	HealthBar = Cast<UESH_HealthBar>(WClass);

	AIOwner = Cast<AESH_AIController>(UAIBlueprintHelperLibrary::GetAIController(this));
	
	for (TActorIterator<AESH_NavMesh> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		NavMesh = ActorItr->GetBounds().BoxExtent;
	}

	OnActorBeginOverlap.AddDynamic(this, &AESH_Character::OnBeginOverlap);
}

void AESH_Character::EndPlay(EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);

	OnActorBeginOverlap.RemoveDynamic(this, &AESH_Character::OnBeginOverlap);
}

void AESH_Character::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	AESH_Character* Target = Cast<AESH_Character>(UnitBlackboard->GetValueAsObject("TargetActor"));
	FVector GoalLocation = UnitBlackboard->GetValueAsVector("NewLocation");

	float Distance = FVector::Distance(GetActorLocation(), GoalLocation);

	if (Distance < 1.0f) {
		UnitBlackboard->SetValueAsBool("ForceMove", false);
	}

	if (Target) {
		float TargetDistance = FVector::Distance(GetActorLocation(), Target->GetActorLocation());
		if (TargetDistance < 800.0f) {
			GetCharacterMovement()->bOrientRotationToMovement = false;
			SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation()));
		} 
		else {
			GetCharacterMovement()->bOrientRotationToMovement = true;
		}

		if (IsBot && TargetDistance > 800.0f) {
			UnitBlackboard->SetValueAsBool("IsAwayFromTarget", true);
			FVector LastLocation = AIOwner->PerceptionComp->GetActorInfo(*Target)->GetLastStimulusLocation();
			UnitBlackboard->SetValueAsVector("NewLocation", LastLocation);
		}
	}

	if (IsBot && UnitBlackboard->GetValueAsBool("IsAwayFromTarget")) {
		float ChaseDistance = FVector::Distance(GetActorLocation(), UnitBlackboard->GetValueAsVector("NewLocation"));
		if (ChaseDistance < 50.0f) {
			UnitBlackboard->SetValueAsBool("IsAwayFromTarget", false);
			UnitBlackboard->SetValueAsObject("TargetActor", nullptr);
		}
	}
}

void AESH_Character::OnBeginOverlap(AActor* Self, AActor* Other) {
	AESH_Bullet* Bullet = Cast<AESH_Bullet>(Other);
	if (Bullet) {
		CurrentHealth -= Damage;
		if (CurrentHealth <= 0) {
			Weapon->Destroy();
			Destroy();
		}
		HealthBar->SetHealthValue(CurrentHealth, MaxHealth);
		/*Moral -= (int32)FMath::RandRange(10.0f, 10.0f);
		if (Moral <= 25) {
			UnitBlackboard->SetValueAsBool("IsFleeing", true);
		}*/
	}
}
