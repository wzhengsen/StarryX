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
#ifndef DRAGONBONES_ANIMATION_H
#define DRAGONBONES_ANIMATION_H

#include "../core/BaseObject.h"

DRAGONBONES_NAMESPACE_BEGIN
/**
 * - The animation player is used to play the animation data and manage the animation states.
 * @see dragonBones.AnimationData
 * @see dragonBones.AnimationState
 * @version DragonBones 3.0
 * @language en_US
 */
/**
 * - �����������������Ŷ������ݺ͹�����״̬��
 * @see dragonBones.AnimationData
 * @see dragonBones.AnimationState
 * @version DragonBones 3.0
 * @language zh_CN
 */
class Animation final : public BaseObject
{
    BIND_CLASS_TYPE_B(Animation);

public:
    /**
     * - The play speed of all animations. [0: Stop, (0~1): Slow, 1: Normal, (1~N): Fast]
     * @default 1.0
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ���ж����Ĳ����ٶȡ� [0: ֹͣ����, (0~1): ���ٲ���, 1: ��������, (1~N): ���ٲ���]
     * @default 1.0
     * @version DragonBones 3.0
     * @language zh_CN
     */
    float timeScale;
    
private:
    bool _animationDirty;
    float _inheritTimeScale;
    std::vector<std::string> _animationNames;
    std::vector<AnimationState*> _animationStates;
    std::map<std::string, AnimationData*> _animations;
    Armature* _armature;
    AnimationConfig* _animationConfig;
    AnimationState* _lastAnimationState;

public:
    Animation() :
        _animationConfig(nullptr)
    { 
        _onClear();
    }
    ~Animation()
    {
        _onClear();
    }

private:
    void _fadeOut(AnimationConfig* animationConfig);

protected:
    virtual void _onClear() override;

public:
    /**
     * @internal
     */
    void init(Armature* armature);
    /**
     * @internal
     */
    void advanceTime(float passedTime);
    /**
     * - Clear all animations states.
     * @see dragonBones.AnimationState
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ������еĶ���״̬��
     * @see dragonBones.AnimationState
     * @version DragonBones 4.5
     * @language zh_CN
     */
    void reset();
    /**
     * - Pause a specific animation state.
     * @param animationName - The name of animation state. (If not set, it will pause all animations)
     * @see dragonBones.AnimationState
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��ָͣ������״̬�Ĳ��š�
     * @param animationName - ����״̬���ơ� �����δ���ã�����ͣ���ж�����
     * @see dragonBones.AnimationState
     * @version DragonBones 3.0
     * @language zh_CN
     */
    void stop(const std::string& animationName);
    /**
     * - Play animation with a specific animation config.
     * The API is still in the experimental phase and may encounter bugs or stability or compatibility issues when used.
     * @param animationConfig - The animation config.
     * @returns The playing animation state.
     * @see dragonBones.AnimationConfig
     * @beta
     * @version DragonBones 5.0
     * @language en_US
     */
    /**
     * - ͨ��ָ���Ķ������������Ŷ�����
     * �� API ����ʵ��׶Σ�ʹ��ʱ�������� bug ���ȶ��Ի���������⡣
     * @param animationConfig - �������á�
     * @returns ���ŵĶ���״̬��
     * @see dragonBones.AnimationConfig
     * @beta
     * @version DragonBones 5.0
     * @language zh_CN
     */
    AnimationState* playConfig(AnimationConfig* animationConfig);
    /**
     * - Play a specific animation.
     * @param animationName - The name of animation data. (If not set, The default animation will be played, or resume the animation playing from pause status, or replay the last playing animation)
     * @param playTimes - Playing repeat times. [-1: Use default value of the animation data, 0: No end loop playing, [1~N]: Repeat N times] (default: -1)
     * @returns The playing animation state.
     * @example
     * TypeScript style, for reference only.
     * <pre>
     *     armature.animation.play("walk");
     * </pre>
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ����ָ��������
     * @param animationName - �����������ơ� �����δ���ã��򲥷�Ĭ�϶���������ͣ״̬�л�Ϊ����״̬�������²���֮ǰ���ŵĶ�����
     * @param playTimes - ѭ�����Ŵ����� [-1: ʹ�ö�������Ĭ��ֵ, 0: ����ѭ������, [1~N]: ѭ������ N ��] ��Ĭ��: -1��
     * @returns ���ŵĶ���״̬��
     * @example
     * TypeScript ��񣬽����ο���
     * <pre>
     *     armature.animation.play("walk");
     * </pre>
     * @version DragonBones 3.0
     * @language zh_CN
     */
    AnimationState* play(const std::string& animationName = "", int playTimes = -1);
    /**
     * - Fade in a specific animation.
     * @param animationName - The name of animation data.
     * @param fadeInTime - The fade in time. [-1: Use the default value of animation data, [0~N]: The fade in time (In seconds)] (Default: -1)
     * @param playTimes - playing repeat times. [-1: Use the default value of animation data, 0: No end loop playing, [1~N]: Repeat N times] (Default: -1)
     * @param layer - The blending layer, the animation states in high level layer will get the blending weights with high priority, when the total blending weights are more than 1.0, there will be no more weights can be allocated to the other animation states. (Default: 0)
     * @param group - The blending group name, it is typically used to specify the substitution of multiple animation states blending. (Default: null)
     * @param fadeOutMode - The fade out mode, which is typically used to specify alternate mode of multiple animation states blending. (Default: AnimationFadeOutMode.SameLayerAndGroup)
     * @returns The playing animation state.
     * @example
     * TypeScript style, for reference only.
     * <pre>
     *     armature.animation.fadeIn("walk", 0.3, 0, 0, "normalGroup").resetToPose = false;
     *     armature.animation.fadeIn("attack", 0.3, 1, 0, "attackGroup").resetToPose = false;
     * </pre>
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ���벥��ָ���Ķ�����
     * @param animationName - �����������ơ�
     * @param fadeInTime - ����ʱ�䡣 [-1: ʹ�ö�������Ĭ��ֵ, [0~N]: ����ʱ�� (����Ϊ��λ)] ��Ĭ��: -1��
     * @param playTimes - ���Ŵ����� [-1: ʹ�ö�������Ĭ��ֵ, 0: ����ѭ������, [1~N]: ѭ������ N ��] ��Ĭ��: -1��
     * @param layer - ���ͼ�㣬ͼ��ߵĶ���״̬�����Ȼ�ȡ���Ȩ�أ������Ȩ�ط����ܺͳ��� 1.0 ʱ��ʣ��Ķ���״̬�������ٻ��Ȩ�ط��䡣 ��Ĭ��: 0��
     * @param group - ��������ƣ�������ͨ������ָ���������״̬���ʱ���໥�滻��ϵ�� ��Ĭ��: null��
     * @param fadeOutMode - ����ģʽ��������ͨ������ָ���������״̬���ʱ���໥�滻ģʽ�� ��Ĭ��: AnimationFadeOutMode.SameLayerAndGroup��
     * @returns ���ŵĶ���״̬��
     * @example
     * TypeScript ��񣬽����ο���
     * <pre>
     *     armature.animation.fadeIn("walk", 0.3, 0, 0, "normalGroup").resetToPose = false;
     *     armature.animation.fadeIn("attack", 0.3, 1, 0, "attackGroup").resetToPose = false;
     * </pre>
     * @version DragonBones 4.5
     * @language zh_CN
     */
    AnimationState* fadeIn(
        const std::string& animationName, float fadeInTime = -1.f, int playTimes = -1,
        int layer = 0, const std::string& group = "", AnimationFadeOutMode fadeOutMode = AnimationFadeOutMode::SameLayerAndGroup
    );
    /**
     * - Play a specific animation from the specific time.
     * @param animationName - The name of animation data.
     * @param time - The start time point of playing. (In seconds)
     * @param playTimes - Playing repeat times. [-1: Use the default value of animation data, 0: No end loop playing, [1~N]: Repeat N times] (Default: -1)
     * @returns The played animation state.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ��ָ��ʱ�俪ʼ����ָ���Ķ�����
     * @param animationName - �����������ơ�
     * @param time - ���ſ�ʼ��ʱ�䡣 (����Ϊ��λ)
     * @param playTimes - ѭ�����Ŵ����� [-1: ʹ�ö�������Ĭ��ֵ, 0: ����ѭ������, [1~N]: ѭ������ N ��] ��Ĭ��: -1��
     * @returns ���ŵĶ���״̬��
     * @version DragonBones 4.5
     * @language zh_CN
     */
    AnimationState* gotoAndPlayByTime(const std::string& animationName, float time = 0.f, int playTimes = -1);
    /**
     * - Play a specific animation from the specific frame.
     * @param animationName - The name of animation data.
     * @param frame - The start frame of playing.
     * @param playTimes - Playing repeat times. [-1: Use the default value of animation data, 0: No end loop playing, [1~N]: Repeat N times] (Default: -1)
     * @returns The played animation state.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ��ָ��֡��ʼ����ָ���Ķ�����
     * @param animationName - �����������ơ�
     * @param frame - ���ſ�ʼ��֡����
     * @param playTimes - ���Ŵ����� [-1: ʹ�ö�������Ĭ��ֵ, 0: ����ѭ������, [1~N]: ѭ������ N ��] ��Ĭ��: -1��
     * @returns ���ŵĶ���״̬��
     * @version DragonBones 4.5
     * @language zh_CN
     */
    AnimationState* gotoAndPlayByFrame(const std::string& animationName, unsigned frame = 0, int playTimes = -1);
    /**
     * - Play a specific animation from the specific progress.
     * @param animationName - The name of animation data.
     * @param progress - The start progress value of playing.
     * @param playTimes - Playing repeat times. [-1: Use the default value of animation data, 0: No end loop playing, [1~N]: Repeat N times] (Default: -1)
     * @returns The played animation state.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ��ָ�����ȿ�ʼ����ָ���Ķ�����
     * @param animationName - �����������ơ�
     * @param progress - ��ʼ���ŵĽ��ȡ�
     * @param playTimes - ���Ŵ����� [-1: ʹ�ö�������Ĭ��ֵ, 0: ����ѭ������, [1~N]: ѭ������ N ��] ��Ĭ��: -1��
     * @returns ���ŵĶ���״̬��
     * @version DragonBones 4.5
     * @language zh_CN
     */
    AnimationState* gotoAndPlayByProgress(const std::string& animationName, float progress = 0.f, int playTimes = -1);
    /**
     * - Stop a specific animation at the specific time.
     * @param animationName - The name of animation data.
     * @param time - The stop time. (In seconds)
     * @returns The played animation state.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ��ָ��ʱ��ָֹͣ����������
     * @param animationName - �����������ơ�
     * @param time - ֹͣ��ʱ�䡣 (����Ϊ��λ)
     * @returns ���ŵĶ���״̬��
     * @version DragonBones 4.5
     * @language zh_CN
     */
    AnimationState* gotoAndStopByTime(const std::string& animationName, float time = 0.f);
    /**
     * - Stop a specific animation at the specific frame.
     * @param animationName - The name of animation data.
     * @param frame - The stop frame.
     * @returns The played animation state.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ��ָ��ָֹ֡ͣ�������Ĳ���
     * @param animationName - �����������ơ�
     * @param frame - ֹͣ��֡����
     * @returns ���ŵĶ���״̬��
     * @version DragonBones 4.5
     * @language zh_CN
     */
    AnimationState* gotoAndStopByFrame(const std::string& animationName, unsigned frame = 0);
    /**
     * - Stop a specific animation at the specific progress.
     * @param animationName - The name of animation data.
     * @param progress - The stop progress value.
     * @returns The played animation state.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ��ָ���Ľ���ָֹͣ���Ķ������š�
     * @param animationName - �����������ơ�
     * @param progress - ֹͣ���ȡ�
     * @returns ���ŵĶ���״̬��
     * @version DragonBones 4.5
     * @language zh_CN
     */
    AnimationState* gotoAndStopByProgress(const std::string& animationName, float progress = 0.f);
    /**
     * - Get a specific animation state.
     * @param animationName - The name of animation state.
     * @example
     * TypeScript style, for reference only.
     * <pre>
     *     armature.animation.play("walk");
     *     let walkState = armature.animation.getState("walk");
     *     walkState.timeScale = 0.5;
     * </pre>
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��ȡָ���Ķ���״̬
     * @param animationName - ����״̬���ơ�
     * @example
     * TypeScript ��񣬽����ο���
     * <pre>
     *     armature.animation.play("walk");
     *     let walkState = armature.animation.getState("walk");
     *     walkState.timeScale = 0.5;
     * </pre>
     * @version DragonBones 3.0
     * @language zh_CN
     */
    AnimationState* getState(const std::string& animationName) const;
    /**
     * - Check whether a specific animation data is included.
     * @param animationName - The name of animation data.
     * @see dragonBones.AnimationData
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ����Ƿ����ָ���Ķ�������
     * @param animationName - �����������ơ�
     * @see dragonBones.AnimationData
     * @version DragonBones 3.0
     * @language zh_CN
     */
    bool hasAnimation(const std::string& animationName) const;
    /**
     * - Get all the animation states.
     * @version DragonBones 5.1
     * @language en_US
     */
    /**
     * - ��ȡ���еĶ���״̬
     * @version DragonBones 5.1
     * @language zh_CN
     */
    inline const std::vector<AnimationState*>& getStates() const
    {
        return _animationStates;
    }
    /**
     * - Check whether there is an animation state is playing
     * @see dragonBones.AnimationState
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ����Ƿ��ж���״̬���ڲ���
     * @see dragonBones.AnimationState
     * @version DragonBones 3.0
     * @language zh_CN
     */
    bool isPlaying() const;
    /**
     * - Check whether all the animation states' playing were finished.
     * @see dragonBones.AnimationState
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ����Ƿ����еĶ���״̬���Ѳ�����ϡ�
     * @see dragonBones.AnimationState
     * @version DragonBones 3.0
     * @language zh_CN
     */
    bool isCompleted() const;
    /**
     * - The name of the last playing animation state.
     * @see #lastAnimationState
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��һ�����ŵĶ���״̬����
     * @see #lastAnimationState
     * @version DragonBones 3.0
     * @language zh_CN
     */
    const std::string& getLastAnimationName() const;
    /**
     * - The name of all animation data
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ���ж������ݵ�����
     * @version DragonBones 4.5
     * @language zh_CN
     */
    inline const std::vector<std::string>& getAnimationNames() const
    {
        return _animationNames;
    }
    /**
     * - All animation data.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ���еĶ������ݡ�
     * @version DragonBones 4.5
     * @language zh_CN
     */
    inline const std::map<std::string, AnimationData*>& getAnimations() const
    {
        return _animations;
    }
    void setAnimations(const std::map<std::string, AnimationData*>& value);
    /**
     * - An AnimationConfig instance that can be used quickly.
     * @see dragonBones.AnimationConfig
     * @version DragonBones 5.0
     * @language en_US
     */
    /**
     * - һ�����Կ���ʹ�õĶ�������ʵ����
     * @see dragonBones.AnimationConfig
     * @version DragonBones 5.0
     * @language zh_CN
     */
    AnimationConfig* getAnimationConfig() const;
    /**
     * - The last playing animation state
     * @see dragonBones.AnimationState
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��һ�����ŵĶ���״̬
     * @see dragonBones.AnimationState
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline AnimationState* getLastAnimationState() const
    {
        return _lastAnimationState;
    }
};

DRAGONBONES_NAMESPACE_END
#endif  // DRAGONBONES_ANIMATION_H
