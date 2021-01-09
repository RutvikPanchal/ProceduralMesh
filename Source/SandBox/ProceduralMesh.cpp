#include "ProceduralMesh.h"

// Sets default values
AProceduralMesh::AProceduralMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("MeshName");
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AProceduralMesh::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProceduralMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickCounter += TickIterator;
	if (TickCounter > TickRange) {
		TickCounter = 0;
	}
}

void AProceduralMesh::CreateMesh() {

	// Clear all Variables
	ClearArrays();

	AngleStep = (90.f / (resolution - 1)) * PI / 180;

	// Calculate Vertices and Triangles from resolution in a Grid pattern
	for (int i = 0; i <= resolution; i++) {
		for (int j = 0; j <= resolution; j++) {
			Vertex.Set(i * scaleX / float(resolution) - (scaleX / 2.f), j * scaleY / float(resolution) - (scaleY / 2.f), 0.f);
			Vertices.Add(Vertex);
			Noise.Add(FMath::FRandRange(0.f, NoiseScale));

			if (i < resolution && j < resolution) {
				Triangles.Add(i * (resolution + 1) + j);
				Triangles.Add(i * (resolution + 1) + (j + 1));
				Triangles.Add((i + 1) * (resolution + 1) + j);

				Triangles.Add(i * (resolution + 1) + (j + 1));
				Triangles.Add((i + 1) * (resolution + 1) + (j + 1));
				Triangles.Add((i + 1) * (resolution + 1) + j);
			}
		}
	}

	// Calculate Vertices and Triangles from resolution in a Grid pattern
	for (int i = 0; i <= resolution; i++) {
		for (int j = 0; j <= resolution; j++) {
			Vertex.Set(i * scaleX / float(resolution) - (scaleX / 2.f), j * scaleY / float(resolution) - (scaleY / 2.f), 0.f);
			Vertices.Add(Vertex);
			Noise.Add(FMath::FRandRange(0.f, NoiseScale));

			if (i < resolution && j < resolution) {
				Triangles.Add(i * (resolution + 1) + j + ((resolution + 1) * (resolution + 1)));
				Triangles.Add((i + 1) * (resolution + 1) + j + ((resolution + 1) * (resolution + 1)));
				Triangles.Add(i * (resolution + 1) + (j + 1) + ((resolution + 1) * (resolution + 1)));

				Triangles.Add(i * (resolution + 1) + (j + 1) + ((resolution + 1) * (resolution + 1)));
				Triangles.Add((i + 1) * (resolution + 1) + j + ((resolution + 1) * (resolution + 1)));
				Triangles.Add((i + 1) * (resolution + 1) + (j + 1) + ((resolution + 1) * (resolution + 1)));
			}
		}
	}

	// Calculate Vertices and Triangles from resolution in a Grid pattern and Stitch 2 hemispheres together
	for (int i = 0; i <= resolution; i++) {
		for (int j = 0; j <= resolution; j++) {
			for (int k = 0; k < resolution; k++) {
				if ((i == k || i == resolution - k) && (j >= k && j <= (resolution - k))) {
					Vertices[i * (resolution + 1) + j].Z = sin(AngleStep * k) * radius + 1.f;
					Vertices[i * (resolution + 1) + j + ((resolution + 1) * (resolution + 1))].Z = (sin(AngleStep * k) * -radius) - 1.f;

					if (k == 0 && j < resolution) {
						if (i == 0) {
							Triangles.Add(i * (resolution + 1) + j + ((resolution + 1) * (resolution + 1)));
							Triangles.Add(i * (resolution + 1) + (j + 1) + ((resolution + 1) * (resolution + 1)));
							Triangles.Add(i * (resolution + 1) + j);

							Triangles.Add(i * (resolution + 1) + j);
							Triangles.Add(i * (resolution + 1) + (j + 1) + ((resolution + 1) * (resolution + 1)));
							Triangles.Add(i * (resolution + 1) + (j + 1));
						}
						else {
							Triangles.Add(i * (resolution + 1) + j + ((resolution + 1) * (resolution + 1)));
							Triangles.Add(i * (resolution + 1) + j);
							Triangles.Add(i * (resolution + 1) + (j + 1) + ((resolution + 1) * (resolution + 1)));

							Triangles.Add(i * (resolution + 1) + j);
							Triangles.Add(i * (resolution + 1) + (j + 1));
							Triangles.Add(i * (resolution + 1) + (j + 1) + ((resolution + 1) * (resolution + 1)));
						}
					}
				}
				if ((j == k || j == resolution - k) && (i >= k && i <= (resolution - k))) {
					Vertices[i * (resolution + 1) + j].Z = sin(AngleStep * k) * radius + 1.f;
					Vertices[i * (resolution + 1) + j + ((resolution + 1) * (resolution + 1))].Z = (sin(AngleStep * k) * -radius) - 1.f;

					if (k == 0 && i < resolution) {
						if (j == 0) {
							Triangles.Add(i * (resolution + 1) + j);
							Triangles.Add((i + 1) * (resolution + 1) + j + ((resolution + 1) * (resolution + 1)));
							Triangles.Add(i * (resolution + 1) + j + ((resolution + 1) * (resolution + 1)));

							Triangles.Add((i + 1) * (resolution + 1) + j);
							Triangles.Add((i + 1) * (resolution + 1) + j +((resolution + 1) * (resolution + 1)));
							Triangles.Add(i * (resolution + 1) + j);
						}
						else {
							Triangles.Add((i + 1) * (resolution + 1) + j + ((resolution + 1) * (resolution + 1)));
							Triangles.Add(i * (resolution + 1) + j);
							Triangles.Add(i * (resolution + 1) + j + ((resolution + 1) * (resolution + 1)));

							Triangles.Add((i + 1) * (resolution + 1) + j + ((resolution + 1) * (resolution + 1)));
							Triangles.Add((i + 1) * (resolution + 1) + j);
							Triangles.Add(i * (resolution + 1) + j);
						}
					}
				}
			}
		}
	}

	// Normalize the vectors
	for (int i = 0; i < Vertices.Num(); i++) {
		Vertices[i].Normalize();
		Vertices[i] *= radius;
	}

	// Create Mesh
	Mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FLinearColor>(), TArray<FProcMeshTangent>(), true);
}

void AProceduralMesh::ClearArrays()
{
	Vertex.Set(0.f, 0.f, 0.f);
	Vertices.Empty();
	Triangles.Empty();
	Noise.Empty();
}

void AProceduralMesh::UpdateMesh() {
	if (Vertices.Num() != 0) {
		for (int i = 0; i < Vertices.Num(); i++) {
			Vertices[i].Normalize();
			Vertices[i] *= (radius + Noise[i]);
			//Vertices[i] *= (radius);
		}

		// Update the Mesh
		Mesh->UpdateMeshSection_LinearColor(0, Vertices, TArray<FVector>(), TArray<FVector2D>(), TArray<FLinearColor>(), TArray<FProcMeshTangent>());
	}
}

void AProceduralMesh::GeneratePerlinNoise() {

	//TArray<float> NoiseArray;
	//TArray<FVector2D> Points;

	//FVector2D Point;

	//Point.X = FMath::RandRange(0, resolution);
	//Point.Y = FMath::RandRange(0, resolution);
	//Points.Add(Point);

	//for (int i = 0; i < resolution; i++) {
	//	for (int j = 0; j < resolution; j++) {
	//		NoiseArray.Add(10.f);
	//	}
	//}
}