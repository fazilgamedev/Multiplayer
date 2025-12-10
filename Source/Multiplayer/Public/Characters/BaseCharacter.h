#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Multiplayer/Public/HealthSystem/Interfaces/DamageInterface.h"
#include "BaseCharacter.generated.h"

UCLASS()
class MULTIPLAYER_API ABaseCharacter : public ACharacter, public IDamageInterface
{
    GENERATED_BODY()

public:

    ABaseCharacter();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    class UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    class USpringArmComponent* CameraBoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float H_Sensitivity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float V_Sensitivity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
    class UDamageComponent* DamageSystem;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
    class UWeaponMaster* CurrentWeapon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<class UWeaponMaster*> Weapons;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bCanAttack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<class UMaterialInterface*> CharacterMeshMaterials;

protected:

    virtual void BeginPlay() override;

private:

    UPROPERTY()
    FTimerHandle FireHandle;

    UPROPERTY()
    FHitResult FireHitResult;

    //

	UFUNCTION()
	void MoveFront(float Value);
	
	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void LookUp(float Value);

	UFUNCTION()
	void LookRight(float Value);
    

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual float GetCurrentHealth_Implementation() override;
    virtual float GetMaxHealth_Implementation() override;
    virtual float Heal_Implementation(float Amount) override;
    virtual bool TakeDamage_Implementation(FDamageInfo DamageInfo) override;

	UFUNCTION()
	void Death();

	UFUNCTION()
	void DamageResponse(EDamageResponse DamageResponse);

    UFUNCTION()
    void Fire();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_FireEFX(const FVector& Location, const FRotator& Rotation, AActor* HitActor);
    void Multicast_FireEFX_Implementation(const FVector& Location, const FRotator& Rotation, AActor* HitActor);

    UFUNCTION(Server, Reliable)
    void Server_StartAttack();
    void Server_StartAttack_Implementation();

    UFUNCTION(Server, Reliable)
    void Server_StopAttack();
    void Server_StopAttack_Implementation();





};
