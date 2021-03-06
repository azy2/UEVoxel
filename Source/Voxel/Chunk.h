// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "MeshData.h"
#include "Block.h"
#include "SettingsManager.h"
#include "Chunk.generated.h"

UCLASS()
class VOXEL_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();
	~AChunk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	UPROPERTY()
	FIntVector pos;
	UPROPERTY()
	class AWorldManager* worldManager;
	FBlock* blocks[USettingsManager::chunkSize][USettingsManager::chunkSize][USettingsManager::chunkSize];
	static bool inRange(int index);
	static bool inRange(FIntVector v);
	FBlock* getBlock(FIntVector pos);
	void setBlock(FIntVector pos, FBlock *block);
	void destroyBlock(FIntVector pos);
	void updateChunk();
	void renderMesh(FMeshData* meshData, FMeshData* waterData);
	void needsUpdate();
	bool isRendered();
private:
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* mesh;
	UPROPERTY()
	bool _needsUpdate;
	UPROPERTY()
	bool rendered;
	UPROPERTY()
	UMaterial* blockMat;
	UPROPERTY()
	UMaterial* waterMat;
};
