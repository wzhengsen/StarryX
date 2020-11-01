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
#ifndef DRAGONBONES_ARMATURE_H
#define DRAGONBONES_ARMATURE_H

#include "../core/BaseObject.h"
#include "../animation/IAnimatable.h"
#include "../model/ArmatureData.h"
#include "IArmatureProxy.h"

DRAGONBONES_NAMESPACE_BEGIN
/**
 * - Armature is the core of the skeleton animation system.
 * @see dragonBones.ArmatureData
 * @see dragonBones.Bone
 * @see dragonBones.Slot
 * @see dragonBones.Animation
 * @version DragonBones 3.0
 * @language en_US
 */
/**
 * - �Ǽ��ǹ�������ϵͳ�ĺ��ġ�
 * @see dragonBones.ArmatureData
 * @see dragonBones.Bone
 * @see dragonBones.Slot
 * @see dragonBones.Animation
 * @version DragonBones 3.0
 * @language zh_CN
 */
class Armature : public virtual IAnimatable, public BaseObject
{
    BIND_CLASS_TYPE_B(Armature);

private:
    static bool _onSortSlots(Slot* a, Slot* b);

public:
    /**
     * - Whether to inherit the animation control of the parent armature.
     * True to try to have the child armature play an animation with the same name when the parent armature play the animation.
     * @default true
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �Ƿ�̳и��ǼܵĶ������ơ�
     * �����ֵΪ true�������Ǽܲ��Ŷ���ʱ���᳢�����ӹǼܲ���ͬ��������
     * @default true
     * @version DragonBones 4.5
     * @language zh_CN
     */
    bool inheritAnimation;
    /**
     * @private
     */
    void* userData;

public:
    /**
     * @internal
     */
    int _cacheFrameIndex;
    /**
     * @internal
     */
    ArmatureData* _armatureData;
    /**
     * @internal
     */
    DragonBones* _dragonBones;
    /**
     * @internal
     */
    Slot* _parent;
    /**
     * @internal
     */
    TextureAtlasData* _replaceTextureAtlasData;
    /**
     * @internal
     */
    std::vector<Constraint*> _constraints;

protected:
    bool _debugDraw;
    bool _lockUpdate;
    bool _slotsDirty;
    bool _zOrderDirty;
    bool _flipX;
    bool _flipY;
    std::vector<Bone*> _bones;
    std::vector<Slot*> _slots;
    std::vector<EventObject*> _actions;
    Animation* _animation;
    IArmatureProxy* _proxy;
    void* _display;
    WorldClock* _clock;
    void* _replacedTexture;

public:
    Armature() :
        _animation(nullptr),
        _proxy(nullptr),
        _clock(nullptr),
        _replaceTextureAtlasData(nullptr)
    {
        _onClear();
    }
    virtual ~Armature()
    {
        _onClear();
    }

protected:
    virtual void _onClear() override;

private:
    void _sortSlots();

public:
    /**
     * @internal
     */
    void _sortZOrder(const int16_t* slotIndices, unsigned offset);
    /**
     * @internal
     */
    void _addBone(Bone* value);
    /**
     * @internal
     */
    void _addSlot(Slot* value);
    /**
     * @internal
     */
    void _addConstraint(Constraint* value);
    /**
     * @internal
     */
    void _bufferAction(EventObject* action, bool append);
    /**
     * - Dispose the armature. (Return to the object pool)
     * @example
     * TypeScript style, for reference only.
     * <pre>
     *     removeChild(armature.display);
     *     armature.dispose();
     * </pre>
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �ͷŹǼܡ� �����յ�����أ�
     * @example
     * TypeScript ��񣬽����ο���
     * <pre>
     *     removeChild(armature.display);
     *     armature.dispose();
     * </pre>
     * @version DragonBones 3.0
     * @language zh_CN
     */
    void dispose();
    /**
     * @internal
     */
    void init(ArmatureData *armatureData, IArmatureProxy* proxy, void* display, DragonBones* dragonBones);
    /**
     * @inheritDoc
     */
    void advanceTime(float passedTime) override;
    /**
     * - Forces a specific bone or its owning slot to update the transform or display property in the next frame.
     * @param boneName - The bone name. (If not set, all bones will be update)
     * @param updateSlot - Whether to update the bone's slots. (Default: false)
     * @see dragonBones.Bone#invalidUpdate()
     * @see dragonBones.Slot#invalidUpdate()
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ǿ���ض���������ӵ�еĲ������һ֡���±任����ʾ���ԡ�
     * @param boneName - �������ơ� �����δ���ã����������й�����
     * @param updateSlot - �Ƿ���¹����Ĳ�ۡ� ��Ĭ��: false��
     * @see dragonBones.Bone#invalidUpdate()
     * @see dragonBones.Slot#invalidUpdate()
     * @version DragonBones 3.0
     * @language zh_CN
     */
    void invalidUpdate(const std::string& boneName = "", bool updateSlot = false);
    /**
     * - Check whether a specific point is inside a custom bounding box in a slot.
     * The coordinate system of the point is the inner coordinate system of the armature.
     * Custom bounding boxes need to be customized in Dragonbones Pro.
     * @param x - The horizontal coordinate of the point.
     * @param y - The vertical coordinate of the point.
     * @version DragonBones 5.0
     * @language en_US
     */
    /**
     * - ����ض����Ƿ���ĳ����۵��Զ���߽���ڡ�
     * �������ϵΪ�Ǽ�������ϵ��
     * �Զ���߽����Ҫ�� DragonBones Pro ���Զ��塣
     * @param x - ���ˮƽ���ꡣ
     * @param y - ��Ĵ�ֱ���ꡣ
     * @version DragonBones 5.0
     * @language zh_CN
     */
    Slot* containsPoint(float x, float y) const;
    /**
     * - Check whether a specific segment intersects a custom bounding box for a slot in the armature.
     * The coordinate system of the segment and intersection is the inner coordinate system of the armature.
     * Custom bounding boxes need to be customized in Dragonbones Pro.
     * @param xA - The horizontal coordinate of the beginning of the segment.
     * @param yA - The vertical coordinate of the beginning of the segment.
     * @param xB - The horizontal coordinate of the end point of the segment.
     * @param yB - The vertical coordinate of the end point of the segment.
     * @param intersectionPointA - The first intersection at which a line segment intersects the bounding box from the beginning to the end. (If not set, the intersection point will not calculated)
     * @param intersectionPointB - The first intersection at which a line segment intersects the bounding box from the end to the beginning. (If not set, the intersection point will not calculated)
     * @param normalRadians - The normal radians of the tangent of the intersection boundary box. [x: Normal radian of the first intersection tangent, y: Normal radian of the second intersection tangent] (If not set, the normal will not calculated)
     * @returns The slot of the first custom bounding box where the segment intersects from the start point to the end point.
     * @version DragonBones 5.0
     * @language en_US
     */
    /**
     * - ����ض��߶��Ƿ���Ǽܵ�ĳ����۵��Զ���߽���ཻ��
     * �߶κͽ��������ϵ��Ϊ�Ǽ�������ϵ��
     * �Զ���߽����Ҫ�� DragonBones Pro ���Զ��塣
     * @param xA - �߶�����ˮƽ���ꡣ
     * @param yA - �߶����Ĵ�ֱ���ꡣ
     * @param xB - �߶��յ��ˮƽ���ꡣ
     * @param yB - �߶��յ�Ĵ�ֱ���ꡣ
     * @param intersectionPointA - �߶δ���㵽�յ���߽���ཻ�ĵ�һ�����㡣 �����δ���ã��򲻼��㽻�㣩
     * @param intersectionPointB - �߶δ��յ㵽�����߽���ཻ�ĵ�һ�����㡣 �����δ���ã��򲻼��㽻�㣩
     * @param normalRadians - ����߽�����ߵķ��߻��ȡ� [x: ��һ���������ߵķ��߻���, y: �ڶ����������ߵķ��߻���] �����δ���ã��򲻼��㷨�ߣ�
     * @returns �߶δ���㵽�յ��ཻ�ĵ�һ���Զ���߽��Ĳ�ۡ�
     * @version DragonBones 5.0
     * @language zh_CN
     */
    Slot* intersectsSegment(
        float xA, float yA, float xB, float yB,
        Point* intersectionPointA = nullptr,
        Point* intersectionPointB = nullptr,
        Point* normalRadians = nullptr
    ) const;
    /**
     * - Get a specific bone.
     * @param name - The bone name.
     * @see dragonBones.Bone
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��ȡ�ض��Ĺ�����
     * @param name - �������ơ�
     * @see dragonBones.Bone
     * @version DragonBones 3.0
     * @language zh_CN
     */
    Bone* getBone(const std::string& name) const;
    /**
     * - Get a specific bone by the display.
     * @param display - The display object.
     * @see dragonBones.Bone
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ͨ����ʾ�����ȡ�ض��Ĺ�����
     * @param display - ��ʾ����
     * @see dragonBones.Bone
     * @version DragonBones 3.0
     * @language zh_CN
     */
    Bone* getBoneByDisplay(void* display) const;
    /**
     * - Get a specific slot.
     * @param name - The slot name.
     * @see dragonBones.Slot
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��ȡ�ض��Ĳ�ۡ�
     * @param name - ������ơ�
     * @see dragonBones.Slot
     * @version DragonBones 3.0
     * @language zh_CN
     */
    Slot* getSlot(const std::string& name) const;
    /**
     * - Get a specific slot by the display.
     * @param display - The display object.
     * @see dragonBones.Slot
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ͨ����ʾ�����ȡ�ض��Ĳ�ۡ�
     * @param display - ��ʾ����
     * @see dragonBones.Slot
     * @version DragonBones 3.0
     * @language zh_CN
     */
    Slot* getSlotByDisplay(void* display) const;
    /**
     * - Get all bones.
     * @see dragonBones.Bone
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��ȡ���еĹ�����
     * @see dragonBones.Bone
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline const std::vector<Bone*>& getBones() const
    {
        return _bones;
    }
    /**
     * - Get all slots.
     * @see dragonBones.Slot
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��ȡ���еĲ�ۡ�
     * @see dragonBones.Slot
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline const std::vector<Slot*>& getSlots() const
    {
        return _slots;
    }
    /**
     * - Whether to flip the armature horizontally.
     * @version DragonBones 5.5
     * @language en_US
     */
    /**
     * - �Ƿ񽫹Ǽ�ˮƽ��ת��
     * @version DragonBones 5.5
     * @language zh_CN
     */
    bool getFlipX() const 
    { 
        return _flipX; 
    }
    void setFlipX(bool value) 
    { 
        _flipX = value;
        invalidUpdate("");
    }

