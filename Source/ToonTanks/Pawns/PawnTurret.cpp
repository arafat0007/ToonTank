// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GamePlayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	//set timer
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);//setting own class's function to timer

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0)); 
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}

	Super::RotateTurret(PlayerPawn->GetActorLocation());
} 

void APawnTurret::CheckFireCondition() {
	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive()) {
		return;
	}
	if (ReturnDistanceToPlayer() <= FireRange)
	{
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn) {
		return 0.0f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

void APawnTurret::HandleDestruction()
{
	//call base pawn class HandleDestruction to play effects
	Super::HandleDestruction();

	Destroy();
}