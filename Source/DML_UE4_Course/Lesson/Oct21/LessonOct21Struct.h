// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "LessonOct21Struct.generated.h"
/**
 *
 */
USTRUCT(BlueprintType)
struct FLessonOct21Struct
{
	GENERATED_USTRUCT_BODY()
public:
	// ������������
	FLessonOct21Struct();
	FLessonOct21Struct(float x, float y, float z);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Struct")
		float MyX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Struct")
		float MyY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Struct")
		float MyZ;

	/* ������, ����������� � ���������, �� ����� �������� UFUNCTION, 
	������� ��� ��������� ������� � Blueprint'�� 
	������� �������� �� UBluepruntFunctionLibrary �����,
	� ������� ��� ��������� ������ ��������� ��� UFUNCTION */
	static FLessonOct21Struct Add(FLessonOct21Struct A, FLessonOct21Struct B);

	FORCEINLINE bool operator==(const FLessonOct21Struct& Other)
	{
		return this->MyX == Other.MyX;
	};

	FORCEINLINE FLessonOct21Struct operator+(const FLessonOct21Struct& Other)
	{
		FLessonOct21Struct Result;

		Result.MyX = this->MyX + Other.MyX;
		Result.MyY = this->MyY + Other.MyY;
		Result.MyZ = this->MyZ + Other.MyZ;

		return Result;
	};
};
