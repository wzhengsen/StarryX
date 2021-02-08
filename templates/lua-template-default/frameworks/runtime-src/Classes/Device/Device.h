#pragma once
namespace StarryX {
    class Device final {
    public:
        /*
            Desc:       �õ������ٷֱȡ�
            Return:     ���ص�ǰ�����ٷֱȡ�
         */
        static double GetBatteryPercent() noexcept;

        /*
            Desc:       ��ǰ�Ƿ����ڳ�硣
            Return:     ���ص�ǰ�Ƿ����ڳ�硣
        */
        static bool IsBatteryCharge() noexcept;


        // �����������͡�
        enum class NetworkType {
            None,
            Wifi,
            Mobile,
            Other
        };

        /*
            Desc:       ��ȡwifi�ź�ǿ�ȡ�
            Return:     �����ź�ǿ�ȣ�0-5��
                        1Ϊ������5Ϊ��ǿ��0Ϊû��wifi�ź�(��������������)��
        */
        static uint8_t GetWifiLevel() noexcept;

        /*
            Desc:       ��ȡ�����������͡�
            Return:     ���ص�ǰ�����������͡�
                        ��û������ʱ��������NetworkType::None��
                        ��windows������������ʱ�����ܷ���Network::Other��
        */
        static NetworkType GetNetworkType() noexcept;

        // ��ǰ�豸�������͡�
        enum class OrientationType {
            // ������
            Landscape,
            // ������
            Portrait,
            // �Զ����ͣ�����ϵͳ����windows�ϲ�һ�����á�
            Auto
        };

        /*
            Desc:���õ�ǰ�豸�ķ���
                �趨�������Ļ��������ת�����Զ�ʹ��
                config.DesignResolution������ֵ��������Ʒֱ��ʡ�
                ��������Landscape��Portrait�����򽫱������������ٴ�ʹ��
                �ú����ı䷽��
        */
        static void SetOrientation(OrientationType ot);

        /*
            Desc:��ȡ��ǰ�豸�ķ���
                ֻ�᷵��Landscape��Portrait�����᷵��Auto��
                ����Ҫ��ȡ��ǰ�Ƿ����Զ���ת����ʹ��IsAutoOrientation.
        */
        static OrientationType GetOrientation();

        /*
            Desc:��ȡ��ǰ�豸�ķ����Ƿ����Զ���ת�ġ�
        */
        static bool IsAutoOrientation() noexcept;

        /*
            Desc:   ��ȡIP��
        */
        static std::string GetIp();

        /*
            Desc:   ��ȡΨһʶ��ID��
        */
        static std::string GetId();

    private:
        static OrientationType curOriType;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 ||\
    CC_TARGET_PLATFORM == CC_PLATFORM_LINUX ||\
    CC_TARGET_PLATFORM == CC_PLATFORM_MAC
        static bool isAutoOri;
        static bool firstGetOri;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    public:
        static int InterfaceOrientationMask;
#endif
    };
}
