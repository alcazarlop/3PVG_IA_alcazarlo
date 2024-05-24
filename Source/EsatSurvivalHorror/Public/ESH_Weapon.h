#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ESH_Weapon.generated.h"

UCLASS()
class ESATSURVIVALHORROR_API AESH_Weapon : public AActor {
	GENERATED_BODY()
	
public:	
	AESH_Weapon();

	void Fire(FVector Direction);
	void Attach(class AESH_Character*);

	UPROPERTY(EditAnywhere, Category = "Bullet Force")
	float ImpulseForce;

	UPROPERTY(EditAnywhere, Category = "Bullet Force")
	TSubclassOf<class AESH_Bullet> BulletBP;

private:	
	UPROPERTY(VisibleAnywhere, Category = "Weapon Mesh")
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Pool Comp")
	class UESH_PoolComponent* BulletPoolComponent;

	class AESH_Character* AttachedActor;

};
