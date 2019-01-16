// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"
#include "Components/Button.h"
#include "MenuSystem/MainMenu.h"

void UServerRow::Setup(UMainMenu * Parent, uint32 Index)
{
	RowParent = Parent;
	RowIndex = Index;
	RowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);

}

void UServerRow::OnClicked()
{
	if(!ensure(RowParent != nullptr)) return;
	RowParent->SelectIndex(RowIndex);
}
