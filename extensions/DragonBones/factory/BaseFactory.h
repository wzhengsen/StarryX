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
#ifndef DRAGONBONES_BASE_FACTORY_H
#define DRAGONBONES_BASE_FACTORY_H

#include "../parser/JSONDataParser.h"
#include "../parser/BinaryDataParser.h"
#include "../armature/Armature.h"
#include "../armature/Bone.h"
#include "../armature/Slot.h"
#include "../armature/Constraint.h"
#include "../animation/Animation.h"

DRAGONBONES_NAMESPACE_BEGIN
/**
 * - Base class for the factory that create the armatures. (Typically only one global factory instance is required)
 * The factory instance create armatures by parsed and added DragonBonesData instances and TextureAtlasData instances.
 * Once the data has been parsed, it has been cached in the factory instance and does not need to be parsed again until it is cleared by the factory instance.
 * @see dragonBones.DragonBonesData
 * @see dragonBones.TextureAtlasData
 * @see dragonBones.ArmatureData
 * @see dragonBones.Armature
 * @version DragonBones 3.0
 * @language en_US
 */
/**
 * - �����ǼܵĹ������ࡣ ��ͨ��ֻ��Ҫһ��ȫ�ֹ���ʵ����
 * ����ͨ����������ӵ� DragonBonesData ʵ���� TextureAtlasData ʵ���������Ǽܡ�
 * �����ݱ�������֮���Ѿ���ӵ������У���û�б���������֮ǰ������Ҫ�ٴν�����
 * @see dragonBones.DragonBonesData
 * @see dragonBones.TextureAtlasData
 * @see dragonBones.ArmatureData
 * @see dragonBones.Armature
 * @version DragonBones 3.0
 * @language zh_CN
 */
