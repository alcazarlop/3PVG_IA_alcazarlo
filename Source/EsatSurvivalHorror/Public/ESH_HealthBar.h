#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ESH_HealthBar.generated.h"

UCLASS()
class ESATSURVIVALHORROR_API UESH_HealthBar : public UUserWidget {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthBar;

	UFUNCTION()
	void SetHealthValue(int32 NewValue, int32 MaxValue);
	
};
