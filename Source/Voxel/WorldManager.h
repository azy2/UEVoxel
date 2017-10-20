#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.h"
#include "Chunk.h"
#include "TerrainGen.h"
#include "WorldManager.generated.h"

UCLASS()
class VOXEL_API AWorldManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static const int worldHeight = 64;
	static const int columnHeight = worldHeight / AChunk::chunkSize;
	AChunk* getChunk(FIntVector pos);
	FBlock* getBlock(FIntVector pos);
	void setBlock(FIntVector pos, FBlock* block);
	void createChunk(FIntVector chunk);
	void destroyChunk(FIntVector pos);
	FIntVector floorToChunkSpace(FIntVector pos);
	UPROPERTY()
	TMap<FIntVector, AChunk*> chunks;
private:
	FTerrainGen terrainGen;
};
