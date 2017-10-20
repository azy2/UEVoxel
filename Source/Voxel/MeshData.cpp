#include "MeshData.h"

void FMeshData::addQuadTriangles() {
	int num = vertices.Num();
	triangles.Add(num - 4);
	triangles.Add(num - 3);
	triangles.Add(num - 2);
	triangles.Add(num - 4);
	triangles.Add(num - 2);
	triangles.Add(num - 1);
	if (useRenderDataForCol) {
		int num = colVertices.Num();
		colTriangles.Add(num - 4);
		colTriangles.Add(num - 3);
		colTriangles.Add(num - 2);
		colTriangles.Add(num - 4);
		colTriangles.Add(num - 2);
		colTriangles.Add(num - 1);
	}
}

void FMeshData::addTriangle(int tri) {
	triangles.Add(tri);
	if (useRenderDataForCol) {
		colTriangles.Add(tri - vertices.Num() - colVertices.Num());
	}
}

void FMeshData::addVertex(FVector v) {
	vertices.Add(v);
	if (useRenderDataForCol) {
		colVertices.Add(v);
	}
}