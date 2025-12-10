// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponMaster.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MULTIPLAYER_API UWeaponMaster : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:

	UWeaponMaster();
	
protected:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_WeaponData")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_WeaponData")
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_WeaponData")
	int32 MagMaxCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_WeaponData")
	int32 MagCurrentCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_WeaponData")
	class UParticleSystem* HitEFX;

	
};
