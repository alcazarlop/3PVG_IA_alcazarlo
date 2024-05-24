#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ESH_Bullet.generated.h"

UCLASS()
class ESATSURVIVALHORROR_API AESH_Bullet : public AActor {
	GENERATED_BODY()
	
public:	
	AESH_Bullet();

	UPROPERTY(VisibleAnywhere, Category = "CustomMesh")
	class UStaticMeshComponent* BulletMesh;

	class AESH_Character* OwnerActor;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type) override;

private:
	UFUNCTION()
	void OnBeginOverlap(AActor* Self, AActor* Other);
};
