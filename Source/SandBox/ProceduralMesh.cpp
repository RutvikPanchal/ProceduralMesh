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
	Mesh->SetMaterial(0, Material);
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

	switch (shape) {
	case 0:
		AngleStep = (90.f / (resolution - 1)) * PI / 180;

		// Calculate Vertices and Triangles from resolution in a Grid pattern
		for (int i = 0; i <= resolution; i++) {
			for (int j = 0; j <= resolution; j++) {
				Vertex.Set(i * scaleX / float(resolution) - (scaleX_div / 2.f), j * scaleY / float(resolution) - (scaleY_div / 2.f), 0.f);
				Vertices.Add(Vertex);
				VertexColors.Add(FLinearColor(FMath::FRandRange(0.f, 1.f), FMath::FRandRange(0.f, 1.f), FMath::FRandRange(0.f, 1.f)));

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
				Vertex.Set(i * scaleX / float(resolution) - (scaleX_div / 2.f), j * scaleY / float(resolution) - (scaleY_div / 2.f), 0.f);
				Vertices.Add(Vertex);
				VertexColors.Add(FLinearColor(FMath::FRandRange(0.f, 1.f), FMath::FRandRange(0.f, 1.f), FMath::FRandRange(0.f, 1.f)));

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

		// Calculate Vertices's Z value from Anglestep and Triangles from resolution in a Grid pattern and Stitch 2 hemispheres together
		for (int i = 0; i <= resolution; i++) {
			for (int j = 0; j <= resolution; j++) {
				for (int k = 0; k < resolution; k++) {
					if ((i == k || i == resolution - k) && (j >= k && j <= (resolution - k))) {
						Vertices[i * (resolution + 1) + j].Z = sin(AngleStep * k) * shapeScale + 1.f;
						Vertices[i * (resolution + 1) + j + ((resolution + 1) * (resolution + 1))].Z = (sin(AngleStep * k) * -shapeScale) - 1.f;

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
						Vertices[i * (resolution + 1) + j].Z = sin(AngleStep * k) * shapeScale + 1.f;
						Vertices[i * (resolution + 1) + j + ((resolution + 1) * (resolution + 1))].Z = (sin(AngleStep * k) * -shapeScale) - 1.f;

						if (k == 0 && i < resolution) {
							if (j == 0) {
								Triangles.Add(i * (resolution + 1) + j);
								Triangles.Add((i + 1) * (resolution + 1) + j + ((resolution + 1) * (resolution + 1)));
								Triangles.Add(i * (resolution + 1) + j + ((resolution + 1) * (resolution + 1)));

								Triangles.Add((i + 1) * (resolution + 1) + j);
								Triangles.Add((i + 1) * (resolution + 1) + j + ((resolution + 1) * (resolution + 1)));
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
		break;

		case 1:
			// Calculate Vertices and Triangles from resolution in a Grid pattern
			for (int i = 0; i <= resolution; i++) {
				for (int j = 0; j <= resolution; j++) {
					Vertex.Set(i * scaleX / float(resolution) - (scaleX_div / 2.f), j * scaleY / float(resolution) - (scaleY_div / 2.f), 0.f);
					Vertices.Add(Vertex);
					VertexColors.Add(FLinearColor(FMath::FRandRange(0.f, 1.f), FMath::FRandRange(0.f, 1.f), FMath::FRandRange(0.f, 1.f)));

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
			DeleteTris(Subdivision_Position_X, Subdivision_Position_Y);
			break;

	case 2:
		// Calculate Vertices and Triangles from resolution in a Grid pattern
		for (int i = 0; i <= resolution; i++) {
			for (int j = 0; j <= resolution; j++) {
				Vertex.Set(FMath::RandRange(-50.f, 50.f), FMath::RandRange(-50.f, 50.f), 0.f);
				Vertices.Add(Vertex);
				VertexColors.Add(FLinearColor(FMath::FRandRange(0.f, 1.f), FMath::FRandRange(0.f, 1.f), FMath::FRandRange(0.f, 1.f)));
			}
		}

		break;
	default:
		break;
	}

	// Create Mesh
	Mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), VertexColors, TArray<FProcMeshTangent>(), true);
	GeneratePerlinNoise();
}

void AProceduralMesh::ClearArrays()
{
	Vertex.Set(0.f, 0.f, 0.f);
	Noise.Empty();
	Points.Empty();
	Vertices.Empty();
	Triangles.Empty();
	VertexColors.Empty();
}

void AProceduralMesh::UpdateMesh() {
	if (Vertices.Num() != 0) {
		for (int i = 0; i < Vertices.Num(); i++) {
			switch (shape) {
			case 0:
				Vertices[i].Normalize();
				if (Vertices.Num() <= Noise.Num()) {
					Vertices[i] *= (shapeScale - (Noise[i]));
				}
				else {
					Vertices[i] *= (shapeScale);
				}
				break;
			case 1:
				if (Vertices.Num() <= Noise.Num()) {
					Vertices[i] *= (shapeScale / 50);
					Vertices[i].Z -= Noise[i];
				}
				else {
					Vertices[i] *= (shapeScale / 50);
				}
				break;
			default:
				Vertices[i] *= (shapeScale / 50);
				break;
			}
		}

		// Update the Mesh
		Mesh->UpdateMeshSection_LinearColor(0, Vertices, TArray<FVector>(), TArray<FVector2D>(), VertexColors, TArray<FProcMeshTangent>());
	}
}

void AProceduralMesh::GeneratePerlinNoise() {
	FVector2D Point;

	float distance;
	float minDistance;
	float maxDistance = sqrt((resolution * resolution) + (resolution * resolution));

	FRandomStream* Seeder = new FRandomStream(Seed);

	// Noise Points Generation and Positioning
	for (int i = 0; i < NoisePoints; i++) {
		Point.X = Seeder->FRand() * resolution;
		Point.Y = Seeder->FRand() * resolution;
		Points.Add(Point);
	}

	// Noise Array Generation
	for (int l = 0; l < (Vertices.Num() / ((resolution + 1) * (resolution + 1))); l++) {
		for (int i = 0; i <= resolution; i++) {
			for (int j = 0; j <= resolution; j++) {
				minDistance = maxDistance;
				for (int k = 0; k < NoisePoints; k++) {
					distance = sqrt((j - Points[k].X) * (j - Points[k].X) + (i - Points[k].Y) * (i - Points[k].Y));
					if (distance < minDistance) {
						minDistance = distance;
					}
				}
				float NoiseVertexVal = FMath::GetMappedRangeValueClamped(FVector2D(0.f, maxDistance), FVector2D(0.f, 0.2f), minDistance);
				VertexColors[(i * (resolution + 1) + j)] = NoiseAdditionFactor_00 * FLinearColor(NoiseVertexVal, NoiseVertexVal, NoiseVertexVal);
				Noise.Add(NoiseAdditionFactor_00 * FMath::GetMappedRangeValueClamped(FVector2D(0.f, maxDistance), FVector2D(0.f, NoiseScale), minDistance));
			}
		}
	}
	for (int i = resolution * resolution; i < Vertices.Num(); i++) {

	}

	Points.Empty();
	// Noise Points Generation and Positioning
	for (int i = 0; i < NoisePoints*3; i++) {
		Point.X = Seeder->FRand() * resolution;
		Point.Y = Seeder->FRand() * resolution;
		Points.Add(Point);
	}

	maxDistance = sqrt((resolution * resolution) + (resolution * resolution));

	// Noise Array Generation
	for (int l = 0; l < (Vertices.Num() / ((resolution + 1) * (resolution + 1))); l++) {
		for (int i = 0; i <= resolution; i++) {
			for (int j = 0; j <= resolution; j++) {
				minDistance = maxDistance;
				for (int k = 0; k < NoisePoints*3; k++) {
					distance = sqrt((j - Points[k].X) * (j - Points[k].X) + (i - Points[k].Y) * (i - Points[k].Y));
					if (distance < minDistance) {
						minDistance = distance;
					}
				}
				float NoiseVertexVal = FMath::GetMappedRangeValueClamped(FVector2D(0.f, maxDistance), FVector2D(0.f, 0.2f), minDistance);
				VertexColors[(i * (resolution + 1) + j)] += NoiseAdditionFactor_01 * FLinearColor(NoiseVertexVal, NoiseVertexVal, NoiseVertexVal);
				Noise[i * (resolution + 1) + j] += NoiseAdditionFactor_01 * (FMath::GetMappedRangeValueClamped(FVector2D(0.f, maxDistance), FVector2D(0.f, NoiseScale), minDistance));
			}
		}
	}

	Points.Empty();
	// Noise Points Generation and Positioning
	for (int i = 0; i < NoisePoints * 10; i++) {
		Point.X = Seeder->FRand() * resolution;
		Point.Y = Seeder->FRand() * resolution;
		Points.Add(Point);
	}

	maxDistance = sqrt((resolution * resolution) + (resolution * resolution));

	// Noise Array Generation
	for (int l = 0; l < (Vertices.Num() / ((resolution + 1) * (resolution + 1))); l++) {
		for (int i = 0; i <= resolution; i++) {
			for (int j = 0; j <= resolution; j++) {
				minDistance = maxDistance;
				for (int k = 0; k < NoisePoints * 10; k++) {
					distance = sqrt((j - Points[k].X) * (j - Points[k].X) + (i - Points[k].Y) * (i - Points[k].Y));
					if (distance < minDistance) {
						minDistance = distance;
					}
				}
				float NoiseVertexVal = FMath::GetMappedRangeValueClamped(FVector2D(0.f, maxDistance), FVector2D(0.f, 0.2f), minDistance);
				VertexColors[(i * (resolution + 1) + j)] += NoiseAdditionFactor_02 * FLinearColor(NoiseVertexVal, NoiseVertexVal, NoiseVertexVal);
				Noise[i * (resolution + 1) + j] += NoiseAdditionFactor_02 * (FMath::GetMappedRangeValueClamped(FVector2D(0.f, maxDistance), FVector2D(0.f, NoiseScale), minDistance));
			}
		}
	}

	delete Seeder;
}

void AProceduralMesh::DeleteTris(int32 X, int32 Y) {
	if (X < resolution && Y < resolution && X >= 0 && Y >= 0) {
		Triangles.RemoveAt((X * (resolution) + Y) * 6, 6, true);
		AddSubDPoints(X, Y, Subdivision_Position_Lvl);
	}
}

void AProceduralMesh::AddSubDPoints(int32 X, int32 Y, int32 SubD)
{
	for (int i = 0; i <= SubD + 1; i++) {
		for (int j = 0; j <= SubD + 1; j++) {
			//if (i > 0 && i < SubD + 1) {
				Vertex.Set((X + (i / float(SubD + 1))) * scaleX / float(resolution) - (scaleX_div / 2.f), (Y + (j / float(SubD + 1))) * scaleY / float(resolution) - (scaleY_div / 2.f), 0.f);
				Vertices.Add(Vertex);

				if (i < SubD + 1 && j < SubD + 1) {
					Triangles.Add(i * (SubD + 2) + j + ((resolution + 1) * (resolution + 1)));
					Triangles.Add(i * (SubD + 2) + (j + 1) + ((resolution + 1) * (resolution + 1)));
					Triangles.Add((i + 1) * (SubD + 2) + j + ((resolution + 1) * (resolution + 1)));

					Triangles.Add(i * (SubD + 2) + (j + 1) + ((resolution + 1) * (resolution + 1)));
					Triangles.Add((i + 1) * (SubD + 2) + (j + 1) + ((resolution + 1) * (resolution + 1)));
					Triangles.Add((i + 1) * (SubD + 2) + j + ((resolution + 1) * (resolution + 1)));
				}
			//}
			//else {
				//if (j > 0 && j < SubD + 1) {
					//Vertex.Set((X + (i / float(SubD + 1))) * scaleX / float(resolution) - (scaleX_div / 2.f), (Y + (j / float(SubD + 1))) * scaleY / float(resolution) - (scaleY_div / 2.f), 0.f);
					//Vertices.Add(Vertex);
				//}
			//}
		}
	}
}