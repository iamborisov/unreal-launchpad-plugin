#include "LaunchpadEngineSubsystem.h"
#include "MIDIDeviceManager.h"
#include "Kismet/KismetMathLibrary.h"

void ULaunchpadEngineSubsystem::RegisterComponent(ULaunchpadComponent* Component)
{
	//UE_LOG(LogCore, Warning, TEXT("RegisterComponent %s"), Component->ID);
	
	if (LaunchpadComponents.Contains(Component))
	{
		return;
	}

	RegisterInputController(Component->InputDeviceID);
	RegisterOutputController(Component->OutputDeviceID);
	
	LaunchpadComponents.AddUnique(Component);
}

void ULaunchpadEngineSubsystem::UnregisterComponent(ULaunchpadComponent* Component)
{
	//UE_LOG(LogCore, Warning, TEXT("UnregisterComponent"));
	
	if (!LaunchpadComponents.Contains(Component))
	{
		return;
	}

	LaunchpadComponents.Remove(Component);

	UnregisterInputController(Component->InputDeviceID);
	UnregisterOutputController(Component->OutputDeviceID);
}

void ULaunchpadEngineSubsystem::Shutdown()
{
	InputControllers.Empty();
	OutputControllers.Empty();
	LaunchpadComponents.Empty();
}

void ULaunchpadEngineSubsystem::RegisterInputController(int DeviceID)
{
	if (InputControllers.Contains(DeviceID))
	{
		return;
	}
	
	auto InputController = UMIDIDeviceManager::CreateMIDIDeviceInputController(DeviceID);
	if (!InputController)
	{
		return;
	}
	
	InputController->OnMIDINoteOn.AddDynamic(this, &ULaunchpadEngineSubsystem::OnMIDINoteOn);
    InputController->OnMIDINoteOff.AddDynamic(this, &ULaunchpadEngineSubsystem::OnMIDINoteOff);
    InputController->OnMIDIControlChange.AddDynamic(this, &ULaunchpadEngineSubsystem::OnMIDIControlChange);

    InputControllers.Add(DeviceID, InputController);
}

void ULaunchpadEngineSubsystem::UnregisterInputController(int DeviceID)
{
	if (!InputControllers.Contains(DeviceID))
	{
		return;
	}

	bool bCanRemove = true;
	for (auto Component : LaunchpadComponents)
	{
		if (!Component.IsValid())
		{
			continue;			
		}
		
		if (Component->InputDeviceID == DeviceID)
		{
			bCanRemove = false;
		}
	}

	if (!bCanRemove)
	{
		return;
	}

	InputControllers[DeviceID]->OnMIDINoteOn.RemoveAll(this);
	InputControllers[DeviceID]->OnMIDINoteOff.RemoveAll(this);
	InputControllers[DeviceID]->OnMIDIControlChange.RemoveAll(this);
	InputControllers[DeviceID]->ShutdownDevice();
	InputControllers[DeviceID]->MarkAsGarbage();
	InputControllers[DeviceID] = nullptr;

	InputControllers.Remove(DeviceID);
}

void ULaunchpadEngineSubsystem::OnMIDINoteOn(UMIDIDeviceInputController* MIDIDeviceController, int32 Timestamp, int32 Channel, int32 Note, int32 Velocity)
{
	auto DeviceID = InputControllers.FindKey(MIDIDeviceController);
	if (DeviceID == nullptr)
	{
		return;
	}
	
	for (auto Component : LaunchpadComponents)
	{
		if (!Component.IsValid())
		{
			continue;			
		}
		
		if (Component->InputDeviceID == *DeviceID && (Component->Channel == -1 || Component->Channel == Channel) && Component->ID == Note)
		{
			Component->Value = UKismetMathLibrary::NormalizeToRange(Velocity, 0, 127);
			Component->Trigger();
		}
	}
}
	
void ULaunchpadEngineSubsystem::OnMIDINoteOff(UMIDIDeviceInputController* MIDIDeviceController, int32 Timestamp, int32 Channel, int32 Note, int32 Velocity)
{
	auto DeviceID = InputControllers.FindKey(MIDIDeviceController);
	if (DeviceID == nullptr)
	{
		return;
	}
	
	for (auto Component : LaunchpadComponents)
	{
		if (!Component.IsValid())
		{
			continue;			
		}
		
		if (Component->InputDeviceID == *DeviceID && (Component->Channel == -1 || Component->Channel == Channel) && Component->ID == Note)
		{
			Component->Value = 0;
			Component->Trigger();
		}
	}
}
	
void ULaunchpadEngineSubsystem::OnMIDIControlChange(UMIDIDeviceInputController* MIDIDeviceController, int32 Timestamp, int32 Channel, int32 Type, int32 Value)
{
	auto DeviceID = InputControllers.FindKey(MIDIDeviceController);
	if (DeviceID == nullptr)
	{
		return;
	}
	
	for (auto Component : LaunchpadComponents)
	{
		if (!Component.IsValid())
		{
			continue;			
		}
		
		if (Component->InputDeviceID == *DeviceID && (Component->Channel == -1 || Component->Channel == Channel) && Component->ID == Type)
		{
			Component->Value = UKismetMathLibrary::NormalizeToRange(Value, 0, 127);
			Component->Trigger();
		}
	}
}

void ULaunchpadEngineSubsystem::RegisterOutputController(int DeviceID)
{
	
}

void ULaunchpadEngineSubsystem::UnregisterOutputController(int DeviceID)
{
	
}