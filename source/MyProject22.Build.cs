// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProject22 : ModuleRules
{
	public MyProject22(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
