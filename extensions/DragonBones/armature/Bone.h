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
#ifndef DRAGONBONES_BONE_H
#define DRAGONBONES_BONE_H

#include "TransformObject.h"
#include "../model/ArmatureData.h"
#include "../animation/AnimationState.h"

DRAGONBONES_NAMESPACE_BEGIN
/**
 * - Bone is one of the most important logical units in the armature animation system,
 * and is responsible for the realization of translate, rotation, scaling in the animations.
 * A armature can contain multiple bones.
 * @see dragonBones.BoneData
 * @see dragonBones.Armature
 * @see dragonBones.Slot
 * @version DragonBones 3.0
 * @language en_US
 */
/**
 * - �����ڹ���������ϵ��������Ҫ���߼���Ԫ֮һ�����𶯻��е�ƽ�ơ���ת�����ŵ�ʵ�֡�
 * һ���Ǽ��п��԰������������
 * @see dragonBones.BoneData
 * @see dragonBones.Armature
 * @see dragonBones.Slot
 * @version DragonBones 3.0
 * @language zh_CN
 */
class Bone final : public TransformObject
{
    BIND_CLASS_TYPE_A(Bone);

public:
    /**
     * - The offset mode.
     * @see #offset
     * @version DragonBones 5.5
     * @language en_US
     */
    /**
     * - ƫ��ģʽ��
     * @see #offset
     * @version DragonBones 5.5
     * @language zh_CN
     */
    OffsetMode offsetMode;
    /**
     * @internal
     */
    Transform animationPose;
    /**
     * @internal
     */
    bool _transformDirty;
    /**
     * @internal
     */
    bool _childrenTransformDirty;
    /**
     * @internal
     */
    bool _hasConstraint;
    /**
     * @internal
     */
    BlendState _blendState;
    /**
     * @internal
     */
    const BoneData* _boneData;
    /**
     * @internal
     */
    std::vector<int>* _cachedFrameIndices;

protected:
    bool _localDirty;
    bool _visible;
    int _cachedFrameIndex;
    /**
     * @private
     */
    Bone* _parent;

protected:
    void _onClear() override;
    void _updateGlobalTransformMatrix(bool isCache);

public:
    /**
     * @internal
     */
    void init(const BoneData* boneData, Armature* armatureValue);
    /**
     * @internal
     */
    void update(int cacheFrameIndex);
    /**
     * @internal
     */
    void updateByConstraint();
    /**
     * - Forces the bone to update the transform in the next frame.
     * When the bone is not animated or its animation state is finished, the bone will not continue to update,
     * and when the skeleton must be updated for some reason, the method needs to be called explicitly.
     * @example
     * TypeScript style, for reference only.
     * <pre>
     *     let bone = armature.getBone("arm");
     *     bone.offset.scaleX = 2.0;
     *     bone.invalidUpdate();
     * </pre>
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ǿ�ƹ�������һ֡���±任��
     * ���ù���û�ж���״̬���䶯��״̬�������ʱ�����������ڼ������£�����ʱ����ĳЩԭ�������¹���ʱ������Ҫ��ʽ���ø÷�����
     * @example
     * TypeScript ��񣬽����ο���
     * <pre>
     *     let bone = armature.getBone("arm");
     *     bone.offset.scaleX = 2.0;
     *     bone.invalidUpdate();
     * </pre>
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline void invalidUpdate()
    {
        _transformDirty = true;
    }
    /**
     * - Check whether the bone contains a specific bone.
     * @see dragonBones.Bone
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ���ù����Ƿ�����ض��Ĺ�����
     * @see dragonBones.Bone
     * @version DragonBones 3.0
     * @language zh_CN
     */
    bool contains(const Bone* value) const;
    /**
     * - The bone data.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �������ݡ�
     * @version DragonBones 4.5
     * @language zh_CN
     */
    inline const BoneData* getBoneData() const
    {
        return _boneData;
    }
    /**
     * - The visible of all slots in the bone.
     * @default true
     * @see dragonBones.Slot#visible
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �˹������в�۵Ŀɼ���
     * @default true
     * @see dragonBones.Slot#visible
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline bool getVisible() const
    {
        return _visible;
    }
    void setVisible(bool value);
    /**
     * - The bone name.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �������ơ�
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline const std::string& getName() const
    {
        return _boneData->name;
    }
    /**
     * - The parent bone to which it belongs.
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �����ĸ�������
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline Bone* getParent() const
    {
        return _parent;
    }

public: // For WebAssembly.
    inline int getOffsetMode() const { return (int)offsetMode; }
    inline void setOffsetMode(int value) { offsetMode = (OffsetMode)value; }
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_BONE_H