    /**
     * - Whether to flip the armature vertically.
     * @version DragonBones 5.5
     * @language en_US
     */
    /**
     * - �Ƿ񽫹Ǽܴ�ֱ��ת��
     * @version DragonBones 5.5
     * @language zh_CN
     */
    bool getFlipY() const 
    { 
        return _flipY; 
    }
    void setFlipY(bool value) 
    { 
        _flipY = value;
        invalidUpdate("");
    }
    /**
     * - The animation cache frame rate, which turns on the animation cache when the set value is greater than 0.
     * There is a certain amount of memory overhead to improve performance by caching animation data in memory.
     * The frame rate should not be set too high, usually with the frame rate of the animation is similar and lower than the program running frame rate.
     * When the animation cache is turned on, some features will fail, such as the offset property of bone.
     * @example
     * TypeScript style, for reference only.
     * <pre>
     *     armature.cacheFrameRate = 24;
     * </pre>
     * @see dragonBones.DragonBonesData#frameRate
     * @see dragonBones.ArmatureData#frameRate
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ��������֡�ʣ������õ�ֵ���� 0 ��ʱ�����Ὺ���������档
     * ͨ�����������ݻ������ڴ���������������ܣ�����һ�����ڴ濪����
     * ֡�ʲ������õĹ��ߣ�ͨ����������֡���൱�ҵ��ڳ������е�֡�ʡ�
     * �������������ĳЩ���ܽ���ʧЧ����������� offset ���Եȡ�
     * @example
     * TypeScript ��񣬽����ο���
     * <pre>
     *     armature.cacheFrameRate = 24;
     * </pre>
     * @see dragonBones.DragonBonesData#frameRate
     * @see dragonBones.ArmatureData#frameRate
     * @version DragonBones 4.5
     * @language zh_CN
     */
    inline unsigned getCacheFrameRate() const
    {
        return _armatureData->cacheFrameRate;
    }
    void setCacheFrameRate(unsigned value);
    /**
     * - The armature name.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �Ǽ����ơ�
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline const std::string& getName() const
    {
        return _armatureData->name;
    }
    /**
     * - The armature data.
     * @see dragonBones.ArmatureData
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �Ǽ����ݡ�
     * @see dragonBones.ArmatureData
     * @version DragonBones 4.5
     * @language zh_CN
     */
    inline const ArmatureData* getArmatureData() const
    {
        return _armatureData;
    }
    /**
     * - The animation player.
     * @see dragonBones.Animation
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ������������
     * @see dragonBones.Animation
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline Animation* getAnimation() const
    {
        return _animation;
    }
    /**
     * @pivate
     */
    inline IArmatureProxy* getProxy() const
    {
        return _proxy;
    }
    /**
     * - The EventDispatcher instance of the armature.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �ùǼܵ� EventDispatcher ʵ����
     * @version DragonBones 4.5
     * @language zh_CN
     */
    inline IEventDispatcher* getEventDispatcher() const
    {
        return _proxy;
    }
    /**
     * - The display container.
     * The display of the slot is displayed as the parent.
     * Depending on the rendering engine, the type will be different, usually the DisplayObjectContainer type.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��ʾ����ʵ����
     * ��۵���ʾ���󶼻��Դ���ʾ����Ϊ������
     * ������Ⱦ����Ĳ�ͬ�����ͻ᲻ͬ��ͨ���� DisplayObjectContainer ���͡�
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline void* getDisplay() const
    {
        return _display;
    }
    /**
     * @private
     */
    inline void* getReplacedTexture() const
    {
        return _replacedTexture;
    }
    void setReplacedTexture(void* value);
    /**
     * @inheritDoc
     */
    inline WorldClock* getClock() const override
    {
        return _clock;
    }
    void setClock(WorldClock* value) override;
    /**
     * - Get the parent slot which the armature belongs to.
     * @see dragonBones.Slot
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �ùǼ������ĸ���ۡ�
     * @see dragonBones.Slot
     * @version DragonBones 4.5
     * @language zh_CN
     */
    inline Slot* getParent() const
    {
        return _parent;
    }

public: // For WebAssembly.
    IAnimatable* getAnimatable() const { return (IAnimatable*)this; }
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_ARMATURE_H
