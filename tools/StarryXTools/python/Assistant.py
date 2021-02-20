#!/usr/bin/env python3

import os
import shutil
import Functions
from Template import ConfigTemplate,ProjectManifestTemplate,VersionManifestTemplate

class Assistant():
    '''助理类，能帮助处理Lua编译/文件夹同步/加密/热更/上传/版本管理等。
    '''
    _TempDir = "../.tempDir"
    _VersionManifest = "version.manifest.json"
    _ProjectManifest = "project.manifest.json"
    _VersionDir = "Version"
    _ModuleFileName = "Module.json"

    def __init__(self,srcPath):
        '''
        Param:

        srcPath             源目录。
        '''

        self._configFileName = os.path.join(srcPath,Assistant._ModuleFileName)
        self._srcPath = srcPath
        self._config = Functions.LoadJson(self._configFileName)
        self._isDefault = self._config == None
        if self._isDefault:
            # 没有配置时，创建一个默认配置，但该配置并不保存，也不产生版本信息。
            self._config = ConfigTemplate.copy()


    def __del__(self):
        if self._config.get("exitSave"):
            Functions.SaveJson(self._configFileName,self._config)

    def GetModules(self):
        return self._config["modules"].copy()

    def CreateDefaultConfig(self):
        """在当前源目录下创建一个默认的配置文件。

        返回：

            boolean     若当前目录下已有配置文件，返回False;
                        否则返回True。
        """
        if not self._isDefault:
            return False
        self._config = ConfigTemplate.copy()
        Functions.SaveJson(self._configFileName,self._config)
        self._isDefault = False
        return True

    @staticmethod
    def __SyncGet(m1,m2,key):
        '''获取m1[key]，若该值存在，则将值覆盖到m2[key]；
        若该值不存在，则使用m2[key]的值。
        '''
        val = m1.get(key)
        if None != val:
            m2[key] = val
        else:
            val = m2.get(key)
        return val

    @staticmethod
    def __VersionGrew(verList,grew,idx):
        if idx >= len(verList) or idx < 0:
            return verList

        verList[idx] += grew
        val = verList[idx]
        if val > 100 and idx != 0:
            verList[idx] = val % 100
            verList = Assistant.__VersionGrew(verList,val // 100,idx - 1)
        return verList


    @staticmethod
    def __VersionStrGrew(ver,grew = 0):
        '''形如"1.2.3.4"格式的版本号，按照grew参数增长，在100时进位。
        '''
        verNList = [0,0,0,0]
        verList = ver.split(".")
        try:
            for i in range(0,min(len(verNList),len(verList))):
                verNList[i] = int(verList[i])
        except:
            verNList = [0,0,0,0]
        verNList = Assistant.__VersionGrew(verNList,grew,idx = 3)

        for i in range(0,min(len(verNList),len(verList))):
            verList[i] = str(verNList[i])
        return ".".join(verList)

    @staticmethod
    def __GetProjectManifest(pManifestPath,template):
        '''获取指定路径的projectManifest文件内容。
        若不存在，将以Template.ProjectManifestTemplate创建一个新的，并以template参数初始化。
        '''

        if os.path.isfile(pManifestPath):
            return Functions.LoadJson(pManifestPath)

        pManifest = ProjectManifestTemplate.copy()
        for k in pManifest.keys():
            if k in template.keys():
                pManifest[k] = template[k]
        Functions.SaveJson(pManifestPath,pManifest,0)
        return pManifest

    def __GetModule(self,moduleName):
        '''由模块名获得模块，moduleName == None时，将获取所有模块。

        Param:

            moduleName      模块名。

        Return:

            dict
        '''
        if moduleName != None:
            return {moduleName,self._config["modules"][moduleName]}
        return self._config["modules"]


    def __SyncModuleToTemp(self,moduleName = None):
        '''同步给定的模块名的文件到_tempDir/module/moduleName中。
        若不提供模块名，将同步全部模块。

        Param:

            moduleName          模块名。
        '''
        mds = self._config["modules"] if moduleName == None else [self._config["modules"].get(moduleName)]
        if mds == None:
            return False
        for name,m in mds.items():
            for d in m["dirs"]:
                if not Functions.SyncDir(d,os.path.join(Assistant._TempDir,name,d),[Assistant._ModuleFileName]):
                    return False
            for f in m["files"]:
                dstFileDir = os.path.dirname(os.path.join(Assistant._TempDir,name,f))
                if not os.path.exists(dstFileDir):
                    os.makedirs(dstFileDir)
                shutil.copy(f,os.path.join(Assistant._TempDir,name,f))
        return True

    def __CompileLua(self,moduleName = None,uniConfig = None,sync = False,**kw):
        '''编译给定的模块名的lua文件到_tempDir/name中。
        若不提供模块名，将编译全部模块。

        Param:

            moduleName          模块名。
            uniConfig           是否使用统一配置。
            sync                操作前是否先同步文件夹。
            compileLua          编译lua的功能是否开启。
        '''
        if sync:
            self.__SyncModuleToTemp(moduleName)
        if None == uniConfig:
            uniConfig = self._config.get("useUniConfig")
        for name,module in self.__GetModule(moduleName).items():
            opDir = os.path.join(Assistant._TempDir,name)
            mConfig = module if not uniConfig else self._config["uniModule"]
            compileLua = Assistant.__SyncGet(kw,mConfig,"compileLua")
            if compileLua and not Functions.CompileLua(opDir):
                return False
        return True

    def __CompressPng(self,moduleName = None,uniConfig = None,sync = False,**kw):
        '''压缩给定的模块名的png文件到_tempDir/name中。
        若不提供模块名，将压缩全部模块。

        Param:

            moduleName          模块名。
            uniConfig           是否使用统一配置。
            sync                操作前是否先同步文件夹。
            compressPic         压缩png的功能是否开启。
            compressQualityMin  最低质量。
            compressQualityMax  最高接近质量。
        '''
        if sync:
            self.__SyncModuleToTemp(moduleName)
        if None == uniConfig:
            uniConfig = self._config.get("useUniConfig")
        for name,module in self.__GetModule(moduleName).items():
            opDir = os.path.join(Assistant._TempDir,name)
            mConfig = module if not uniConfig else self._config["uniModule"]
            compressQualityMin = Assistant.__SyncGet(kw,mConfig,"compressQualityMin")
            compressQualityMax = Assistant.__SyncGet(kw,mConfig,"compressQualityMax")
            compressPic = Assistant.__SyncGet(kw,mConfig,"compressPic")
            if compressPic and not Functions.CompressPng(opDir,qMin = compressQualityMin,qMax = compressQualityMax):
                return False
        return True

    def __EncryptRes(self,moduleName = None,uniConfig = None,sync = False,**kw):
        '''加密给定的模块名的png/lua/luac文件到_tempDir/name中。
        若不提供模块名，将加密全部模块。

        Param:

            moduleName          模块名。
            uniConfig           是否使用统一配置。
            sync                操作前是否先同步文件夹。
            encryptRes          加密功能是否开启。
            encryptPassword     加密密码。
        '''
        # 当使用默认配置时，不进行任何加密（由于默认配置未指定有效密码，且对用户不可见），直接返回。
        if self._isDefault:
            return True
        if sync:
            self.__SyncModuleToTemp(moduleName)
        if None == uniConfig:
            uniConfig = self._config.get("useUniConfig")
        for name,module in self.__GetModule(moduleName).items():
            opDir = os.path.join(Assistant._TempDir,name)
            mConfig = module if not uniConfig else self._config["uniModule"]
            encryptPassword = Assistant.__SyncGet(kw,mConfig,"encryptPassword")
            encryptRes = Assistant.__SyncGet(kw,mConfig,"encryptRes")

            if encryptRes and not Functions.EncryptRes(opDir,encryptPassword):
                return False
        return True

    def __HashModule(self,moduleName,uniConfig = None,sync = False,**kw):
        '''生成并返回给定的模块名的哈希描述。

        Param:

            moduleName          模块名。
            uniConfig           是否使用统一配置。
            sync                操作前是否先同步文件夹。
            zipUncompress       是否将zip文件标识为需要解压。
        '''

        # 当使用默认配置时，哈希描述无生成意义（默认配置不进行任何热更操作，不需要比对哈希），直接返回。
        if self._isDefault or None == moduleName:
            return {}
        if sync:
            self.__SyncModuleToTemp(moduleName)
        if None == uniConfig:
                uniConfig = self._config.get("useUniConfig")
        for name,module in self.__GetModule(moduleName).items():
            opDir = os.path.join(Assistant._TempDir,name)
            mConfig = module if not uniConfig else self._config["uniModule"]

            zipUncompress = Assistant.__SyncGet(kw,mConfig,"zipUncompress")
            return Functions.CalcDirHash(opDir,compressed = zipUncompress)
        return {}

    def __Upload(
        self,
        moduleName = None,
        uniConfig = False,
        **kw
    ):
        '''见Upload
        '''
        # 当使用默认配置时，不进行上传（默认配置不进行任何热更操作，不需要上传），直接返回。
        if self._isDefault:
            return True
        if None == uniConfig:
            uniConfig = self._config.get("useUniConfig")
        for name,module in self.__GetModule(moduleName).items():
            opDir = os.path.join(Assistant._TempDir,name)
            mConfig = module if not uniConfig else self._config["uniModule"]

            versionType = kw.get("versionType")
            if None != versionType:
                if isinstance(versionType,str):
                    mConfig["versionType"] = 3
                    mConfig["useVersion"] = versionType
                else:
                    mConfig["versionType"] = versionType
            else:
                if mConfig["versionType"] == 3:
                    versionType = mConfig["useVersion"]
                else:
                    versionType = mConfig["versionType"]

            noUpload = Assistant.__SyncGet(kw,mConfig,"noUpload")
            onlyHashDiff = Assistant.__SyncGet(kw,mConfig,"onlyHashDiff")
            compressUpload = Assistant.__SyncGet(kw,mConfig,"compressUpload")
            ftpAccount = Assistant.__SyncGet(kw,mConfig,"ftpAccount")
            ftpPassword = Assistant.__SyncGet(kw,mConfig,"ftpPassword")
            Assistant.__SyncGet(kw,mConfig,"filterType")
            Assistant.__SyncGet(kw,mConfig,"openFilterNum")
            Assistant.__SyncGet(kw,mConfig,"filterNum")
            Assistant.__SyncGet(kw,mConfig,"openFilterSize")
            Assistant.__SyncGet(kw,mConfig,"filterSize")

            pManifestPath = os.path.join(Assistant._VersionDir,name,Assistant._ProjectManifest)
            mpManifestPath = os.path.join(Assistant._TempDir,name,Assistant._ProjectManifest)
            mvManifestPath = os.path.join(Assistant._TempDir,name,Assistant._VersionManifest)
            moduleZip = os.path.join(Assistant._TempDir,name,name + ".zip")

            pManifest = Assistant.__GetProjectManifest(pManifestPath,module)

            # 先删除version.manifest.json/project.manifest.json/name.zip
            if os.path.isfile(mvManifestPath):
                os.remove(mvManifestPath)
            if os.path.isfile(mpManifestPath):
                os.remove(mpManifestPath)
            if os.path.isfile(moduleZip):
                os.remove(moduleZip)
            # 生成文件哈希描述。
            pManifest["assets"] = self.__HashModule(name,uniConfig,False,**kw)

            if versionType == 0:
                # 远程版本+1操作。
                remoteVM = Functions.LoadNetJson(module["remoteVersionUrl"])
                if remoteVM:
                    pManifest["version"] = Assistant.__VersionStrGrew(remoteVM["version"],1)
                else:
                    print("获取远程版本失败！")
                    return False
            elif versionType == 1:
                # 本地版本+1操作。
                pManifest["version"] = Assistant.__VersionStrGrew(pManifest["version"],1)
            elif isinstance(versionType,str):
                # 指定版本。
                pManifest["version"] = Assistant.__VersionStrGrew(versionType)

            # ProjectManifest写回文件。
            Functions.SaveJson(pManifestPath,pManifest,0)
            Functions.SaveJson(mpManifestPath,pManifest,0)
            # VersionManifest写入。
            vManifest = VersionManifestTemplate.copy()
            vManifest["version"] = pManifest["version"]
            vManifest["remoteManifestUrl"] = pManifest["remoteManifestUrl"]
            vManifest["remoteVersionUrl"] = pManifest["remoteVersionUrl"]
            Functions.SaveJson(mvManifestPath,vManifest,0)

            if not noUpload:
                # 待上传文件。
                uploadFiles = pManifest["assets"]
                if onlyHashDiff:
                    # 比对不同哈希文件。
                    rpManifest = Functions.LoadNetJson(module["remoteManifestUrl"])
                    if None == rpManifest:
                        print("获取远程文件列表失败！")
                        return False
                    remoteFiles = rpManifest.get("assets",{})
                    uploadFiles = [
                        k\
                        for k,v in uploadFiles.items()\
                        if k not in remoteFiles.keys() or (remoteFiles[k].get("md5","").lower() != v.get("md5","").lower())
                    ]
                else:
                    uploadFiles = [k for k in uploadFiles.keys()]

                oCWD = os.getcwd()
                os.chdir(opDir)
                if compressUpload:
                    # 需要压缩再上传。
                    ret = Functions.ZipFiles(name + ".zip",uploadFiles)
                    if not ret:
                        return False
                    uploadFiles = [name + ".zip"]

                # 追加version.manifest.json和project.manifest.json
                uploadFiles.append(Assistant._VersionManifest)
                uploadFiles.append(Assistant._ProjectManifest)
                # ftp上传
                ret = Functions.FtpUpload(module["uploadUrl"],ftpAccount,ftpPassword,uploadFiles)
                os.chdir(oCWD)
                if not ret:
                    print("文件上传失败！")
                    return False

        return True

    def Upload(
        self,
        moduleName = None,
        uniConfig = None,
        **kw
    ):
        '''在本地完成部署后上传。
        若不提供模块名，将部署和上传全部模块。
        project.manifest.json文件将生成于模块根目录的Version下；
        version.manifest.json文件将生成于_tempDir的模块目录下。
        如果不提供参数，则参数将使用模块文件中的默认值。

        Param:

            moduleName          模块名。

            uniConfig           是否使用统一配置。

            versionType         版本配置类型，可以为整数或字符串。
                                整数0表示使用远程版本号+1；
                                整数1表示使用本地版本号+1；
                                整数2表示版本不变；
                                字符串表示为："1.2.3.4"的格式。

            zipUncompress       表示zip资源在project.manifest.json文件中是否标识为自动解压。

            encryptRes          表示是否加密资源.
                                若为True，则encryptPassword指示了加密密码；
                                若为False，则encryptPassword不生效。

            encryptPassword     加密密码。

            compressPic         表示是否压缩png图像。
                                若为True，qMin和qMax参数指示了压缩质量；
                                若为False，qMin和qMax不生效。

            compressQualityMin  压缩图像的最低质量。

            compressQualityMax  压缩图像的最高接近质量。

            compileLua          表示是否对lua编译。

            noUpload            表示是否不上传。
                                若为True，将不会有上传步骤，但仍然会进行本地部署，这对于应用编译和本地调试很有用；
                                若为True，uploadHashDiff和compressUpload将被强制认为是False。
                                若为False，将在本地部署后，将部署完成的文件上传。

            onlyHashDiff        表示是否仅上传哈希不同的文件。
                                当且仅当uploadHashDiff为False（或默认配置中为False），compressUpload为True（或默认配置中为True）时，
                                文件下载筛选才会生效。

            compressUpload      表示是否压缩文件后再上传（需要接收端解压）。
                                当且仅当uploadHashDiff为False（或默认配置中为False），compressUpload为True（或默认配置中为True）时，
                                文件下载筛选才会生效。

            ftpAccount          ftp账号。

            ftpPassword         ftp密码。

            filterType          整数，整包下载筛选类型。
                                若为0，使用||逻辑；
                                若为1，使用&&逻辑。

            openFilterNum       是否开启文件数量筛选。

            filterNum           整数，文件筛选总数量。

            openFilterSize      是否开启文件容量筛选。

            filterSize          整数，文件筛选总容量（字节）。

        Return:

            bool                有任意一个步骤失败，均会中断剩余步骤，返回False；
                                否则返回True。
        '''

        # 依次进行文件同步/编译lua/压缩图像/加密资源/生成描述文件和上传的步骤。
        ret = self.__SyncModuleToTemp(moduleName) and\
        self.__CompileLua(moduleName,uniConfig,False,**kw) and\
        self.__CompressPng(moduleName,uniConfig,False,**kw) and\
        self.__EncryptRes(moduleName,uniConfig,False,**kw) and\
        self.__Upload(moduleName,uniConfig,**kw)
        if not ret:
            print("操作失败！")
        else:
            print("操作成功。")
        return ret

    def Sync(self,syncDir,moduleName = None):
        """仅同步文件。
        
        参数：
            syncDir             同步的目录。
            moduleName          模块名。不提供该参数时，同步所以模块。

        返回：

            boolean             表示是否成功同步。
        """

        mds = self._config["modules"] if moduleName == None else [self._config["modules"].get(moduleName)]
        if mds == None:
            return False
        for m in mds.values():
            for d in m["dirs"]:
                if not Functions.SyncDir(d,os.path.join(syncDir,d),[Assistant._ModuleFileName]):
                    return False
            for f in m["files"]:
                dstFileDir = os.path.dirname(os.path.join(syncDir,f))
                if not os.path.exists(dstFileDir):
                    os.makedirs(dstFileDir)
                shutil.copy(f,os.path.join(syncDir,f))
        return True

    def Deploy(self,
        deployDir,
        uniConfig = None,
        **kw
    ):
        '''仅在本地部署，不上传。
        将会部署全部模块。
        project.manifest.json文件将生成于模块根目录的Version下；
        如果不提供参数，则参数将使用模块文件中的默认值。

        Param:

            deployDir           部署文件夹。

            uniConfig           是否使用统一配置。

            versionType         版本配置类型，可以为整数或字符串。
                                整数0表示使用远程版本号+1；
                                整数1表示使用本地版本号+1；
                                整数2表示版本不变；
                                字符串表示为："1.2.3.4"的格式。

            zipUncompress       表示zip资源在project.manifest.json文件中是否标识为自动解压。

            encryptPassword     加密密码。

            compressQualityMin  压缩图像的最低质量。

            compressQualityMax  压缩图像的最高接近质量。

        Return:

            bool                有任意一个步骤失败，均会中断剩余步骤，返回False；
                                否则返回True。
        '''
        # 依次进行文件同步/编译lua/压缩图像/加密资源/生成描述文件的步骤。
        ret = self.__SyncModuleToTemp() and\
        self.__CompileLua(None,uniConfig,False,compileLua = True,**kw) and\
        self.__CompressPng(None,uniConfig,False,compressPic = True,**kw) and\
        self.__EncryptRes(None,uniConfig,False,encryptRes = True,**kw) and\
        self.__Upload(None,uniConfig,noUpload = True,**kw)# 此处并不真正上传，仅依靠该函数生成哈希描述。

        if not os.path.exists(os.path.join(deployDir,Assistant._VersionDir)) and not self._isDefault:
            os.makedirs(os.path.join(deployDir,Assistant._VersionDir))
        if ret:
            for name,m in self._config["modules"].items():
                for d in m["dirs"]:
                    if not Functions.SyncDir(os.path.join(Assistant._TempDir,name,d),os.path.join(deployDir,d),[Assistant._ModuleFileName]):
                        ret = False
                        break
                for f in m["files"]:
                    dstFileDir = os.path.dirname(os.path.join(deployDir,f))
                    if not os.path.exists(dstFileDir):
                        os.makedirs(dstFileDir)
                    shutil.copy(os.path.join(Assistant._TempDir,name,f),os.path.join(deployDir,f))
                
                if self._isDefault:
                    # 使用默认配置时，不生成版本信息（默认配置对用户不可见）。
                    continue
                vPath = os.path.join(Assistant._TempDir,name,Assistant._VersionManifest)
                pPath = os.path.join(Assistant._TempDir,name,Assistant._ProjectManifest)
                dvPath = os.path.join(deployDir,Assistant._VersionDir,name,Assistant._VersionManifest)
                dpPath = os.path.join(deployDir,Assistant._VersionDir,name,Assistant._ProjectManifest)
                dvPath = os.path.dirname(dvPath)
                dpPath = os.path.dirname(dpPath)
                if not os.path.exists(dvPath):
                    os.makedirs(dvPath)
                if not os.path.exists(dpPath):
                    os.makedirs(dpPath)

                if os.path.isfile(vPath):
                    shutil.copy(vPath,dvPath)
                if os.path.isfile(pPath):
                    shutil.copy(pPath,dpPath)
        if not ret:
            print("操作失败！")
        else:
            print("操作成功。")
        return ret