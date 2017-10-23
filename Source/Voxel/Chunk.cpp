#include "Chunk.h"
#include "BlockAir.h"
#include "BlockStone.h"
#include "BlockGrass.h"
#include "WorldManager.h"
#include "ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AChunk::AChunk()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_needsUpdate = false;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	mesh->bUseAsyncCooking = true;
	RootComponent = mesh;
	static ConstructorHelpers::FObjectFinder<UMaterial> BlockMaterial(TEXT("/Game/BlockMaterial"));
	if (BlockMaterial.Succeeded()) {
		blockMat = BlockMaterial.Object;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Can't find BlockMaterial"))
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> WaterMaterial(TEXT("/Game/StarterContent/Materials/M_Water_Lake"));
	if (WaterMaterial.Succeeded()) {
		//waterMat = UMaterialInstanceDynamic::Create(WaterMaterial.Object, mesh);
		waterMat = WaterMaterial.Object;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Can't find WaterMaterial"))
	}
}

void AChunk::PostInitializeComponents() {
	Super::PostInitializeComponents();
	mesh->SetMaterial(0, blockMat);
	mesh->SetMaterial(1, waterMat);
}

AChunk::~AChunk() {
	for (int x = 0; x < USettingsManager::chunkSize; x++) {
		for (int y = 0; y < USettingsManager::chunkSize; y++) {
			for (int z = 0; z < USettingsManager::chunkSize; z++) {
				if (blocks[x][y][z] != NULL) {
					delete blocks[x][y][z];
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_needsUpdate) {
		updateChunk();
	}
}

void AChunk::needsUpdate() {
	_needsUpdate = true;
}

bool AChunk::isRendered() {
	return rendered;
}

bool AChunk::inRange(int index) {
	return (index >= 0 && index < USettingsManager::chunkSize);
}

bool AChunk::inRange(FIntVector v) {
	return (inRange(v.X) && inRange(v.Y) && inRange(v.Z));
}

FBlock *AChunk::getBlock(FIntVector pos) {
	return (inRange(pos) ? blocks[pos.X][pos.Y][pos.Z] : worldManager->getBlock(pos + this->pos));
}

void AChunk::setBlock(FIntVector pos, FBlock *block) {
	if (inRange(pos)) {
		blocks[pos.X][pos.Y][pos.Z] = block;
	}
	else {
		worldManager->setBlock(pos, block);
	}
}

void AChunk::destroyBlock(FIntVector pos) {
	if (blocks[pos.X][pos.Y][pos.Z] != NULL) {
		delete blocks[pos.X][pos.Y][pos.Z];
		blocks[pos.X][pos.Y][pos.Z] = new FBlockAir();
	}
}

void AChunk::updateChunk() {
	_needsUpdate = false;
	rendered = true;
	FMeshData meshData;
	FMeshData waterData;
	for (int x = 0; x < USettingsManager::chunkSize; x++) {
		for (int y = 0; y < USettingsManager::chunkSize; y++) {
			for (int z = 0; z < USettingsManager::chunkSize; z++) {
				if (blocks[x][y][z] != NULL) {
					//if (blocks[x][y][z]->isWater()) {
					//	blocks[x][y][z]->blockData(this, FIntVector(x, y, z), &waterData);
					//}
					//else {
						blocks[x][y][z]->blockData(this, FIntVector(x, y, z), &meshData);
					//}
				}
				else {
					UE_LOG(LogTemp, Error, TEXT("Missing block"));
				}
			}
		}
	}
	renderMesh(&meshData, &waterData);
}

void AChunk::renderMesh(FMeshData* meshData, FMeshData* waterData) {
	mesh->CreateMeshSection_LinearColor(0, meshData->vertices, meshData->triangles, TArray<FVector>(), meshData->UVs, TArray<FLinearColor>(), TArray<FProcMeshTangent>(), true);
	// mesh->CreateMeshSection_LinearColor(1, waterData->vertices, waterData->triangles, TArray<FVector>(), waterData->UVs, TArray<FLinearColor>(), TArray<FProcMeshTangent>(), false);
}

