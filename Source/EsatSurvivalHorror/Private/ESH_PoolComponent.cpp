#include "ESH_PoolComponent.h"
#include "ESH_Bullet.h"

UESH_PoolComponent::UESH_PoolComponent() {
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UESH_PoolComponent::BeginPlay() {
	Super::BeginPlay();

	for (int i = 0; i < PoolSize; ++i) {
		AESH_Bullet* NewBullet = GetWorld()->SpawnActor<AESH_Bullet>(BullterBlueprint);
		NewBullet->SetActorEnableCollision(false);
		NewBullet->SetActorHiddenInGame(true);
		BulletPool.Add(NewBullet);
	}
}

AESH_Bullet* UESH_PoolComponent::GetFromPool() {
	for (auto bullet : BulletPool) {
		if (bullet->IsHidden()) {
			bullet->SetActorEnableCollision(true);
			bullet->SetActorHiddenInGame(false);
			return bullet;
		}
	}
	return nullptr;
}

