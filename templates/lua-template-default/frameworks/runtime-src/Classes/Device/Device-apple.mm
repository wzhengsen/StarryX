#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS ||\
CC_TARGET_PLATFORM == CC_PLATFORM_MAC
#include "Device/Device.h"
#import <ifaddrs.h>
#import <arpa/inet.h>
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#import <UIKit/UIKit.h>
#else
#import <IOKit/ps/IOPowerSources.h>
#import <IOKit/ps/IOPSKeys.h>
#import <CoreWLAN/CoreWLAN.h>
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
using namespace rapidjson;
StarryX::Device::OrientationType StarryX::Device::curOriType = StarryX::Device::OrientationType::Landscape;
bool StarryX::Device::isAutoOri = false;
bool StarryX::Device::firstGetOri = false;
#endif

using namespace StarryX;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
int StarryX::Device::InterfaceOrientationMask = UIInterfaceOrientationMaskLandscape;

double StarryX::Device::GetBatteryPercent() noexcept {
    [UIDevice currentDevice].batteryMonitoringEnabled = YES;
    double bl = [[UIDevice currentDevice] batteryLevel];
    if (bl < 0.0) {
        bl = 0.0;
    }
    return bl;
}

bool StarryX::Device::IsBatteryCharge() noexcept {
    return [UIDevice currentDevice].batteryState == UIDeviceBatteryStateCharging;
}

uint8_t StarryX::Device::GetWifiLevel() noexcept {
    uint8_t signalStrength = 0;
    if (@available(iOS 13.0, *)) {
        UIStatusBarManager *statusBarManager = [UIApplication sharedApplication].keyWindow.windowScene.statusBarManager;

        id statusBar = nil;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundeclared-selector"
        if ([statusBarManager respondsToSelector:@selector(createLocalStatusBar)]) {
            UIView *localStatusBar = [statusBarManager performSelector:@selector(createLocalStatusBar)];
            if ([localStatusBar respondsToSelector:@selector(statusBar)]) {
                statusBar = [localStatusBar performSelector:@selector(statusBar)];
            }
        }
#pragma clang diagnostic pop
        if (statusBar) {
            id currentData = [[statusBar valueForKeyPath:@"_statusBar"] valueForKeyPath:@"currentData"];
            id _wifiEntry = [currentData valueForKeyPath:@"wifiEntry"];
            //id _cellularEntry = [currentData valueForKeyPath:@"cellularEntry"];
            if (_wifiEntry && [[_wifiEntry valueForKeyPath:@"isEnabled"] boolValue]) {
                // If wifiEntry is enabled, is WiFi.
                if ([_wifiEntry isKindOfClass:NSClassFromString(@"_UIStatusBarDataIntegerEntry")]) {
                    // 层级：_UIStatusBarDataNetworkEntry、_UIStatusBarDataIntegerEntry、_UIStatusBarDataEntry
                    signalStrength = [[_wifiEntry valueForKey:@"displayValue"] unsignedCharValue];
                }
            }
        }
        if (signalStrength == 2) {
            signalStrength = 3;
        }
        else if (signalStrength == 3) {
            signalStrength = 5;
        }
        else if (signalStrength > 5) {
            signalStrength = 5;
        }
    }
    return signalStrength;
}

StarryX::Device::NetworkType StarryX::Device::GetNetworkType() noexcept {
    Device::NetworkType nt = Device::NetworkType::None;
    UIApplication *app = [UIApplication sharedApplication];
    id statusBar = nil;
    if (@available(iOS 13.0, *)) {
        UIStatusBarManager *statusBarManager = [UIApplication sharedApplication].keyWindow.windowScene.statusBarManager;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundeclared-selector"
        if ([statusBarManager respondsToSelector:@selector(createLocalStatusBar)]) {
            UIView *localStatusBar = [statusBarManager performSelector:@selector(createLocalStatusBar)];
            if ([localStatusBar respondsToSelector:@selector(statusBar)]) {
                statusBar = [localStatusBar performSelector:@selector(statusBar)];
            }
        }
#pragma clang diagnostic pop

        if (statusBar) {
            // UIStatusBarDataCellularEntry
            id currentData = [[statusBar valueForKeyPath:@"_statusBar"] valueForKeyPath:@"currentData"];
            id _wifiEntry = [currentData valueForKeyPath:@"wifiEntry"];
            id _cellularEntry = [currentData valueForKeyPath:@"cellularEntry"];
            if (_wifiEntry && [[_wifiEntry valueForKeyPath:@"isEnabled"] boolValue]) {
                // If wifiEntry is enabled, is WiFi.
                nt = NetworkType::Wifi;
            }
            else if (_cellularEntry && [[_cellularEntry valueForKeyPath:@"isEnabled"] boolValue]) {
                nt = NetworkType::Mobile;
            }
        }
    }
    return nt;
}

StarryX::Device::OrientationType StarryX::Device::GetOrientation() {
    UIInterfaceOrientation orientation = [UIApplication sharedApplication].statusBarOrientation;

    if (orientation == UIInterfaceOrientationLandscapeLeft || orientation == UIInterfaceOrientationLandscapeRight) {
        return Device::OrientationType::Landscape;
    }
    return Device::OrientationType::Portrait;
}

