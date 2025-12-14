// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ActionRoguelikeTarget : TargetRules
{
	public ActionRoguelikeTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		ExtraModuleNames.AddRange( new string[] { "ActionRoguelike" } );
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
        CppStandard = CppStandardVersion.Cpp20;
    }
}
