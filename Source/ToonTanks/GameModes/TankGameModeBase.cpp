// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GamePlayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors); //Static class means we are not asking for
	//Object, rather it will give us UClass of APawnTurret

	return TurretActors.Num();
}

void ATankGameModeBase::HandleGameStart()
{
	TargetTurrets = GetTargetTurretCount();

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();

	if (PlayerControllerRef) {
		PlayerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
			&APlayerControllerBase::SetPlayerEnabledState, true);//setting other class's function to timer
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerRef) {
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)){
		DestroyedTurret->HandleDestruction();
		TargetTurrets -= 1;
		if (TargetTurrets == 0) {
			HandleGameOver(true);
		}
	}
}

// Called when the game starts or when spawned
void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}