// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

using UnrealBuildTool;
using System.Collections.Generic;

public class EndlessRunnerEditorTarget : TargetRules
{
	public EndlessRunnerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("EndlessRunner");
	}
}
