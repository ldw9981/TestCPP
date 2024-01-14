#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class TESTCPP_API APortal : public AActor
{
	GENERATED_BODY()
	
public:
	// 이 actor의 속성에 대한 기본값을 설정합니다.
	APortal();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Portal, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Collision;			// 오버랩을 검출할 영역

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Portal, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;  // 포탈의 바닥 표시

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Portal, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWorld> Level;	// 에셋의 경로만 지정한다. (경로만 저장되고, 에셋이 로드되지는 않는다.)

protected:
	// 게임이 시작되거나 생성될 때 호출됩니다.

	virtual void BeginPlay() override;

	UFUNCTION()	// 델리게이트 이벤트 시스템을 사용하기 위해 선언
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor );
public:
	// 매 프레임마다 호출됨
	virtual void Tick(float DeltaTime) override;
};
