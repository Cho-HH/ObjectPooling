// Fill out your copyright notice in the Description page of Project Settings.


#include "HPWidget.h"
#include "Components/ProgressBar.h"

void UHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	mHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
}

void UHPWidget::SetPercent(float percecnt)
{ 
	if (mHPBar != nullptr)
	{
		mHPBar->SetPercent(percecnt);
	}
}
