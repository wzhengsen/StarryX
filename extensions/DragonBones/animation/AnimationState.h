/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2018 DragonBones team and other contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef DRAGONBONES_ANIMATION_STATE_H
#define DRAGONBONES_ANIMATION_STATE_H

#include "../core/BaseObject.h"
#include "../geom/Transform.h"

DRAGONBONES_NAMESPACE_BEGIN
/**
 * - The animation state is generated when the animation data is played.
 * @see dragonBones.Animation
 * @see dragonBones.AnimationData
 * @version DragonBones 3.0
 * @language en_US
 */
/**
 * - ����״̬�ɲ��Ŷ�������ʱ������
 * @see dragonBones.Animation
 * @see dragonBones.AnimationData
 * @version DragonBones 3.0
 * @language zh_CN
 */
class AnimationState : public BaseObject
{
    BIND_CLASS_TYPE_B(AnimationState);

private:
    enum class BaseTimelineType {
        Bone,
        Slot,
        Constraint
    };

public:
    /**
     * @private
     */
    bool actionEnabled;
    /**
     * @private
     */
    bool additiveBlending;
    /**
     * - Whether the animation state has control over the display object properties of the slots.
     * Sometimes blend a animation state does not want it to control the display object properties of the slots,
     * especially if other animation state are controlling the display object properties of the slots.
     * @default true
     * @version DragonBones 5.0
     * @language en_US
     */
    /**
     * - ����״̬�Ƿ�Բ�۵���ʾ���������п���Ȩ��
     * ��ʱ���һ������״̬����ϣ������Ʋ�۵���ʾ�������ԣ�
     * ��������������״̬���ڿ�����Щ��۵���ʾ��������ʱ��
     * @default true
     * @version DragonBones 5.0
     * @language zh_CN
     */
    bool displayControl;
    /**
     * - Whether to reset the objects without animation to the armature pose when the animation state is start to play.
     * This property should usually be set to false when blend multiple animation states.
     * @default true
     * @version DragonBones 5.1
     * @language en_US
     */
    /**
     * - ��ʼ���Ŷ���״̬ʱ�Ƿ�û�ж����Ķ�������Ϊ�Ǽܳ�ʼֵ��
     * ͨ���ڻ�϶������״̬ʱӦ�ý�����������Ϊ false��
     * @default true
     * @version DragonBones 5.1
     * @language zh_CN
     */
    bool resetToPose;
    /**
     * - The play times. [0: Loop play, [1~N]: Play N times]
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ���Ŵ����� [0: ����ѭ������, [1~N]: ѭ������ N ��]
     * @version DragonBones 3.0
     * @language zh_CN
     */
    unsigned playTimes;
    /**
     * - The blend layer.
     * High layer animation state will get the blend weight first.
     * When the blend weight is assigned more than 1, the remaining animation states will no longer get the weight assigned.
     * @readonly
     * @version DragonBones 5.0
     * @language en_US
     */
    /**
     * - ���ͼ�㡣
     * ͼ��ߵĶ���״̬�����Ȼ�ȡ���Ȩ�ء�
     * �����Ȩ�ط��䳬�� 1 ʱ��ʣ��Ķ���״̬�����ٻ��Ȩ�ط��䡣
     * @readonly
     * @version DragonBones 5.0
     * @language zh_CN
     */
    unsigned layer;
    /**
     * - The play speed.
     * The value is an overlay relationship with {@link dragonBones.Animation#timeScale}.
     * [(-N~0): Reverse play, 0: Stop play, (0~1): Slow play, 1: Normal play, (1~N): Fast play]
     * @default 1.0
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �����ٶȡ�
     * ��ֵ�� {@link dragonBones.Animation#timeScale} �ǵ��ӹ�ϵ��
     * [(-N~0): ��ת����, 0: ֹͣ����, (0~1): ���ٲ���, 1: ��������, (1~N): ���ٲ���]
     * @default 1.0
     * @version DragonBones 3.0
     * @language zh_CN
     */
    float timeScale;
    /**
     * - The blend weight.
     * @default 1.0
     * @version DragonBones 5.0
     * @language en_US
     */
    /**
     * - ���Ȩ�ء�
     * @default 1.0
     * @version DragonBones 5.0
     * @language zh_CN
     */
    float weight;
    /**
     * - The auto fade out time when the animation state play completed.
     * [-1: Do not fade out automatically, [0~N]: The fade out time] (In seconds)
     * @default -1.0
     * @version DragonBones 5.0
     * @language en_US
     */
    /**
     * - ����״̬������ɺ���Զ�����ʱ�䡣
     * [-1: ���Զ�����, [0~N]: ����ʱ��] ������Ϊ��λ��
     * @default -1.0
     * @version DragonBones 5.0
     * @language zh_CN
     */
    float autoFadeOutTime;
    /**
     * @private
     */
    float fadeTotalTime;
    /**
     * - The name of the animation state. (Can be different from the name of the animation data)
     * @readonly
     * @version DragonBones 5.0
     * @language en_US
     */
    /**
     * - ����״̬���ơ� �����Բ�ͬ�ڶ������ݣ�
     * @readonly
     * @version DragonBones 5.0
     * @language zh_CN
     */
    std::string name;
    /**
     * - The blend group name of the animation state.
     * This property is typically used to specify the substitution of multiple animation states blend.
     * @readonly
     * @version DragonBones 5.0
     * @language en_US
     */
    /**
     * - ��������ơ�
     * ������ͨ������ָ���������״̬���ʱ���໥�滻��ϵ��
     * @readonly
     * @version DragonBones 5.0
     * @language zh_CN
     */
    std::string group;

public:
    /**
     * - xx: Play Enabled, Fade Play Enabled
     * @internal
     */
    int _playheadState;
    /**
     * -1: Fade in, 0: Fade complete, 1: Fade out;
     * @internal
     */
    int _fadeState;
    /**
     * -1: Fade start, 0: Fading, 1: Fade complete;
     * @internal
     */
    int _subFadeState;
    /**
     * @internal
     */
    float _position;
    /**
     * @internal
     */
    float _duration;
    /**
     * @internal
     */
    float _fadeProgress;
    /**
     * @internal
     */
    float _weightResult;
    /**
     * @internal
     */
    AnimationData* _animationData;
    /**
     * @internal
     */
    ActionTimelineState* _actionTimeline;

private:
    unsigned _timelineDirty;
    float _fadeTime;
    float _time;
    std::vector<std::string> _boneMask;
    std::vector<BoneTimelineState*> _boneTimelines;
    std::vector<SlotTimelineState*> _slotTimelines;
    std::vector<ConstraintTimelineState*> _constraintTimelines;
    std::vector<std::pair<TimelineState*, BaseTimelineType>> _poseTimelines;
    std::map<std::string, BonePose*> _bonePoses;
    Armature* _armature;
    ZOrderTimelineState* _zOrderTimeline;

public:
    AnimationState() :
        _actionTimeline(nullptr),
        _zOrderTimeline(nullptr)
    {
        _onClear();
    }
    virtual ~AnimationState()
    {
        _onClear();
    }

protected:
    virtual void _onClear() override;

private:
    void _updateTimelines();
    void _updateBoneAndSlotTimelines();
    void _advanceFadeTime(float passedTime);

public:
    /**
     * @internal
     */
    void init(Armature* armature, AnimationData* animationData, AnimationConfig* animationConfig);
    /**
     * @internal
     */
    void advanceTime(float passedTime, float cacheFrameRate);
    /**
     * - Continue play.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �������š�
     * @version DragonBones 3.0
     * @language zh_CN
     */
    void play();
    /**
     * - Stop play.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��ͣ���š�
     * @version DragonBones 3.0
     * @language zh_CN
     */
    void stop();
    /**
     * - Fade out the animation state.
     * @param fadeOutTime - The fade out time. (In seconds)
     * @param pausePlayhead - Whether to pause the animation playing when fade out.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��������״̬��
     * @param fadeOutTime - ����ʱ�䡣 ������Ϊ��λ��
     * @param pausePlayhead - ����ʱ�Ƿ���ͣ���š�
     * @version DragonBones 3.0
     * @language zh_CN
     */
    void fadeOut(float fadeOutTime, bool pausePlayhead = true);
    /**
     * - Check if a specific bone mask is included.
     * @param boneName - The bone name.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ����Ƿ�����ض��������֡�
     * @param boneName - �������ơ�
     * @version DragonBones 3.0
     * @language zh_CN
     */
    bool containsBoneMask(const std::string& boneName) const;
    /**
     * - Add a specific bone mask.
     * @param boneName - The bone name.
     * @param recursive - Whether or not to add a mask to the bone's sub-bone.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ����ض��Ĺ������֡�
     * @param boneName - �������ơ�
     * @param recursive - �Ƿ�Ϊ�ù������ӹ���������֡�
     * @version DragonBones 3.0
     * @language zh_CN
     */
    void addBoneMask(const std::string& boneName, bool recursive = true);
    /**
     * - Remove the mask of a specific bone.
     * @param boneName - The bone name.
     * @param recursive - Whether to remove the bone's sub-bone mask.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ɾ���ض����������֡�
     * @param boneName - �������ơ�
     * @param recursive - �Ƿ�ɾ���ù������ӹ������֡�
     * @version DragonBones 3.0
     * @language zh_CN
     */
    void removeBoneMask(const std::string& boneName, bool recursive = true);
    /**
     * - Remove all bone masks.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ɾ�����й������֡�
     * @version DragonBones 3.0
     * @language zh_CN
     */
    void removeAllBoneMask();
    /**
     * - Whether the animation state is fading in.
     * @version DragonBones 5.1
     * @language en_US
     */
    /**
     * - �Ƿ����ڵ��롣
     * @version DragonBones 5.1
     * @language zh_CN
     */
    inline bool isFadeIn() const 
    {
        return _fadeState < 0;
    }
    /**
     * - Whether the animation state is fading out.
     * @version DragonBones 5.1
     * @language en_US
     */
    /**
     * - �Ƿ����ڵ�����
     * @version DragonBones 5.1
     * @language zh_CN
     */
    inline bool isFadeOut() const
    {
        return _fadeState > 0;
    }
    /**
     * - Whether the animation state is fade completed.
     * @version DragonBones 5.1
     * @language en_US
     */
    /**
     * - �Ƿ���򵭳���ϡ�
     * @version DragonBones 5.1
     * @language zh_CN
     */
    inline bool isFadeComplete() const
    {
        return _fadeState == 0;
    }
    /**
     * - Whether the animation state is playing.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �Ƿ����ڲ��š�
     * @version DragonBones 3.0
     * @language zh_CN
     */
    bool isPlaying() const;
    /**
     * - Whether the animation state is play completed.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �Ƿ񲥷���ϡ�
     * @version DragonBones 3.0
     * @language zh_CN
     */
    bool isCompleted() const;
    /**
     * - The times has been played.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �Ѿ�ѭ�����ŵĴ�����
     * @version DragonBones 3.0
     * @language zh_CN
     */
    unsigned getCurrentPlayTimes() const;
    /**
     * - The total time. (In seconds)
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �ܲ���ʱ�䡣 ������Ϊ��λ��
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline float getTotalTime() const
    {
        return _duration;
    }
    /**
     * - The time is currently playing. (In seconds)
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��ǰ���ŵ�ʱ�䡣 ������Ϊ��λ��
     * @version DragonBones 3.0
     * @language zh_CN
     */
    float getCurrentTime() const;
    void setCurrentTime(float value);
    inline const std::string& getName() const
    {
        return name;
    }

    /**
     * - The animation data.
     * @see dragonBones.AnimationData
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �������ݡ�
     * @see dragonBones.AnimationData
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline const AnimationData* getAnimationData() const
    { 
        return _animationData; 
    }
};
/**
 * @internal
 */
class BonePose : public BaseObject
{
    BIND_CLASS_TYPE_A(BonePose);

public:
    Transform current;
    Transform delta;
    Transform result;

protected:
    virtual void _onClear() override;
};
/**
 * @internal
 */
class BlendState
{
public:
    bool dirty;
    int layer;
    float leftWeight;
    float layerWeight;
    float blendWeight;

    /**
     * -1: First blending, 0: No blending, 1: Blending.
     */
    int update(float weight, int p_layer);
    void clear();
};

DRAGONBONES_NAMESPACE_END
#endif  // DRAGONBONES_ANIMATION_STATE_H
