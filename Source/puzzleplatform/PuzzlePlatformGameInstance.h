// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();
	
	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& Address) override;

	UFUNCTION(Exec)
	virtual void LoadMainMenu() override;

private:
	TSubclassOf<UUserWidget> MenuClass;

	TSubclassOf<UUserWidget> InGameMenuClass;

	class UMainMenu* Menu;

	IOnlineSessionPtr SessionInterface;

	void OnCreateSessionComplete(FName SessionName, bool Success);
};
