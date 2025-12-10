// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageInfo.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8 {
	None,
	Melee,
	Projectile,
	Explosion,
	Environmental
};

UENUM(BlueprintType)
enum class EDamageResponse : uint8 {
	None,
	HitReaction,
	Stagger,
	Stun,
	Knockback
};

USTRUCT(BlueprintType)
struct FDamageInfo {
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EDamageResponse DamageResponse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bShouldDamageInvincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanBeBlocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanBeParried;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bShouldForceInterrupt;

	FDamageInfo() : Amount(0.f), DamageType(EDamageType::None), DamageResponse(EDamageResponse::None), bShouldDamageInvincible(false), bCanBeBlocked(false), bCanBeParried(false), bShouldForceInterrupt(false) {}
};

