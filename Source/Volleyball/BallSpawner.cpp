// Fill out your copyright notice in the Description page of Project Settings.


#include "BallSpawner.h"
#include "BallBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "VolleyCharacter.h"

void ABallSpawner::BeginPlay()
{
    if (HasAuthority())
    {
        SR_SpawnBall();
    }
}

void ABallSpawner::SR_SpawnBall_Implementation()
{
    ABallBase* SpawnedBall;
    SpawnedBall = Cast<ABallBase>(UGameplayStatics::GetActorOfClass(this, Ball));
    if (SpawnedBall)
    {
        SpawnedBall->Destroy();
    }
    SpawnedBall = GetWorld()->SpawnActor<ABallBase>(Ball, GetActorTransform());
    UStaticMeshComponent* MeshBall = Cast<UStaticMeshComponent>(SpawnedBall->GetRootComponent());
    //FreezeBall(MeshBall);
    LaunchBall(MeshBall);
}

void ABallSpawner::LaunchBall(UStaticMeshComponent* Mesh)
{
    UnfreezeBall(Mesh);

    TArray<AActor*> PlayerLocations;
    UGameplayStatics::GetAllActorsOfClass(this, AVolleyCharacter::StaticClass(), PlayerLocations);

    if (PlayerLocations.IsEmpty()) return;

    int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, PlayerLocations.Num()-1);

    FVector PlayerPosition;
    FRotator PlayerRotation;
    PlayerLocations[RandomIndex]->GetActorEyesViewPoint(PlayerPosition, PlayerRotation);

    FVector Direction;
    UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), Direction, GetActorLocation(), PlayerPosition, {}, 0.75);
    Mesh->AddImpulse(Direction * Impulse);

    //if start of the game
        //Launch ball in random team direction
    //else
        //Launch ball towards last scored team
}

void ABallSpawner::FreezeBall(UStaticMeshComponent* Mesh)
{
    Mesh->SetSimulatePhysics(false);
}

void ABallSpawner::UnfreezeBall(UStaticMeshComponent* Mesh)
{
    Mesh->SetSimulatePhysics(true);
}
