#include "ESH_Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "ESH_Character.h"

AESH_Bullet::AESH_Bullet() {
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	RootComponent = BulletMesh;
	BulletMesh->SetSimulatePhysics(true);

	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AESH_Bullet::BeginPlay() {
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AESH_Bullet::OnBeginOverlap);
}

void AESH_Bullet::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	OnActorBeginOverlap.RemoveDynamic(this, &AESH_Bullet::OnBeginOverlap);
}

void AESH_Bullet::OnBeginOverlap(AActor* SelfActor, AActor* OtherActor) {
	//SetActorHiddenInGame(true);
	//SetActorEnableCollision(false);
	
	AESH_Character* Target = Cast<AESH_Character>(OtherActor);
	if (Target) {
		AESH_Character* CurrentTarget = Cast<AESH_Character>(Target->UnitBlackboard->GetValueAsObject("TargetActor"));
		if (CurrentTarget) {
			Target->UnitBlackboard->SetValueAsObject("TargetActor", OwnerActor);
		}
	}

	Destroy();
}

