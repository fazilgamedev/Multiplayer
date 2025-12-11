// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/Public/UI/HealthBar.h"
#include "Multiplayer/Public/HealthSystem/Interfaces/DamageInterface.h"
#include "Components/ProgressBar.h"

float UHealthBar::GetHealthPercent()
{
    return GetOwningPlayerPawn()->GetClass()->ImplementsInterface(UDamageInterface::StaticClass()) ? IDamageInterface::Execute_GetCurrentHealth(GetOwningPlayerPawn()) / IDamageInterface::Execute_GetMaxHealth(GetOwningPlayerPawn()) : 0.f;
}
