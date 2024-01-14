#pragma once

#include "CoreMinimal.h"
#include "LaunchpadComponent.h"
#include "Subsystems/EngineSubsystem.h"
#include "MIDIDeviceInputController.h"
#include "MIDIDeviceOutputController.h"
#include "LaunchpadEngineSubsystem.generated.h"

UCLASS(Blueprintable)
class LAUNCHPAD_API ULaunchpadEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterComponent(ULaunchpadComponent* Component);

	UFUNCTION(BlueprintCallable)
	void UnregisterComponent(ULaunchpadComponent* Component);

	void Shutdown();
	
private:
	UPROPERTY()
	TArray<TSoftObjectPtr<ULaunchpadComponent>> LaunchpadComponents;
	
	UPROPERTY()
	TMap<int, UMIDIDeviceInputController*> InputControllers;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void RegisterInputController(int DeviceID);

	UFUNCTION(BlueprintCallable, CallInEditor)
	void UnregisterInputController(int DeviceID);

	UFUNCTION(BlueprintCallable, CallInEditor)
	void OnMIDINoteOn(UMIDIDeviceInputController* MIDIDeviceController, int32 Timestamp, int32 Channel, int32 Note, int32 Velocity);
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void OnMIDINoteOff(UMIDIDeviceInputController* MIDIDeviceController, int32 Timestamp, int32 Channel, int32 Note, int32 Velocity);
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void OnMIDIControlChange(UMIDIDeviceInputController* MIDIDeviceController, int32 Timestamp, int32 Channel, int32 Type, int32 Value);
	
	UPROPERTY()
	TMap<int, UMIDIDeviceOutputController*> OutputControllers;
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void RegisterOutputController(int DeviceID);

	UFUNCTION(BlueprintCallable, CallInEditor)
	void UnregisterOutputController(int DeviceID);
};