void StarryX::Device::SetOrientation(StarryX::Device::OrientationType ot) {
    if (ot == OrientationType::Auto && IsAutoOrientation()) {
        return;
    }
    else if (ot == GetOrientation()) {
        return;
    }
    if (ot == OrientationType::Landscape) {
        [[UIDevice currentDevice] setValue:@(UIInterfaceOrientationUnknown) forKey:@"orientation"];
        InterfaceOrientationMask = UIInterfaceOrientationMaskLandscape;
        [[UIDevice currentDevice] setValue:@(UIInterfaceOrientationLandscapeLeft) forKey:@"orientation"];
    }
    else if (ot == OrientationType::Portrait) {
        [[UIDevice currentDevice] setValue:@(UIInterfaceOrientationUnknown) forKey:@"orientation"];
        InterfaceOrientationMask = UIInterfaceOrientationMaskPortrait;
        [[UIDevice currentDevice] setValue:@(UIInterfaceOrientationPortrait) forKey:@"orientation"];
    }
    else {
        InterfaceOrientationMask = UIInterfaceOrientationMaskAllButUpsideDown;
    }
    [UIViewController attemptRotationToDeviceOrientation];
}

bool StarryX::Device::IsAutoOrientation() noexcept {
    return InterfaceOrientationMask == UIInterfaceOrientationMaskAllButUpsideDown || InterfaceOrientationMask == UIInterfaceOrientationMaskAll;
}
#else
double StarryX::Device::GetBatteryPercent() noexcept {
    double ret = 0.;
    CFTypeRef cft = IOPSCopyPowerSourcesInfo();
    if (!cft) {
        return ret;
    }
    CFArrayRef cftArr = IOPSCopyPowerSourcesList(cft);
    if (!cftArr) {
        CFRelease(cft);
        return ret;
    }
    NSArray *array = (__bridge NSArray*)cftArr;
    for (id v : array) {
        CFTypeRef ps = (CFTypeRef)v;
        CFDictionaryRef info = IOPSGetPowerSourceDescription(cft, ps);
        NSDictionary* dictInfo = (__bridge NSDictionary*)info;
        NSNumber* lvl = [dictInfo objectForKey:@kIOPSCurrentCapacityKey];
        NSNumber* maxLvl = [dictInfo objectForKey:@kIOPSMaxCapacityKey];
        signed int iLvl = [lvl unsignedIntegerValue];
        signed int iMaxLvl = [maxLvl unsignedIntegerValue];
        ret = (double)iLvl / (double)iMaxLvl;
        dictInfo = nil;
        break;
    }
    CFRelease(cftArr);
    CFRelease(cft);
    cftArr = nil;

    return ret;
}

bool StarryX::Device::IsBatteryCharge() noexcept {
    double ret = false;
    CFTypeRef cft = IOPSCopyPowerSourcesInfo();
    if (!cft) {
        return ret;
    }
    CFArrayRef cftArr = IOPSCopyPowerSourcesList(cft);
    if (!cftArr) {
        CFRelease(cft);
        return ret;
    }
    NSArray *array = (__bridge NSArray*)cftArr;
    for (id v : array) {
        CFTypeRef ps = (CFTypeRef)v;
        CFDictionaryRef info = IOPSGetPowerSourceDescription(cft, ps);
        NSDictionary* dictInfo = (__bridge NSDictionary*)info;
        NSNumber* charging = [dictInfo objectForKey:@kIOPSIsChargingKey];
        dictInfo = nil;
        break;
    }
    CFRelease(cftArr);
    CFRelease(cft);
    cftArr = nil;

    return ret;
}

uint8_t StarryX::Device::GetWifiLevel() noexcept {
    CWInterface* wifi = [[CWWiFiClient sharedWiFiClient] interface];
    if(!wifi || !wifi.powerOn || !wifi.ssid) {
        return 0;
    }
    uint8_t lvl = 0;
    auto rssi = 100 + wifi.rssiValue;;
    if (rssi > 0) {
        lvl = (rssi - 1) / 20 + 1;
        if (lvl > 5) {
            lvl = 5;
        }
    }
    return lvl;
}

StarryX::Device::NetworkType StarryX::Device::GetNetworkType() noexcept {
    CWInterface* wifi = [[CWWiFiClient sharedWiFiClient] interface];
    std::string addr = "";
    if(!wifi || !wifi.powerOn || !wifi.ssid) {
        addr = GetIp();
        if (addr.empty()) {
            return NetworkType::None;
        }
        return NetworkType::Other;
    }
    return NetworkType::Wifi;
}

