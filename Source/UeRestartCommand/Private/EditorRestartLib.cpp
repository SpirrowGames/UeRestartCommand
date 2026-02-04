// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorRestartLib.h"
#include "FileHelpers.h"
#include "UnrealEdMisc.h"
#include "ILiveCodingModule.h"
#include "HAL/PlatformMisc.h"


bool UEditorRestartLib::SaveAllDirtyPackages()
{
	// Save all dirty packages (maps and content)
	const bool bSuccess = FEditorFileUtils::SaveDirtyPackages(
		false,  // bPromptUserToSave
		true,   // bSaveMapPackages
		true,   // bSaveContentPackages
		true,   // bFastSave
		false,  // bNotifyNoPackagesSaved
		false   // bCanBeDeclined
	);

	return bSuccess;
}

void UEditorRestartLib::ExitEditor()
{
	FPlatformMisc::RequestExit(false);
}

void UEditorRestartLib::RestartEditor()
{
	FUnrealEdMisc::Get().RestartEditor(false);
}

void UEditorRestartLib::SaveAndExitEditor()
{
	SaveAllDirtyPackages();
	ExitEditor();
}

void UEditorRestartLib::SaveAndRestartEditor()
{
	SaveAllDirtyPackages();
	RestartEditor();
}

bool UEditorRestartLib::CompileLiveCoding()
{
	ILiveCodingModule* LiveCodingModule = FModuleManager::GetModulePtr<ILiveCodingModule>("LiveCoding");

	if (!LiveCodingModule)
	{
		UE_LOG(LogTemp, Warning, TEXT("Live Coding module is not available"));
		return false;
	}

	if (!LiveCodingModule->IsEnabledForSession())
	{
		UE_LOG(LogTemp, Warning, TEXT("Live Coding is not enabled for this session"));
		return false;
	}

	LiveCodingModule->Compile(ELiveCodingCompileFlags::None, nullptr);

	UE_LOG(LogTemp, Log, TEXT("Live Coding compilation started"));
	return true;
}
