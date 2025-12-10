// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/Public/WeaponSystem/WeaponMaster.h"
#include "Particles/ParticleSystem.h"

UWeaponMaster::UWeaponMaster()
{
    
}

void UWeaponMaster::BeginPlay()
{
    Super::BeginPlay();
}

void UWeaponMaster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

