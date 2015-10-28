// Fill out your copyright notice in the Description page of Project Settings.

#include "DML_UE4_Course.h"
#include "RayCastCharacter.h"

ARayCastCharacter::ARayCastCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	RayDistance = 1500.f;

	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);

	this->OnActorHit.AddDynamic(this, &ARayCastCharacter::OnHit);
	this->OnActorBeginOverlap.AddDynamic(this, &ARayCastCharacter::OnBeginOverlap);
	this->OnActorEndOverlap.AddDynamic(this, &ARayCastCharacter::OnEndOverlap);


	/*this->OnActorHit.AddDynamic(this, &ARayCastCharacter::OnHit)*/
}

void ARayCastCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Ray", IE_Pressed, this, &ARayCastCharacter::ThrowRay);
}

void ARayCastCharacter::ThrowRay()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Throw Ray Cast");

	// ��������� ����� ������ ����
	FVector TraceEnd = GetActorLocation() + GetActorForwardVector()*RayDistance;

	// ������������� ���������, ������� ����� ������������ ����� ������� ������ � ������������
	FHitResult TraceHit;

	// ��������� ��� ��� ��������
	FCollisionQueryParams TraceParams(FName("Ray Cast"), true, this);

	// ������� ��� ���� �� ����� ������, ������� �����������, ����� �������� ���� � ���� �����������
	GetWorld()->LineTraceSingleByChannel(
		TraceHit,
		GetActorLocation(),
		TraceEnd,
		COLLISION_TEST_TRACE,
		TraceParams);




	// ������������� ����� ��������, � �������� ������� ����� �����������������
	/*TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery(ECC_Pawn));
	ObjectTypes.Add(EObjectTypeQuery(ECC_WorldStatic));
	ObjectTypes.Add(EObjectTypeQuery(ECC_WorldDynamic));
	FCollisionObjectQueryParams ObjectParams(ObjectTypes);

	GetWorld()->LineTraceSingleByObjectType(
	TraceHit,
	GetActorLocation(),
	TraceEnd,
	ObjectParams,
	TraceParams);*/




	/*GetWorld()->SweepSingleByChannel(	// ������� ��� ������ ���������� ����������
	TraceHit,
	GetActorLocation(),
	TraceEnd,
	FQuat::Identity,	// ��� ����� ��������� Rotation, ���������� ����� FQuat. FQuat::Identity ��� ���������� ������� �� ������ ���� ������ �����. �� �� ����� ������ ������� ��� �������
	COLLISION_TEST_TRACE,
	FCollisionShape::MakeBox(FVector(0, 100, 100)),	// ������ �����, �� ������� ����� ������ ����
	TraceParams);*/




	/*TArray<FHitResult> TraceHits;	// ���� �������� ������� ��� ������������� ��������. ������� � ���, ��� ������ ������ FHitResult, ���������� �������� ������ �� ���

	GetWorld()->LineTraceMultiByChannel(
	TraceHits,
	GetActorLocation(),
	TraceEnd,
	COLLISION_TEST_TRACE,
	TraceParams);*/




	// ��������� ������ ����
	DrawDebugLine(
		GetWorld(),
		GetActorLocation(),
		TraceEnd,
		FColor::Cyan,
		false,	// ����� �� ��� ��� �������������� ���������
		3.0f,	// ������� ������� �� ����� ��������������
		0,
		5.0f);	// ������� ����. �������� �� ��� ���� �������

	if (TraceHit.GetActor())	// ��������, ������� �� �� ������-���� ������
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "YAY!!!");
		ARayCastCharacter* Ray = Cast<ARayCastCharacter>(TraceHit.GetActor());

		if (Ray)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, "It's Ray!!!");
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "No hit...");
	}


}

void ARayCastCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, "Actor Hit");
}

void ARayCastCharacter::OnBeginOverlap(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, "Actor Begin Overlap");
}

void ARayCastCharacter::OnEndOverlap(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "Actor End Overlap");
}