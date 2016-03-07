// Fill out your copyright notice in the Description page of Project Settings.

#include "DML_UE4_Course.h"
#include "Lesson/Oct14/PlayableCharacter.h"

APlayableCharacter::APlayableCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, "Camera Boom");	// �������� ���������� Spring Arm, �� ������� ������� ������
	CameraBoom->AttachTo(RootComponent);	// ��������� ������ � ��������� ���������� ���������
	CameraBoom->bUsePawnControlRotation = true;	// ��� ������ �������� ����������� �������� ����������� ������ ���������
	CameraBoom->bInheritPitch = false;	// �� �� ���������� ������
	CameraBoom->bInheritRoll = false;	// � �� ���������� ��������
	CameraBoom->bInheritYaw = true;		// � �������� ������ �������

	FollowCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, "Follow Camera");	// ������� ��������� ������
	FollowCamera->AttachTo(CameraBoom);	// ��������� � ������, ��� ������ ������ ���������
}


void APlayableCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveForward", this, &APlayableCharacter::MoveForward);
	InputComponent->BindAxis("LookUp", this, &APlayableCharacter::LookUp);
	InputComponent->BindAxis("MoveRight", this, &APlayableCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &APlayableCharacter::Turn);

	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayableCharacter::DoCharacterJump);
	//InputComponent->BindAction("Jump", IE_Released, this, &APlayableCharacter::StopCharacterJump);	// �� ������, ���� ��� ����� ��������� �������� �� ������� ������
}

void APlayableCharacter::MoveForward(float Step)
{
	/*
	const FRotator rot = GetControlRotation();	// �������� Rotator �����������
	const newRot = FRotator(0, rot.Yaw, 0);		// �� ��� �� ����� ���� �������, � ������ �������(Yaw)
	const FVector dir = FRotationMatrix(newRot)::GetUnitAxis(EAxis::X);	// �������� �� ������ �������� ������ ������ ���������
	AddMovementInput(dir, Step);	// � ��������� �������� �� ���� ������
	 */

	const FVector direction = FRotationMatrix(FRotator(0, GetControlRotation().Yaw, 0)).GetUnitAxis(EAxis::X);
	AddMovementInput(direction, Step);
}

void APlayableCharacter::LookUp(float Step)
{
	AddControllerPitchInput(Step);
}

/*	����� �� ��������� �������
 *	����� �� ������ ������ ������ �� �� �����, ��� � � ������ MoveForward, 
 *	� �������� � ���, ��� �������� ������ ������ ��������� (������ � Unreal'e - ��� Y)
 */
void APlayableCharacter::MoveRight(float Step)
{
	const FVector direction = FRotationMatrix(FRotator(0, GetControlRotation().Yaw, 0)).GetUnitAxis(EAxis::Y);
	AddMovementInput(direction, Step);
}
/*	����� �� ��������� �������
	�� ������ ��������� ��� ��������(Yaw) �����������, � �� �������(Pitch) ��� � ������� ������
 */
void APlayableCharacter::Turn(float Step)
{
	AddControllerYawInput(Step);
}

void APlayableCharacter::DoCharacterJump()
{
	GetCharacterMovement()->DoJump(true);
}