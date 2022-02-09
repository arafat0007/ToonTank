// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReflectionHandler.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UReflectionHandler : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Search for method existance in Actor class and return result */
	UFUNCTION(BlueprintCallable, Category = "ReflectionHandling | MethodExist")
		static bool MethodExist(AActor* ActorToInspect, FString MethodNameToSearch);
};
