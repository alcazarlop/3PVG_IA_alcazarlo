#include "ESH_Weapon.h"
#include "ESH_PoolComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ESH_Character.h"
#include "ESH_Bullet.h"

AESH_Weapon::AESH_Weapon() {
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	RootComponent = WeaponMesh;

	BulletPoolComponent = CreateDefaultSubobject<UESH_PoolComponent>(TEXT("Pool Comp"));

	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AESH_Weapon::Fire(FVector Direction) {
	AESH_Bullet* bullet = GetWorld()->SpawnActor<AESH_Bullet>(BulletBP);
	if (bullet) {
		bullet->OwnerActor = AttachedActor;
		bullet->SetActorLocation(WeaponMesh->GetSocketLocation(TEXT("WeaponSocket")));
		bullet->BulletMesh->AddImpulse(Direction * ImpulseForce);
	}
}

void AESH_Weapon::Attach(AESH_Character* Parent) {
	AttachedActor = Parent;
	AttachToComponent(Parent->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_rSocket"));
	AddActorLocalOffset(FVector(-28.0f, 6.0f, 8.0f));
	AddActorLocalRotation(FRotator(0.0f, 90.0f, 0.0f));
}

