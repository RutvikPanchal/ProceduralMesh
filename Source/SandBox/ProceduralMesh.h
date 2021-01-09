#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"

#include "SceneView.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

#include "ProceduralMesh.generated.h" // always put .generated files last
#define OUT

UCLASS()
class SANDBOX_API AProceduralMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	// Mesh Object with Triangles and Vertices
	UProceduralMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	int32 resolution = 4;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	float scale = 100.f;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	float radius = 100.f;

	float AngleStep;
	FVector Vertex;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<float> Noise;

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	void UpdateMesh();

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	void CreateMesh();

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	void ClearArrays();

	UPROPERTY(VisibleAnywhere, Category = "Tick")
	float TickCounter = 0.f;

	UPROPERTY(EditAnywhere, Category = "Tick")
	float TickIterator = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Tick")
	float TickRange = 180.f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};