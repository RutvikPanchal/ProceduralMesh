// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SandBox : ModuleRules
{
	public SandBox(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
