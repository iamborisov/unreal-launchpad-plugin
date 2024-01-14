// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LaunchpadComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLaunchpadTrigger, class ULaunchpadComponent*, Component, float, Value);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LAUNCHPAD_API ULaunchpadComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULaunchpadComponent();

	UFUNCTION()
	void OnComponentActivateHandler(UActorComponent* Component, bool bReset);

	UFUNCTION()
	void OnComponentDeactivateHandler(UActorComponent* Component);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MIDI")
	int InputDeviceID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MIDI")
	int OutputDeviceID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MIDI")
	int ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MIDI")
	int Channel = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MIDI", Interp)
	float Value;

	UFUNCTION(BlueprintCallable, CallInEditor, Category="MIDI")
	void Trigger();

	UPROPERTY(BlueprintAssignable)
	FOnLaunchpadTrigger OnTrigger;
};
