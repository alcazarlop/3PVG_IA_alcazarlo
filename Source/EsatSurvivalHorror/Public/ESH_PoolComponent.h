#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ESH_PoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESATSURVIVALHORROR_API UESH_PoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UESH_PoolComponent();

	class AESH_Bullet* GetFromPool();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Pool Object")
	TSubclassOf<class AESH_Bullet> BullterBlueprint;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Pool Object")
	int32 PoolSize;

	TArray<class AESH_Bullet*> BulletPool;

};
