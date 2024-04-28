// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Engine/World.h"
#include "GameFramework/Pawn.h"

#include "PawnAttributeAsset.h"

#include "PawnPossession/TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "DynamicPawnController.generated.h"

/**
 * 
 */

//UENUM(Blueprintable)
UENUM()
enum class EPawnType {
	ThirdPerson,
	FirstPerson,
	TopDown
};

USTRUCT(Blueprintable)
struct FPawnDataTable: public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EPawnType PawnType{};

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> PawnClass{};
};

UCLASS()
class PAWNPOSSESSION_API ADynamicPawnController : public APlayerController
{
	GENERATED_BODY()

	void Spawn();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/*UFUNCTION(BlueprintImplementable)
	void DisplayAttributes(UPawnAttributeAsset* PawnAttrtibute);*/

public:
	ADynamicPawnController();

	UPROPERTY()
	int8 indexOfDataTable;
	 
};

