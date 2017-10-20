// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Voxel : ModuleRules
{
    private string ModulePath {
        get { return ModuleDirectory;  }
    }

    private string ThirdPartyPath {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

	public Voxel(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "ProceduralMeshComponent" });

        string fastNoiseSIMDPath = Path.Combine(ThirdPartyPath, "FastNoiseSIMD", "Libraries");
        PublicAdditionalLibraries.Add(Path.Combine(fastNoiseSIMDPath, "FastNoiseSIMD.lib"));
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "FastNoiseSIMD", "Includes"));
	}
}
