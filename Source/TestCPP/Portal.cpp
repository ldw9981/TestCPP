#include "Portal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// 기본값 설정
APortal::APortal()
{
	// 모든 프레임에서 Tick()을 호출하도록 이 actor을(를) 설정합니다. 필요하지 않은 경우 이 기능을 해제하여 성능을 향상시킬 수 있습니다.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트생성
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);  // 최상위 루트로 연결

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);   // 컬리전의 자식으로 연결
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);	// 바닥 메시 충돌은 사용안함.

	//엔진이 등록된 포인터함수를 호출한다.
	OnActorBeginOverlap.AddDynamic(this, &APortal::OnOverlap);
}

// 게임이 시작되거나 생성될 때 호출됩니다.
void APortal::BeginPlay()
{
	Super::BeginPlay();
}

void APortal::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	// 현재 플레이어 캐릭터와 Overlap된 Actor가 같은지 확인한다.
	AActor* result = (AActor*)UGameplayStatics::GetPlayerCharacter(this, 0);
	if(OtherActor != result)
	{
		return;
	}

	// 경로가 어셋인지 확인하고 맞으면 레벨을 로드한다.
	if(Level.ToSoftObjectPath().IsAsset())
		UGameplayStatics::OpenLevelBySoftObjectPtr(this,Level);	
}

// 매 프레임마다 호출됨
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
