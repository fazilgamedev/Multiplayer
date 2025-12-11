// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABaseCharacter* CharacterRef;

	UPROPERTY()
	class UHealthBar* HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UHealthBar> HealthBarClass;

protected:

	virtual void BeginPlay() override;
	
	
	
};
