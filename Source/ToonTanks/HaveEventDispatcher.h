// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HaveEventDispatcher.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UHaveEventDispatcher : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static bool HaveEventDispacher(AActor* ActorToInspect, FString EventName);
};
