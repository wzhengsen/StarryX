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
#ifndef DRAGONBONES_IEVENT_DISPATCHER_H
#define DRAGONBONES_IEVENT_DISPATCHER_H

#include "../core/DragonBones.h"

DRAGONBONES_NAMESPACE_BEGIN
/**
 * - The event dispatcher interface.
 * Dragonbones event dispatch usually relies on docking engine to implement, which defines the event method to be implemented when docking the engine.
 * @version DragonBones 4.5
 * @language en_US
 */
/**
 * - �¼��ɷ��ӿڡ�
 * DragonBones ���¼��ɷ�ͨ�������ڶԽӵ�������ʵ�֣��ýӿڶ����˶Խ�����ʱ��Ҫʵ�ֵ��¼�������
 * @version DragonBones 4.5
 * @language zh_CN
 */
class IEventDispatcher
{
    ABSTRACT_CLASS(IEventDispatcher)

public:
    /**
     * - Checks whether the object has any listeners registered for a specific type of event��
     * @param type - Event type.
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ����Ƿ�Ϊ�ض����¼�����ע�����κ���������
     * @param type - �¼����͡�
     * @version DragonBones 4.5
     * @language zh_CN
     */
    virtual bool hasDBEventListener(const std::string& type) const = 0;
    /**
     * - Dispatches an event into the event flow.
     * @param type - Event type.
     * @param eventObject - Event object.
     * @see dragonBones.EventObject
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - �����ض����¼����¼����С�
     * @param type - �¼����͡�
     * @param eventObject - �¼����ݡ�
     * @see dragonBones.EventObject
     * @version DragonBones 4.5
     * @language zh_CN
     */
    virtual void dispatchDBEvent(const std::string& type, EventObject* value) = 0;
    /**
     * - Add an event listener object so that the listener receives notification of an event.
     * @param type - Event type.
     * @param listener - Event listener.
     * @param thisObject - The listener function's "this".
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ����ض��¼����͵��¼�����������ʹ�������ܹ������¼�֪ͨ��
     * @param type - �¼����͡�
     * @param listener - �¼���������
     * @param thisObject - ���������󶨵� this ����
     * @version DragonBones 4.5
     * @language zh_CN
     */
    virtual void addDBEventListener(const std::string& type, const std::function<void(EventObject*)> & listener) = 0;
    /**
     * - Removes a listener from the object.
     * @param type - Event type.
     * @param listener - Event listener.
     * @param thisObject - The listener function's "this".
     * @version DragonBones 4.5
     * @language en_US
     */
    /**
     * - ɾ���ض��¼����͵���������
     * @param type - �¼����͡�
     * @param listener - �¼���������
     * @param thisObject - ���������󶨵� this ����
     * @version DragonBones 4.5
     * @language zh_CN
     */
    virtual void removeDBEventListener(const std::string& type, const std::function<void(EventObject*)>& listener) = 0;
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_IEVENT_DISPATCHER_H
