// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CK2025_Summer_Team1 : ModuleRules
{
	public CK2025_Summer_Team1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"PhysicsCore",
			"SlateCore",
			"LevelSequence",
			"Niagara",
			"NiagaraAnimNotifies",
			"AdvancedWidgets",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			
		});

		PublicIncludePaths.AddRange(new string[] {
			"CK2025_Summer_Team1"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
