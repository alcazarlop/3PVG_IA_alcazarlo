#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ESH_HUD.generated.h"

UCLASS()
class ESATSURVIVALHORROR_API AESH_HUD : public AHUD {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD Settings")
	FLinearColor DragColor;

protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	UPROPERTY()
	class AESH_PlayerController* PlayerControllerReference;

};
