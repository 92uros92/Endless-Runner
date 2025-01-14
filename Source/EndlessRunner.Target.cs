// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

using UnrealBuildTool;
using System.Collections.Generic;

public class EndlessRunnerTarget : TargetRules
{
	public EndlessRunnerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("EndlessRunner");
	}
}
