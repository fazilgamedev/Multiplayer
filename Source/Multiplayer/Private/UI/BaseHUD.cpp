// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/Public/UI/BaseHUD.h"
#include "Multiplayer/Public/Characters/BaseCharacter.h"
#include "Multiplayer/Public/UI/HealthBar.h"
#include "Blueprint/UserWidget.h"

void ABaseHUD::BeginPlay()
{
    Super::BeginPlay();

    CharacterRef = Cast<ABaseCharacter>(GetOwningPawn());

    if(!CharacterRef) return;

    HealthBar = CreateWidget<UHealthBar>(GetWorld(), HealthBarClass);
    HealthBar->AddToViewport(0);

}