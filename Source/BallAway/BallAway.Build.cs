// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class BallAway : ModuleRules
{
	public BallAway(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PrivateIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory,"Private")
		});

        PublicIncludePaths.AddRange(new string[]
		{
            Path.Combine(ModuleDirectory, "Public"),
            Path.Combine(ModuleDirectory, "Public/GameMode"),
			Path.Combine(ModuleDirectory, "Public/Obstacles"),
			Path.Combine(ModuleDirectory, "Public/PlayerCharacter"),
			Path.Combine(ModuleDirectory, "Public/Item"),
			Path.Combine(ModuleDirectory, "Public/UI")

		});

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
