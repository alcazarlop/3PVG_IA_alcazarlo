#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ESH_Weapon.h"
#include "ESH_Character.generated.h"

UCLASS()
class ESATSURVIVALHORROR_API AESH_Character : public ACharacter, public IGenericTeamAgentInterface {
	GENERATED_BODY()

public:
	AESH_Character();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Settings")
	class UAIPerceptionStimuliSourceComponent* Stimuli;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class AESH_Weapon> WeaponBlueprint;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	AESH_Weapon* Weapon;

	UPROPERTY(EditAnywhere, Category = "AI Settings")
	UBehaviorTree* UnitBehaviorTree;

	UPROPERTY(EditAnywhere, Category = "AI Settings")
	UBlackboardComponent* UnitBlackboard;

	UPROPERTY(VisibleAnywhere, Category = "AI Settings")
	FVector NavMesh;

	UPROPERTY(EditAnywhere, Category = "UX Settings")
	class UWidgetComponent* CharacterWidget;

	UPROPERTY(EditAnywhere, Category = "AI Settings")
	uint8 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Stats")
	int32 MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Stats")
	int32 CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Stats")
	int32 Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Stats")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Stats")
	int32 Moral;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Stats")
	int32 HealAmount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Stats")
	bool IsBot;

	UPROPERTY(VisibleAnywhere, Category = "AI Settings")
	TArray<FVector> ShotPositions;

	float NextShoot;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "UX Settings")
	class UBoxComponent* SelectableBox;

	class UESH_HealthBar* HealthBar;
	class AESH_AIController* AIOwner;

	UFUNCTION()
	void OnBeginOverlap(AActor* Self, AActor* Other);

};
