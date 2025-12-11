// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/Public/Characters/BaseCharacter.h"
#include "Multiplayer/Public/WeaponSystem/WeaponMaster.h"
#include "Multiplayer/Public/HealthSystem/DamageComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetFieldOfView(90.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	Camera->SetupAttachment(CameraBoom, FName("SpringEndpoint"));

	DamageSystem = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageSystem"));
	DamageSystem->SetIsReplicated(true);
	DamageSystem->OnDeath.AddDynamic(this, &ABaseCharacter::Death);
	DamageSystem->OnDamageResponse.AddDynamic(this, &ABaseCharacter::DamageResponse);
	
	CurrentWeapon = CreateDefaultSubobject<UWeaponMaster>(TEXT("CurrentWeapon"));
	CurrentWeapon->SetupAttachment(GetMesh(), FName("WeaponSocket"));
	CurrentWeapon->SetIsReplicated(true);

	Weapons.Init(nullptr, 2);

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(DamageSystem){

	}
	if(!IsLocallyControlled()){
		GetMesh()->SetMaterial(0, CharacterMeshMaterials[0]);
		GetMesh()->SetMaterial(1, CharacterMeshMaterials[1]);
	}else{
		GetMesh()->SetMaterial(0, CharacterMeshMaterials[2]);
		GetMesh()->SetMaterial(1, CharacterMeshMaterials[3]);
	}

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveFront", this, &ABaseCharacter::MoveFront);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &ABaseCharacter::LookRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCharacter::Jump);	

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABaseCharacter::Server_StartAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ABaseCharacter::Server_StopAttack);
}

void ABaseCharacter::MoveFront(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ABaseCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ABaseCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * V_Sensitivity);
}

void ABaseCharacter::LookRight(float Value)
{
	AddControllerYawInput(Value * H_Sensitivity);
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, CurrentWeapon);
	DOREPLIFETIME(ABaseCharacter, DamageSystem);
}

float ABaseCharacter::GetCurrentHealth_Implementation()
{
    return DamageSystem->Health;
}

float ABaseCharacter::GetMaxHealth_Implementation()
{
    return DamageSystem->MaxHealth;
}

float ABaseCharacter::Heal_Implementation(float Amount)
{
	return DamageSystem->Heal(Amount);
}

bool ABaseCharacter::TakeDamage_Implementation(FDamageInfo DamageInfo)
{
	return DamageSystem->TakeDamage(DamageInfo);
}

void ABaseCharacter::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("DEAD"), 0);
}

void ABaseCharacter::DamageResponse(EDamageResponse DamageResponse)
{
	UE_LOG(LogTemp, Warning, TEXT("RESPONSE"), 0);
}

void ABaseCharacter::Fire()
{
	FCollisionQueryParams Params;
	Params.bTraceComplex = true;
	Params.AddIgnoredActor(this);
	//DrawDebugLine(GetWorld(), CurrentWeapon->GetSocketLocation(FName("Muzzle")), CurrentWeapon->GetSocketLocation(FName("Muzzle")) + Camera->GetForwardVector() * CurrentWeapon->Range, FColor::Red, false, 2.f, 2, 3.f);
	if(GetWorld()->LineTraceSingleByChannel(FireHitResult, CurrentWeapon->GetSocketLocation(FName("Muzzle")), CurrentWeapon->GetSocketLocation(FName("Muzzle")) + Camera->GetForwardVector() * CurrentWeapon->Range, ECollisionChannel::ECC_Visibility)){
		AActor* HitActor = FireHitResult.GetActor();
		if(HitActor){
			Multicast_FireEFX(FireHitResult.Location, UKismetMathLibrary::MakeRotFromX(FireHitResult.ImpactNormal), HitActor);
			if(HitActor->GetClass()->ImplementsInterface(UDamageInterface::StaticClass())){
				FDamageInfo Info;
				Info.Amount = CurrentWeapon->Damage;
				IDamageInterface::Execute_TakeDamage(HitActor, Info);
			}
		}
	}
}

void ABaseCharacter::Multicast_FireEFX_Implementation(const FVector& Location, const FRotator& Rotation, AActor* HitActor)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CurrentWeapon->HitEFX, FTransform(Rotation, Location));
}

void ABaseCharacter::Server_StartAttack_Implementation()
{
	GetWorldTimerManager().SetTimer(FireHandle, this, &ABaseCharacter::Fire, 0.1f, true);
}

void ABaseCharacter::Server_StopAttack_Implementation()
{
	GetWorldTimerManager().ClearTimer(FireHandle);
	FireHandle.Invalidate();
}