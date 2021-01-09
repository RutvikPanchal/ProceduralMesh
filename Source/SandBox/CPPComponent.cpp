#include "CPPComponent.h"

UCPPComponent::UCPPComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCPPComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld();
	FString ActorLocation = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Display, TEXT("Location is %s"), *ActorLocation)
}

void UCPPComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}