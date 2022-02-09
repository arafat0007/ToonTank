// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectionHandler.h"

bool UReflectionHandler::MethodExist(AActor* ActorToInspect, FString MethodNameToSearch) {

	//if parameter actor is nullptr, stop processing
	if (ActorToInspect == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Actor To Inspect can not be null"));
		return false;
	}

	FString EventNamePrefix;
	FString EventNameSuffix;
	FString MethodName;

	bool HaveMethod = false;

	for (TFieldIterator<UFunction> Func(ActorToInspect->GetClass()); Func; ++Func) {

		//Only for event dispatcher searching, Func->GetName() returns EventName+__DelegateSignature;
		//after spliting, EventNamePrefix = EventName
		//for function and custom event, there is no need for spliting
		MethodName = Func->GetName();
		MethodName.Split(TEXT("_"), &EventNamePrefix, &EventNameSuffix);

		if (Func->HasAnyFunctionFlags(FUNC_BlueprintEvent) && Func->HasAnyFunctionFlags(FUNC_BlueprintCallable) && ((EventNamePrefix == MethodNameToSearch) || (MethodName == MethodNameToSearch))) {
			HaveMethod = true;
			break;
		}
	}

	return HaveMethod;
}