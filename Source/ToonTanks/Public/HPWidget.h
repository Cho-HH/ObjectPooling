// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UHPWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	//class UProgressBar* GetHPBar() const;

	void SetPercent(float percecnt);
private:
	UPROPERTY()
	class UProgressBar* mHPBar;
};
