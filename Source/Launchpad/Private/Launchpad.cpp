// Copyright Epic Games, Inc. All Rights Reserved.

#include "Launchpad.h"

#include "LaunchpadEngineSubsystem.h"

#define LOCTEXT_NAMESPACE "FLaunchpadModule"

void FLaunchpadModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FLaunchpadModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	// auto LaunchpadEngineSubsystem = GEngine->GetEngineSubsystem<ULaunchpadEngineSubsystem>();
	// if (LaunchpadEngineSubsystem)
	// {
	// 	LaunchpadEngineSubsystem->Shutdown();
	// }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLaunchpadModule, Launchpad)