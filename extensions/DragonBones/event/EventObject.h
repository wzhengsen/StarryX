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
#ifndef DRAGONBONES_EVENT_OBJECT_H
#define DRAGONBONES_EVENT_OBJECT_H

#include "../core/BaseObject.h"

DRAGONBONES_NAMESPACE_BEGIN
/**
 * - The properties of the object carry basic information about an event,
 * which are passed as parameter or parameter's parameter to event listeners when an event occurs.
 * @version DragonBones 4.5
 * @language en_US
 */
/**
 * - �¼����󣬰����й��¼��Ļ�����Ϣ���������¼�ʱ����ʵ������Ϊ����������Ĳ������ݸ��¼���������
 * @version DragonBones 4.5
 * @language zh_CN
 */
class EventObject : public BaseObject
{
    BIND_CLASS_TYPE_A(EventObject);

public:
    /**
     * - Animation start play.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ������ʼ���š�
     * @version DragonBones 4.5
     * @language zh_CN
     */
    static const char* START;
    /**
     * - Animation loop play complete once.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ����ѭ���������һ�Ρ�
     * @version DragonBones 4.5
     * @language zh_CN
     */
    static const char* LOOP_COMPLETE;
    /**
     * - Animation play complete.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ����������ɡ�
     * @version DragonBones 4.5
     * @language zh_CN
     */
    static const char* COMPLETE;
    /**
     * - Animation fade in start.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �������뿪ʼ��
     * @version DragonBones 4.5
     * @language zh_CN
     */
    static const char* FADE_IN;
    /**
     * - Animation fade in complete.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ����������ɡ�
     * @version DragonBones 4.5
     * @language zh_CN
     */
    static const char* FADE_IN_COMPLETE;
    /**
     * - Animation fade out start.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ����������ʼ��
     * @version DragonBones 4.5
     * @language zh_CN
     */
    static const char* FADE_OUT;
    /**
     * - Animation fade out complete.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ����������ɡ�
     * @version DragonBones 4.5
     * @language zh_CN
     */
    static const char* FADE_OUT_COMPLETE;
    /**
     * - Animation frame event.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ����֡�¼���
     * @version DragonBones 4.5
     * @language zh_CN
     */
    static const char* FRAME_EVENT;
    /**
     * - Animation frame sound event.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ����֡�����¼���
     * @version DragonBones 4.5
     * @language zh_CN
     */
    static const char* SOUND_EVENT;

    /**
     * @internal
     */
    static void actionDataToInstance(const ActionData* data, EventObject* instance, Armature* armature);

public:
    /**
     * - If is a frame event, the value is used to describe the time that the event was in the animation timeline. (In seconds)
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �����֡�¼�����ֵ�����������¼��ڶ���ʱ������������ʱ�䡣������Ϊ��λ��
     * @version DragonBones 4.5
     * @language zh_CN
     */
    float time;
    /**
     * - The event type��
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �¼����͡�
     * @version DragonBones 4.5
     * @language zh_CN
     */
    std::string type;
    /**
     * - The event name. (The frame event name or the frame sound name)
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �¼����ơ� (֡�¼������ƻ�֡����������)
     * @version DragonBones 4.5
     * @language zh_CN
     */
    std::string name;
    /**
     * - The armature that dispatch the event.
     * @see dragonBones.Armature
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �������¼��ĹǼܡ�
     * @see dragonBones.Armature
     * @version DragonBones 4.5
     * @language zh_CN
     */
    Armature* armature;
    /**
     * - The bone that dispatch the event.
     * @see dragonBones.Bone
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �������¼��Ĺ�����
     * @see dragonBones.Bone
     * @version DragonBones 4.5
     * @language zh_CN
     */
    Bone* bone;
    /**
     * - The slot that dispatch the event.
     * @see dragonBones.Slot
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �������¼��Ĳ�ۡ�
     * @see dragonBones.Slot
     * @version DragonBones 4.5
     * @language zh_CN
     */
    Slot* slot;
    /**
     * - The animation state that dispatch the event.
     * @see dragonBones.AnimationState
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �������¼��Ķ���״̬��
     * @see dragonBones.AnimationState
     * @version DragonBones 4.5
     * @language zh_CN
     */
    AnimationState* animationState;
    /**
     * @private
     */
    const ActionData* actionData;
    /**
     * - The custom data.
     * @see dragonBones.CustomData
     * @private
     * @version DragonBones 5.0
     * @language en_US
     */
    /**
     * - �Զ������ݡ�
     * @see dragonBones.CustomData
     * @private
     * @version DragonBones 5.0
     * @language zh_CN
     */
    UserData* data;

protected:
    virtual void _onClear() override;

public: // For WebAssembly.
    Armature* getArmature() const { return armature; }
    Bone* getBone() const { return bone; }
    Slot* getSlot() const { return slot; }
    AnimationState* getAnimationState() const { return animationState; }
    UserData* getData() const { return data; }
};
DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_EVENT_OBJECT_H
