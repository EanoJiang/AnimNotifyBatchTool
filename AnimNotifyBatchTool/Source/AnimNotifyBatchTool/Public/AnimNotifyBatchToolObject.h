#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AnimNotifyBatchToolObject.generated.h"

class UAnimSequenceBase;
class UAnimSequence;
class UAnimNotify;

// 单条批处理规则：
// - 在动画中查找“源事件”（可以是Notify名，也可以是 Sync Marker创建的MarkerName）
// - 同帧创建一个TargetNotifyClass
USTRUCT(BlueprintType)
struct FAnimNotifyBatchRule
{
    GENERATED_BODY()

    // 源事件名称
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotifyBatchTool")
    FName SourceNotifyName;

    // 目标 Notify 类：可拖入 AnimNotify 的 Blueprint Class
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotifyBatchTool")
    TSoftClassPtr<UAnimNotify> TargetNotifyClass;

    // 指定Track名，为空则使用默认 Track(0)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotifyBatchTool")
    FName TargetNotifyTrackName;
};

UCLASS(BlueprintType)
class UAnimNotifyBatchToolObject : public UObject
{
    GENERATED_BODY()

public:
    // 待处理动画资产
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotifyBatchTool")
    TArray<TObjectPtr<UAnimSequenceBase>> AnimAssets;

    // 规则列表
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotifyBatchTool")
    TArray<FAnimNotifyBatchRule> Rules;

    // 是否自动保存资产
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotifyBatchTool")
    bool bAutoSave = false;

    void Apply();

private:
    // 解析目标 NotifyClass
    UClass* ResolveNotifyClass(const FAnimNotifyBatchRule& Rule) const;
    // 将单条规则应用到单个动画资产
    void ApplyToSingleAnim(UAnimSequenceBase* Anim, const FAnimNotifyBatchRule& Rule);
    // 查找/创建目标 Track，并返回其 TrackIndex（TrackName 为空时返回默认 0）
    int32 GetOrAddNotifyTrackIndex(UAnimSequenceBase* Anim, FName TrackName) const;
};