class BaseFactory
{
protected:
    static JSONDataParser _jsonParser;
    static BinaryDataParser _binaryParser;

public:
    /**
     * @private
     */
    bool autoSearch;

protected:
    std::map<std::string, DragonBonesData*> _dragonBonesDataMap;
    std::map<std::string, std::vector<TextureAtlasData*>> _textureAtlasDataMap;
    DragonBones* _dragonBones;
    DataParser* _dataParser;

public:
    /**
     * - Create a factory instance. (typically only one global factory instance is required)
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ����һ������ʵ���� ��ͨ��ֻ��Ҫһ��ȫ�ֹ���ʵ����
     * @version DragonBones 3.0
     * @language zh_CN
     */
    BaseFactory(DataParser* dataParser = nullptr) :
        autoSearch(false),
        _dragonBonesDataMap(),
        _textureAtlasDataMap(),
        _dragonBones(nullptr),
        _dataParser(nullptr)
    {
        _dataParser = dataParser != nullptr ? dataParser : &BaseFactory::_jsonParser;
    }
    virtual ~BaseFactory()
    {
        clear();

        _dragonBones = nullptr;
        _dataParser = nullptr;
    }

protected:
    virtual inline bool _isSupportMesh() const
    {
        return true;
    }
    virtual TextureData* _getTextureData(const std::string& textureAtlasName, const std::string& textureName) const;
    virtual bool _fillBuildArmaturePackage(
        BuildArmaturePackage& dataPackage,
        const std::string& dragonBonesName, const std::string& armatureName, const std::string& skinName, const std::string& textureAtlasName
    ) const;
    virtual void _buildBones(const BuildArmaturePackage& dataPackage, Armature* armature) const;
    /**
     * @private
     */
    virtual void _buildSlots(const BuildArmaturePackage& dataPackage, Armature* armature) const;
    virtual Armature* _buildChildArmature(const BuildArmaturePackage* dataPackage, Slot* slot, DisplayData* displayData) const;
    virtual std::pair<void*, DisplayType> _getSlotDisplay(const BuildArmaturePackage* dataPackage, DisplayData* displayData, DisplayData* rawDisplayData, Slot* slot) const;
    virtual TextureAtlasData* _buildTextureAtlasData(TextureAtlasData* textureAtlasData, void* textureAtlas) const = 0;
    virtual Armature* _buildArmature(const BuildArmaturePackage& dataPackage) const = 0;
    virtual Slot* _buildSlot(const BuildArmaturePackage& dataPackage, const SlotData* slotData, Armature* armature) const = 0;

public:
    /**
     * - Parse the raw data to a DragonBonesData instance and cache it to the factory.
     * @param rawData - The raw data.
     * @param name - Specify a cache name for the instance so that the instance can be obtained through this name. (If not set, use the instance name instead)
     * @param scale - Specify a scaling value for all armatures. (Default: 1.0)
     * @returns DragonBonesData instance
     * @see #getDragonBonesData()
     * @see #addDragonBonesData()
     * @see #removeDragonBonesData()
     * @see dragonBones.DragonBonesData
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ��ԭʼ���ݽ���Ϊ DragonBonesData ʵ���������浽�����С�
     * @param rawData - ԭʼ���ݡ�
     * @param name - Ϊ��ʵ��ָ��һ���������ƣ��Ա����ͨ�������ƻ�ȡ��ʵ���� �����δ���ã���ʹ�ø�ʵ���е����ƣ�
     * @param scale - Ϊ���еĹǼ�ָ��һ������ֵ�� ��Ĭ��: 1.0��
     * @returns DragonBonesData ʵ��
     * @see #getDragonBonesData()
     * @see #addDragonBonesData()
     * @see #removeDragonBonesData()
     * @see dragonBones.DragonBonesData
     * @version DragonBones 4.5
     * @language zh_CN
     */
    virtual DragonBonesData* parseDragonBonesData(const char* rawData, const std::string& name = "", float scale = 1.0f);
    /**
     * - Parse the raw texture atlas data and the texture atlas object to a TextureAtlasData instance and cache it to the factory.
     * @param rawData - The raw texture atlas data.
     * @param textureAtlas - The texture atlas object.
     * @param name - Specify a cache name for the instance so that the instance can be obtained through this name. (If not set, use the instance name instead)
     * @param scale - Specify a scaling value for the map set. (Default: 1.0)
     * @returns TextureAtlasData instance
     * @see #getTextureAtlasData()
     * @see #addTextureAtlasData()
     * @see #removeTextureAtlasData()
     * @see dragonBones.TextureAtlasData
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ��ԭʼ��ͼ�����ݺ���ͼ���������Ϊ TextureAtlasData ʵ���������浽�����С�
     * @param rawData - ԭʼ��ͼ�����ݡ�
     * @param textureAtlas - ��ͼ������
     * @param name - Ϊ��ʵ��ָ��һ���������ƣ��Ա����ͨ�������ƻ�ȡ��ʵ���� �����δ���ã���ʹ�ø�ʵ���е����ƣ�
     * @param scale - Ϊ��ͼ��ָ��һ������ֵ�� ��Ĭ��: 1.0��
     * @returns TextureAtlasData ʵ��
     * @see #getTextureAtlasData()
     * @see #addTextureAtlasData()
     * @see #removeTextureAtlasData()
     * @see dragonBones.TextureAtlasData
     * @version DragonBones 4.5
     * @language zh_CN
     */
    virtual TextureAtlasData* parseTextureAtlasData(const char* rawData, void* textureAtlas, const std::string& name = "", float scale = 1.0f);
    /**
     * - Get a specific DragonBonesData instance.
     * @param name - The DragonBonesData instance cache name.
     * @returns DragonBonesData instance
     * @see #parseDragonBonesData()
     * @see #addDragonBonesData()
     * @see #removeDragonBonesData()
     * @see dragonBones.DragonBonesData
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��ȡ�ض��� DragonBonesData ʵ����
     * @param name - DragonBonesData ʵ���Ļ������ơ�
     * @returns DragonBonesData ʵ��
     * @see #parseDragonBonesData()
     * @see #addDragonBonesData()
     * @see #removeDragonBonesData()
     * @see dragonBones.DragonBonesData
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline DragonBonesData* getDragonBonesData(const std::string& name) const
    {
        return mapFind(_dragonBonesDataMap, name);
    }
    /**
     * - Cache a DragonBonesData instance to the factory.
     * @param data - The DragonBonesData instance.
     * @param name - Specify a cache name for the instance so that the instance can be obtained through this name. (if not set, use the instance name instead)
     * @see #parseDragonBonesData()
     * @see #getDragonBonesData()
     * @see #removeDragonBonesData()
     * @see dragonBones.DragonBonesData
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �� DragonBonesData ʵ�����浽�����С�
     * @param data - DragonBonesData ʵ����
     * @param name - Ϊ��ʵ��ָ��һ���������ƣ��Ա����ͨ�������ƻ�ȡ��ʵ���� �����δ���ã���ʹ�ø�ʵ���е����ƣ�
     * @see #parseDragonBonesData()
     * @see #getDragonBonesData()
     * @see #removeDragonBonesData()
     * @see dragonBones.DragonBonesData
     * @version DragonBones 3.0
     * @language zh_CN
     */
    virtual void addDragonBonesData(DragonBonesData* data, const std::string& name = "");
    /**
     * - Remove a DragonBonesData instance.
     * @param name - The DragonBonesData instance cache name.
     * @param disposeData - Whether to dispose data. (Default: true)
     * @see #parseDragonBonesData()
     * @see #getDragonBonesData()
     * @see #addDragonBonesData()
     * @see dragonBones.DragonBonesData
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �Ƴ� DragonBonesData ʵ����
     * @param name - DragonBonesData ʵ���������ơ�
     * @param disposeData - �Ƿ��ͷ����ݡ� ��Ĭ��: true��
     * @see #parseDragonBonesData()
     * @see #getDragonBonesData()
     * @see #addDragonBonesData()
     * @see dragonBones.DragonBonesData
     * @version DragonBones 3.0
     * @language zh_CN
     */
    virtual void removeDragonBonesData(const std::string& name, bool disposeData = true);
    /**
     * - Get a list of specific TextureAtlasData instances.
     * @param name - The TextureAtlasData cahce name.
     * @see #parseTextureAtlasData()
     * @see #addTextureAtlasData()
     * @see #removeTextureAtlasData()
     * @see dragonBones.TextureAtlasData
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ��ȡ�ض��� TextureAtlasData ʵ���б�
     * @param name - TextureAtlasData ʵ���������ơ�
     * @see #parseTextureAtlasData()
     * @see #addTextureAtlasData()
     * @see #removeTextureAtlasData()
     * @see dragonBones.TextureAtlasData
     * @version DragonBones 3.0
     * @language zh_CN
     */
    inline std::vector<TextureAtlasData*>* getTextureAtlasData(const std::string& name)
    {
        return mapFindB(_textureAtlasDataMap, name);
    }
    /**
     * - Cache a TextureAtlasData instance to the factory.
     * @param data - The TextureAtlasData instance.
     * @param name - Specify a cache name for the instance so that the instance can be obtained through this name. (if not set, use the instance name instead)
     * @see #parseTextureAtlasData()
     * @see #getTextureAtlasData()
     * @see #removeTextureAtlasData()
     * @see dragonBones.TextureAtlasData
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �� TextureAtlasData ʵ�����浽�����С�
     * @param data - TextureAtlasData ʵ����
     * @param name - Ϊ��ʵ��ָ��һ���������ƣ��Ա����ͨ�������ƻ�ȡ��ʵ���� �����δ���ã���ʹ�ø�ʵ���е����ƣ�
     * @see #parseTextureAtlasData()
     * @see #getTextureAtlasData()
     * @see #removeTextureAtlasData()
     * @see dragonBones.TextureAtlasData
     * @version DragonBones 3.0
     * @language zh_CN
     */
    virtual void addTextureAtlasData(TextureAtlasData* data, const std::string& name = "");
    /**
     * - Remove a TextureAtlasData instance.
     * @param name - The TextureAtlasData instance cache name.
     * @param disposeData - Whether to dispose data.
     * @see #parseTextureAtlasData()
     * @see #getTextureAtlasData()
     * @see #addTextureAtlasData()
     * @see dragonBones.TextureAtlasData
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - �Ƴ� TextureAtlasData ʵ����
     * @param name - TextureAtlasData ʵ���Ļ������ơ�
     * @param disposeData - �Ƿ��ͷ����ݡ�
     * @see #parseTextureAtlasData()
     * @see #getTextureAtlasData()
     * @see #addTextureAtlasData()
     * @see dragonBones.TextureAtlasData
     * @version DragonBones 3.0
     * @language zh_CN
     */
    virtual void removeTextureAtlasData(const std::string& name, bool disposeData = true);
    /**
     * - Get a specific armature data.
     * @param name - The armature data name.
     * @param dragonBonesName - The cached name for DragonbonesData instance.
     * @see dragonBones.ArmatureData
     * @version DragonBones 5.1
     * @language en_US
     */
    /**
     * - ��ȡ�ض��ĹǼ����ݡ�
     * @param name - �Ǽ��������ơ�
     * @param dragonBonesName - DragonBonesData ʵ���Ļ������ơ�
     * @see dragonBones.ArmatureData
     * @version DragonBones 5.1
     * @language zh_CN
     */
    virtual ArmatureData* getArmatureData(const std::string& name, const std::string& dragonBonesName = "") const;
    /**
     * - Clear all cached DragonBonesData instances and TextureAtlasData instances.
     * @param disposeData - Whether to dispose data.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ������������ DragonBonesData ʵ���� TextureAtlasData ʵ����
     * @param disposeData - �Ƿ��ͷ����ݡ�
     * @version DragonBones 4.5
     * @language zh_CN
     */
    virtual void clear(bool disposeData = true);
    /**
     * - Create a armature from cached DragonBonesData instances and TextureAtlasData instances.
     * Note that when the created armature that is no longer in use, you need to explicitly dispose {@link #dragonBones.Armature#dispose()}.
     * @param armatureName - The armature data name.
     * @param dragonBonesName - The cached name of the DragonBonesData instance. (If not set, all DragonBonesData instances are retrieved, and when multiple DragonBonesData instances contain a the same name armature data, it may not be possible to accurately create a specific armature)
     * @param skinName - The skin name, you can set a different ArmatureData name to share it's skin data. (If not set, use the default skin data)
     * @returns The armature.
     * @example
     * TypeScript style, for reference only.
     * <pre>
     *     let armature = factory.buildArmature("armatureName", "dragonBonesName");
     *     armature.clock = factory.clock;
     * </pre>
     * @see dragonBones.DragonBonesData
     * @see dragonBones.ArmatureData
     * @version DragonBones 3.0
     * @language en_US
     */
    /**
     * - ͨ������� DragonBonesData ʵ���� TextureAtlasData ʵ������һ���Ǽܡ�
     * ע�⣬�����ĹǼܲ���ʹ��ʱ����Ҫ��ʽ�ͷ� {@link #dragonBones.Armature#dispose()}��
     * @param armatureName - �Ǽ��������ơ�
     * @param dragonBonesName - DragonBonesData ʵ���Ļ������ơ� �����δ���ã����������е� DragonBonesData ʵ��������� DragonBonesData ʵ���а���ͬ���ĹǼ�����ʱ�������޷�׼ȷ�Ĵ������ض��ĹǼܣ�
     * @param skinName - Ƥ�����ƣ���������һ�������Ǽ�����������������Ƥ�����ݡ������δ���ã���ʹ��Ĭ�ϵ�Ƥ�����ݣ�
     * @returns �Ǽܡ�
     * @example
     * TypeScript ��񣬽����ο���
     * <pre>
     *     let armature = factory.buildArmature("armatureName", "dragonBonesName");
     *     armature.clock = factory.clock;
     * </pre>
     * @see dragonBones.DragonBonesData
     * @see dragonBones.ArmatureData
     * @version DragonBones 3.0
     * @language zh_CN
     */
    virtual Armature* buildArmature(const std::string& armatureName, const std::string& dragonBonesName = "", const std::string& skinName = "", const std::string & textureAtlasName = "") const;
    /**
     * @private
     */
    virtual void replaceDisplay(Slot* slot, DisplayData* displayData, int displayIndex) const;
    /**
     * - Replaces the current display data for a particular slot with a specific display data.
     * Specify display data with "dragonBonesName/armatureName/slotName/displayName".
     * @param dragonBonesName - The DragonBonesData instance cache name.
     * @param armatureName - The armature data name.
     * @param slotName - The slot data name.
     * @param displayName - The display data name.
     * @param slot - The slot.
     * @param displayIndex - The index of the display data that is replaced. (If it is not set, replaces the current display data)
     * @example
     * TypeScript style, for reference only.
     * <pre>
     *     let slot = armature.getSlot("weapon");
     *     factory.replaceSlotDisplay("dragonBonesName", "armatureName", "slotName", "displayName", slot);
     * </pre>
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ���ض�����ʾ���������滻�ض���۵�ǰ����ʾ�������ݡ�
     * �� "dragonBonesName/armatureName/slotName/displayName" ָ����ʾ�������ݡ�
     * @param dragonBonesName - DragonBonesData ʵ���Ļ������ơ�
     * @param armatureName - �Ǽ��������ơ�
     * @param slotName - ����������ơ�
     * @param displayName - ��ʾ�����������ơ�
     * @param slot - ��ۡ�
     * @param displayIndex - ���滻����ʾ�������ݵ������� �����δ���ã����滻��ǰ����ʾ�������ݣ�
     * @example
     * TypeScript ��񣬽����ο���
     * <pre>
     *     let slot = armature.getSlot("weapon");
     *     factory.replaceSlotDisplay("dragonBonesName", "armatureName", "slotName", "displayName", slot);
     * </pre>
     * @version DragonBones 4.5
     * @language zh_CN
     */
    virtual bool replaceSlotDisplay(
        const std::string& dragonBonesName, const std::string& armatureName, const std::string& slotName, const std::string& displayName,
        Slot* slot, int displayIndex = -1
    ) const;
    /**
     * @private
     */
    virtual bool replaceSlotDisplayList(
        const std::string& dragonBonesName, const std::string& armatureName, const std::string& slotName,
        Slot* slot
    ) const;
    /**
     * - Share specific skin data with specific armature.
     * @param armature - The armature.
     * @param skin - The skin data.
     * @param isOverride - Whether it completely override the original skin. (Default: false)
     * @param exclude - A list of slot names that do not need to be replace.
     * @example
     * TypeScript style, for reference only.
     * <pre>
     *     let armatureA = factory.buildArmature("armatureA", "dragonBonesA");
     *     let armatureDataB = factory.getArmatureData("armatureB", "dragonBonesB");
     *     if (armatureDataB && armatureDataB.defaultSkin) {
     *     factory.replaceSkin(armatureA, armatureDataB.defaultSkin, false, ["arm_l", "weapon_l"]);
     *     }
     * </pre>
     * @see dragonBones.Armature
     * @see dragonBones.SkinData
     * @version DragonBones 5.6
     * @language en_US
     */
    /**
     * - ���ض���Ƥ�����ݹ�����ض��ĹǼ�ʹ�á�
     * @param armature - �Ǽܡ�
     * @param skin - Ƥ�����ݡ�
     * @param isOverride - �Ƿ���ȫ����ԭ����Ƥ���� ��Ĭ��: false��
     * @param exclude - ����Ҫ���滻�Ĳ�������б�
     * @example
     * TypeScript ��񣬽����ο���
     * <pre>
     *     let armatureA = factory.buildArmature("armatureA", "dragonBonesA");
     *     let armatureDataB = factory.getArmatureData("armatureB", "dragonBonesB");
     *     if (armatureDataB && armatureDataB.defaultSkin) {
     *     factory.replaceSkin(armatureA, armatureDataB.defaultSkin, false, ["arm_l", "weapon_l"]);
     *     }
     * </pre>
     * @see dragonBones.Armature
     * @see dragonBones.SkinData
     * @version DragonBones 5.6
     * @language zh_CN
     */
    virtual bool replaceSkin(Armature* armature, SkinData* skin, bool isOverride = false, const std::vector<std::string>* exclude = nullptr) const;
    /**
     * - Replaces the existing animation data for a specific armature with the animation data for the specific armature data.
     * This enables you to make a armature template so that other armature without animations can share it's animations.
     * @param armature - The armtaure.
     * @param armatureData - The armature data.
     * @param isOverride - Whether to completely overwrite the original animation. (Default: false)
     * @example
     * TypeScript style, for reference only.
     * <pre>
     *     let armatureA = factory.buildArmature("armatureA", "dragonBonesA");
     *     let armatureDataB = factory.getArmatureData("armatureB", "dragonBonesB");
     *     if (armatureDataB) {
     *     factory.replaceAnimation(armatureA, armatureDataB);
     *     }
     * </pre>
     * @see dragonBones.Armature
     * @see dragonBones.ArmatureData
     * @version DragonBones 5.6
     * @language en_US
     */
    /**
     * - ���ض��Ǽ����ݵĶ��������滻�ض��Ǽ����еĶ������ݡ�
     * ��������ʵ������һ���Ǽܶ���ģ�壬������û�����������ĹǼܹ���ö�����
     * @param armature - �Ǽܡ�
     * @param armatureData - �Ǽ����ݡ�
     * @param isOverride - �Ƿ���ȫ����ԭ���Ķ�������Ĭ��: false��
     * @example
     * TypeScript ��񣬽����ο���
     * <pre>
     *     let armatureA = factory.buildArmature("armatureA", "dragonBonesA");
     *     let armatureDataB = factory.getArmatureData("armatureB", "dragonBonesB");
     *     if (armatureDataB) {
     *     factory.replaceAnimation(armatureA, armatureDataB);
     *     }
     * </pre>
     * @see dragonBones.Armature
     * @see dragonBones.ArmatureData
     * @version DragonBones 5.6
     * @language zh_CN
     */
    virtual bool replaceAnimation(Armature* armature, ArmatureData* armatureData, bool isReplaceAll = true) const;
    /**
     * @private
     */
    inline const std::map<std::string, std::vector<TextureAtlasData*>>& getAllTextureAtlasData() const
    {
        return _textureAtlasDataMap;
    }
    /**
     * @private
     */
    inline const std::map<std::string, DragonBonesData*>& getAllDragonBonesData() const
    {
        return _dragonBonesDataMap;
    }
    /**
     * - An Worldclock instance updated by engine.
     * @version DragonBones 5.7
     * @language en_US
     */
    /**
     * - ������������ WorldClock ʵ����
     * @version DragonBones 5.7
     * @language zh_CN
     */
    inline WorldClock* getClock() const 
    {
        return _dragonBones->getClock();
    }

    /**
     * - Deprecated, please refer to {@link #replaceSkin}.
     * @deprecated
     * @language en_US
     */
    /**
     * - �ѷ�������ο� {@link #replaceSkin}��
     * @deprecated
     * @language zh_CN
     */
    inline bool changeSkin(Armature* armature, SkinData* skin, const std::vector<std::string>* exclude = nullptr) const
    {
        return replaceSkin(armature, skin, false, exclude);
    }
};
/**
 * @internal
 */
class BuildArmaturePackage
{
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(BuildArmaturePackage)

public:
    std::string dataName;
    std::string textureAtlasName;
    DragonBonesData* data;
    ArmatureData* armature;
    SkinData* skin;

    BuildArmaturePackage() :
        dataName(),
        textureAtlasName(),
        data(nullptr),
        armature(nullptr),
        skin(nullptr)
    {}
    ~BuildArmaturePackage() {}
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_BASE_FACTORY_H
