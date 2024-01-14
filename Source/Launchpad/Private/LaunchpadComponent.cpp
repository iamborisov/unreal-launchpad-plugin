#include "LaunchpadComponent.h"

#include "LaunchpadEngineSubsystem.h"

ULaunchpadComponent::ULaunchpadComponent()
{
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = false;

	OnComponentActivated.AddDynamic(this, &ULaunchpadComponent::OnComponentActivateHandler);
	OnComponentDeactivated.AddDynamic(this, &ULaunchpadComponent::OnComponentDeactivateHandler);
}

void ULaunchpadComponent::OnComponentActivateHandler(UActorComponent* Component, bool bReset)
{
	auto LaunchpadEngineSubsystem = GEngine->GetEngineSubsystem<ULaunchpadEngineSubsystem>();
	if (LaunchpadEngineSubsystem)
	{
		LaunchpadEngineSubsystem->RegisterComponent(Cast<ULaunchpadComponent>(Component));
	}
}

void ULaunchpadComponent::OnComponentDeactivateHandler(UActorComponent* Component)
{
	auto LaunchpadEngineSubsystem = GEngine->GetEngineSubsystem<ULaunchpadEngineSubsystem>();
	if (LaunchpadEngineSubsystem)
	{
		LaunchpadEngineSubsystem->UnregisterComponent(Cast<ULaunchpadComponent>(Component));
	}
}

void ULaunchpadComponent::Trigger()
{
	if (OnTrigger.IsBound())
	{
		OnTrigger.Broadcast(this, Value);
	}
}

