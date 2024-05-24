#include "ESH_HealthBar.h"
#include "Components/ProgressBar.h"

void UESH_HealthBar::SetHealthValue(int32 NewValue, int32 MaxValue) {
	HealthBar->SetPercent((float)NewValue / (float)MaxValue);
}

