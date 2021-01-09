#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPPComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SANDBOX_API UCPPComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCPPComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	AActor* TriggerVolume;
};