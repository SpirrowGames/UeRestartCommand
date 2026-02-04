// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EditorRestartLib.generated.h"

/**
 * Blueprint Function Library for Unreal Editor restart and save operations.
 * Provides functions to save, exit, restart the Editor, and hot reload code.
 */
UCLASS()
class UERESTARTCOMMAND_API UEditorRestartLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Saves all dirty packages (maps and content).
	 */
	UFUNCTION(BlueprintCallable, Category = "Editor|Restart")
	static bool SaveAllDirtyPackages();

	/**
	 * Exits the Unreal Editor (without restarting).
	 */
	UFUNCTION(BlueprintCallable, Category = "Editor|Restart")
	static void ExitEditor();

	/**
	 * Restarts the Unreal Editor.
	 */
	UFUNCTION(BlueprintCallable, Category = "Editor|Restart")
	static void RestartEditor();

	/**
	 * Saves all dirty packages and then exits the Unreal Editor.
	 */
	UFUNCTION(BlueprintCallable, Category = "Editor|Restart")
	static void SaveAndExitEditor();

	/**
	 * Saves all dirty packages and then restarts the Unreal Editor.
	 */
	UFUNCTION(BlueprintCallable, Category = "Editor|Restart")
	static void SaveAndRestartEditor();

	/**
	 * Compiles and hot reloads code using Live Coding.
	 * Note: Live Coding has limitations (e.g., cannot handle header changes, new classes).
	 * Returns true if Live Coding is available and compilation started.
	 */
	UFUNCTION(BlueprintCallable, Category = "Editor|Restart")
	static bool CompileLiveCoding();
};