StarryX::Device::OrientationType StarryX::Device::GetOrientation() {
    // 第一次的值，判断ConfigParser中的isLandscape作为依据。
    if (!firstGetOri) {
        firstGetOri = true;

        const cocos2d::FileUtils* const fu = cocos2d::FileUtils::getInstance();
        const std::string fileName = fu->fullPathForFilename("config.json");
        const std::string content = fu->getStringFromFile(fileName);
        Document docRootjson = Document();
        if (!docRootjson.Parse<ParseFlag::kParseNoFlags>(content.c_str()).HasParseError()) {
            if (docRootjson.HasMember("isLandscape") && docRootjson["isLandscape"].IsBool() && !docRootjson["isLandscape"].GetBool()) {
                curOriType = StarryX::Device::OrientationType::Portrait;
            }
        }
    }
    return curOriType;
}

void StarryX::Device::SetOrientation(StarryX::Device::OrientationType ot) {
    if (ot == curOriType) {
        return;
    }
    if (ot != StarryX::Device::OrientationType::Auto) {
        firstGetOri = true;
        isAutoOri = false;
        curOriType = ot;

        auto e = cocos2d::Director::getInstance()->getEventDispatcher();
        if (ot == StarryX::Device::OrientationType::Landscape) {
            e->dispatchCustomEvent("DeviceToLandscape");
        }
        else if (ot == StarryX::Device::OrientationType::Portrait) {
            e->dispatchCustomEvent("DeviceToPortrait");
        }
    }
    else {
        isAutoOri = true;
    }
}

bool StarryX::Device::IsAutoOrientation() noexcept {
    return isAutoOri;
}
#endif
std::string StarryX::Device::GetIp() {
    std::string address = "";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;

    success = getifaddrs(&interfaces);
    if (success == 0) { // 0 表示获取成功

        temp_addr = interfaces;
        while (temp_addr != NULL) {
            if( temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection
                const std::string ifa_name = temp_addr->ifa_name;
                if (ifa_name.find("en") == 0) {
                    // Get NSString from C String
                    address = inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr);
                    if (!address.empty()) {
                        break;
                    }
                }
            }

            temp_addr = temp_addr->ifa_next;
        }
    }

    freeifaddrs(interfaces);
    return address;
}


static NSMutableDictionary* GetKeychainQuery(NSString* service) {
    return [NSMutableDictionary dictionaryWithObjectsAndKeys:
            (id)kSecClassGenericPassword,(id)kSecClass,
            service,(id)kSecAttrService,
            service,(id)kSecAttrAccount,
            (id)kSecAttrAccessibleAfterFirstUnlock,(id)kSecAttrAccessible,
            nil];
}

static void SaveKeyData(NSString* service,id data) {
    //Get search dictionary
    NSMutableDictionary* keychainQuery = GetKeychainQuery(service);

    //Delete old item before add new item
    SecItemDelete((CFDictionaryRef)keychainQuery);

    //Add new object to searchdictionary(Attention:the data format)
    [keychainQuery setObject:[NSKeyedArchiver archivedDataWithRootObject:data] forKey:(id)kSecValueData];

    //Add item to keychain with the searchdictionary
    SecItemAdd((CFDictionaryRef)keychainQuery,NULL);
}

static id LoadKeyData(NSString* service) {
    id ret = nil;

    NSMutableDictionary*keychainQuery = GetKeychainQuery(service);
    //Configure the search setting

    //Since in our simple case we areexpecting only a single attribute to be returned (the password) wecan set the attribute kSecReturnData to kCFBooleanTrue
    [keychainQuery setObject:(id)kCFBooleanTrue forKey:(id)kSecReturnData];
    [keychainQuery setObject:(id)kSecMatchLimitOne forKey:(id)kSecMatchLimit];

    CFDataRef keyData = NULL;
    if(SecItemCopyMatching((CFDictionaryRef)keychainQuery,(CFTypeRef*)&keyData) == noErr){
        @try{
            ret =[NSKeyedUnarchiver unarchiveObjectWithData:(__bridge NSData*)keyData];
        }@catch(NSException* e) {
            NSLog(@"Unarchive of %@ failed: %@",service, e);
        }@finally{
        }
    }

    if(keyData) {
        CFRelease(keyData);
    }
    return ret;
}

static void DeleteKeyData(NSString* service) {
    NSMutableDictionary* keychainQuery = GetKeychainQuery(service);
    SecItemDelete((CFDictionaryRef)keychainQuery);
}

std::string StarryX::Device::GetId() {
    static std::string dId = std::string();
    if (dId.empty()) {
        NSString* ID = [NSString stringWithFormat:@"%@.%@",[[NSBundle mainBundle] bundleIdentifier],@"UniqueID"];
        NSString* strUUID = (NSString*)LoadKeyData(ID);

        //首次执行该方法时，uuid为空
        if(!strUUID || [strUUID isEqualToString:@""]) {
            //生成一个uuid的方法
            CFUUIDRef uuidRef = CFUUIDCreate(kCFAllocatorDefault);
            strUUID = (NSString*)CFBridgingRelease(CFUUIDCreateString(kCFAllocatorDefault,uuidRef));
            //将该uuid保存到keychain
            SaveKeyData(ID,strUUID);
        }
        dId = [strUUID UTF8String];
    }

    return dId;
}
#endif
