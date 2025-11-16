// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/LCoreFunctions.h"

#include "ShaderPipelineCache.h"

int32 ULCoreFunctions::NumPrecompilePSORemaining()
{
	return (int32)FShaderPipelineCache::NumPrecompilesRemaining();
}

void ULCoreFunctions::ClearPSOCache()
{
	FString LocalAppDataFolder = FPlatformMisc::GetEnvironmentVariable(TEXT("LOCALAPPDATA"));
		if (!LocalAppDataFolder.IsEmpty())
		{
			auto ClearFolder = [](const FString& PSOPath, const TCHAR* Extension)
				{
					TArray<FString> Files;
					IFileManager& FileManager = IFileManager::Get();
					FileManager.FindFiles(Files, *PSOPath, Extension);
					for (FString& File : Files)
					{
						FString FilePath = FString::Printf(L"%s\\%s", *PSOPath, *File);
						FileManager.Delete(*FilePath, /*RequireExists*/ false, /*EvenReadOnly*/ true, /*Quiet*/ true);
					}
				};

			if (IsRHIDeviceNVIDIA())
			{
				// NVIDIA used to have a global cache, but now also has a per-driver cache in a different folder in LocalLow.
				FString GlobalPSOPath = FPaths::Combine(*LocalAppDataFolder, TEXT("NVIDIA"), TEXT("DXCache"));
				ClearFolder(GlobalPSOPath, nullptr);

				FString PerDriverPSOPath = FPaths::Combine(*LocalAppDataFolder, TEXT(".."), TEXT("LocalLow"), TEXT("NVIDIA"), TEXT("PerDriverVersion"), TEXT("DXCache"));
				ClearFolder(PerDriverPSOPath, nullptr);

				UE_LOG(LogTemp, Display, TEXT("Successfully clear NVIDIA PSO Cache Data"))
			}
			else if (IsRHIDeviceAMD())
			{
				FString PSOPath = FPaths::Combine(*LocalAppDataFolder, TEXT("AMD"), TEXT("DxCache"));
				ClearFolder(PSOPath, nullptr);

				PSOPath = FPaths::Combine(*LocalAppDataFolder, TEXT("AMD"), TEXT("DxcCache"));
				ClearFolder(PSOPath, nullptr);

				PSOPath = FPaths::Combine(*LocalAppDataFolder, TEXT(".."), TEXT("LocalLow"), TEXT("AMD"), TEXT("DxCache"));
				ClearFolder(PSOPath, nullptr);

				PSOPath = FPaths::Combine(*LocalAppDataFolder, TEXT(".."), TEXT("LocalLow"), TEXT("AMD"), TEXT("DxcCache"));
				ClearFolder(PSOPath, nullptr);

				UE_LOG(LogTemp, Display, TEXT("Successfully clear AMD PSO Cache Data"))
			}
			else if (IsRHIDeviceIntel())
			{
				// Intel stores the cache in LocalLow.
				FString PSOPath = FPaths::Combine(*LocalAppDataFolder, TEXT(".."), TEXT("LocalLow"), TEXT("Intel"), TEXT("ShaderCache"));
				ClearFolder(PSOPath, nullptr);

				UE_LOG(LogTemp, Display, TEXT("Successfully clear INTEL PSO Cache Data"))
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("clearPSODriverCache failed: please ensure that LOCALAPPDATA points to C:\\Users\\<username>\\AppData\\Local"));
		}
}
