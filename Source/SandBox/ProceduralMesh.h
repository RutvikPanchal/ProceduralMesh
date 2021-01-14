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

	UPROPERTY(EditAnywhere, Category = "Shape", meta = (ClampMin = "0", ClampMax = "2", UIMin = "0", UIMax = "2"))
	int32 shape = 0;

	// Mesh Variables
	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (UIMin = "2"))
	int32 resolution = 4;
	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (UIMin = "0"))
	float shapeScale = 100.f;
	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (UIMin = "0"))
	float scaleX = 100.f;
	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (UIMin = "0"))
	float scaleY = 100.f;
	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (UIMin = "0"))
	float scaleX_div = 100.f;
	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (UIMin = "0"))
	float scaleY_div = 100.f;

	float AngleStep;
	FVector Vertex;

	//UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TArray<FVector> Vertices;
	//UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TArray<int32> Triangles;

	// Noise Variables
	TArray<float> Noise;
	UPROPERTY(EditAnywhere, Category = "Noise", meta = (UIMin = "0"))
	float NoiseScale = 0.f;
	UPROPERTY(EditAnywhere, Category = "Noise", meta = (UIMin = "0"))
	int32 NoisePoints = 4;
	UPROPERTY(EditAnywhere, Category = "Noise", meta = (UIMin = "0"))
	int32 Seed = 0;
	TArray<FVector2D> Points;

	void GeneratePerlinNoise();

	// Mesh Functions
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	void UpdateMesh();
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	void CreateMesh();
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	void ClearArrays();

	// Tick Variables
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