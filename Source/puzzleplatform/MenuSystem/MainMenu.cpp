// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Button.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuSystem/ServerRow.h"
#include "WidgetSwitcher.h"
#include "EditableTextBox.h"
#include "Components/TextBlock.h"

UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;

	ServerRowClass = ServerRowBPClass.Class;
}

void UMainMenu::SetServerList(TArray<FServerData> ServerNames)
{
	UWorld* World = this->GetWorld();
	if(!ensure(World != nullptr)) return;

	ServerList->ClearChildren();
	uint32 i = 0;

	for (const FServerData& ServerData : ServerNames)
	{
		if (!ensure(ServerRowClass != nullptr)) return;
		UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
		if (!ensure(Row != nullptr)) return;
		Row->ServerName->SetText(FText::FromString(ServerData.Name));
		Row->HostUser->SetText(FText::FromString(ServerData.HostUsername));
		FString FractionText = FString::Printf(TEXT("%d/%d"), ServerData.CurrentPlayers, ServerData.MaxPlayers);
		Row->ConnectionFrackion->SetText(FText::FromString(FractionText));
		Row->Setup(this, i);
		++i;
		ServerList->AddChild(Row);
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if(!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	if (!ensure(ConfirmButton != nullptr)) return false;
	ConfirmButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	if (!ensure(ExitButton != nullptr)) return false;
	ExitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);
	return true;
}


void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}


void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr))
	{
		return;
	}
	if (!ensure(JoinMenu != nullptr))
	{
		return;
	}
	MenuSwitcher->SetActiveWidget(JoinMenu);
	if (MenuInterface != nullptr)
	{
		MenuInterface->RefreshServerList();
	}
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr))
	{
		return;
	}
	if (!ensure(MainMenu != nullptr))
	{
		return;
	}
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{
	if (SelectedIndex.IsSet() && MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Select Index %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Select Index not set"));
	}

}

void UMainMenu::QuitGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

void UMainMenu::UpdateChildren()
{
	for (int32 i = 0; i < ServerList->GetChildrenCount(); i++)
	{
		UServerRow* Row = Cast<UServerRow>(ServerList->GetChildAt(i));
		if (Row != nullptr)
		{
			Row->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}
