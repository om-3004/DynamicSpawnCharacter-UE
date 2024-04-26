// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicPawnController.h"

ADynamicPawnController::ADynamicPawnController() : indexOfDataTable{ 0 } {

}

void ADynamicPawnController::Spawn() {

	if (GetPawn()) {
		GetPawn()->Destroy();
	}

	UDataTable* dataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Blueprint/PawnSelection.PawnSelection'"));
	if (dataTable) {
		TArray<FName> rowNames = dataTable->GetRowNames();

		if(rowNames.Num() == indexOfDataTable) {
			indexOfDataTable = 0;
		}

		FPawnDataTable* dataRow = dataTable->FindRow<FPawnDataTable>(rowNames[indexOfDataTable++], TEXT(""));

		UWorld* World = GetWorld();

		if(dataRow) {
			
			TSubclassOf<APawn> PawnReference = dataRow->PawnClass;
			//CurrentPawnType = dataRow->PawnType;

			if (World) {
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				FVector Location = { 50, 50, 200 };
				FRotator SpawnRotation = { 0, 0, 0 };

				if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
					Subsystem->ClearAllMappings();
				}
				

				APawn* SpawnedPawn = World->SpawnActor<APawn>(PawnReference, Location, SpawnRotation, SpawnParams);

				SetupInputComponent();

				if (SpawnedPawn) {
					Possess(SpawnedPawn);
					if (dataRow->PawnType == EPawnType::TopDown) {
						bShowMouseCursor = true;
						DefaultMouseCursor = EMouseCursor::GrabHand;
					}
				}
			}
		}


	}

}

void ADynamicPawnController::BeginPlay()
{
	Super::BeginPlay();
	Spawn();
}

void ADynamicPawnController::SetupInputComponent() {
	Super::SetupInputComponent();

	UInputMappingContext* InputMappingContext = NewObject<UInputMappingContext>();

	UInputAction* TogglePawn = NewObject<UInputAction>();
	TogglePawn->ValueType = EInputActionValueType::Boolean;

	InputMappingContext->MapKey(TogglePawn, EKeys::P);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(TogglePawn, ETriggerEvent::Completed, this, &ADynamicPawnController::Spawn);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

}
