#include "VoxelPlayerController.h"
#include "SettingsManager.h"
#include "Kismet/GameplayStatics.h"
#include "CollisionQueryParams.h"

void AVoxelPlayerController::BeginPlay() {
	TArray<AActor*> outActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldManager::StaticClass(), outActors);
	worldManager = (AWorldManager*)outActors[0];
}

void AVoxelPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	check(InputComponent);

	if (InputComponent != NULL) {
		InputComponent->BindAction("Click", IE_Pressed, this, &AVoxelPlayerController::OnClick);
	}
}

void AVoxelPlayerController::OnClick() {
	FCollisionQueryParams TraceParams(FName(TEXT("trace")), true, GetPawn());
	TraceParams.bTraceComplex = true;
	TraceParams.AddIgnoredActor(GetPawn());

	FHitResult hit = FHitResult(ForceInitToZero);

	FVector start = GetPawn()->GetPawnViewLocation();
	const FVector end = start + (GetControlRotation().Vector() * 10 * USettingsManager::voxelToUUFactor);

	//UE_LOG(LogTemp, Warning, TEXT("Start: %s, End: %s"), *start.ToString(), *end.ToString());
	GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, TraceParams, ECR_Block);

	if (hit.GetActor()) {
		//UE_LOG(LogTemp, Warning, TEXT("Hit something %f uu away."), hit.Distance);
		FVector hitLocation = FVector(hit.Location.X, hit.Location.Y, hit.Location.Z);
		hitLocation /= USettingsManager::voxelToUUFactor;
		UE_LOG(LogTemp, Warning, TEXT("Hit block at location %s"), *hitLocation.ToString());
		worldManager->destroyBlock(FIntVector(hitLocation.X, hitLocation.Y, hitLocation.Z));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No actor found"));
	}
}