#pragma once

#include "CoreMinimal.h"
#include "Class.h"
#include "MeshData.generated.h"

USTRUCT()
struct VOXEL_API FMeshData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	TArray<FVector> vertices;
	UPROPERTY()
	TArray<int> triangles;
	UPROPERTY()
	TArray<FVector2D> UVs;
	UPROPERTY()
	TArray<FVector> colVertices;
	UPROPERTY()
	TArray<int> colTriangles;
	UPROPERTY()
	bool useRenderDataForCol;

	void addQuadTriangles();
	void addTriangle(int tri);
	void addVertex(FVector v);

};
