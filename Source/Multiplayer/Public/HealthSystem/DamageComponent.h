// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Multiplayer/Public/Structs_Enums/DamageInfo.h"
#include "DamageComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBlocked, bool, bCanBeParried);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageResponse, EDamageResponse, DamageResponse);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class MULTIPLAYER_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDamageComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health)
		float Health = MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsInvincible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsInterruptable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsBlocking = false;

	UPROPERTY(BlueprintAssignable)
		FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable)
		FOnBlocked OnBlocked;

	UPROPERTY(BlueprintAssignable)
		FOnDamageResponse OnDamageResponse;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
		float Heal(float Amount);

	UFUNCTION(BlueprintCallable)
		bool TakeDamage(FDamageInfo DamageInfo);

	enum class ECanBeDamaged : uint8 {
		BlockDamage,
		DoDamage,
		NoDamage
	};
	ECanBeDamaged CanBeDamaged(bool bShouldDamageInvincible, bool bCanBeBlocked);

	UFUNCTION()
	void OnRep_Health();

};
