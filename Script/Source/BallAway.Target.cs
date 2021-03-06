// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BallAwayTarget : TargetRules
{
	public BallAwayTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "BallAway" } );

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            ExtraModuleNames.Add("OnlineSubsystemGooglePlay");
            ExtraModuleNames.Add("OnlineSubsystem");
            ExtraModuleNames.Add("AndroidAdvertising");
        }
    }

}

