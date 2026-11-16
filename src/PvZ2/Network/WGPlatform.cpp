//
//  WGPlatform.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "WGPlatform.h"
#include "WGPlatformObserver.h"

WGPlatform::~WGPlatform()
{
}

WGPlatform WGPlatform::m_Instance;

WGPlatform *WGPlatform::GetInstance()
{
    return &m_Instance;
}

void WGPlatform::init(JavaVM *pVM, WGPlatformObserver *pNotify)
{
    m_pVM = pVM;
    needDelayWakeupNotify = false;
    needDelayLoginNotify = false;
}

void WGPlatform::setVM(JavaVM *pVM)
{
    m_pVM = pVM;
}

WGPlatformObserver *WGPlatform::GetObserver() const
{
    return m_pNotify;
}

WakeupRet &WGPlatform::getWakeup()
{
    return m_lastWakeup;
}

LoginRet &WGPlatform::getLoginRet()
{
    return m_lastLoginRet;
}

void WGPlatform::setLoginRet(LoginRet &lr)
{
    m_lastLoginRet = lr;
    needDelayLoginNotify = true;
    __android_log_print(ANDROID_LOG_INFO, "WeGame  ~!!@", "WGPlatform::setLoginRet %d", 1);
}

void WGPlatform::setWakeup(WakeupRet &wakeup)
{
    m_lastWakeup = wakeup;
    needDelayWakeupNotify = true;
    __android_log_print(ANDROID_LOG_INFO, "WeGame  ~!!@", "WGPlatform::setWakeup %d", 1);
}

void WGPlatform::WGLogin(int platform)
{
    __android_log_print(ANDROID_LOG_INFO, "WeGame  ~!!@", "WGPlatform::WGLogin platform:%d", platform);
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGLogin", "(I)V");
    env->CallStaticVoidMethod(cls, mid, platform);
}

bool WGPlatform::WGLogout(bool clean)
{
    __android_log_print(ANDROID_LOG_INFO, "WeGame  ~!!@", "WGPlatform::WGLogout", "");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGLogout", "(Z)Z");
    jboolean ret = env->CallStaticBooleanMethod(cls, mid, clean);
    return ret != 0;
}

void WGPlatform::WGSetPermission(unsigned int permissions)
{
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGSetQzonePermisson", "(I)V");
    env->CallStaticVoidMethod(cls, mid, permissions);
}

void WGPlatform::WGChangeEnv(int env_)
{
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGChangeEnvironment", "(I)V");
    env->CallStaticVoidMethod(cls, mid, env_);
}

void WGPlatform::WGRefreshWXToken()
{
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGRefreshWXToken", "()V");
    env->CallStaticVoidMethod(cls, mid);
}

void WGPlatform::WGEnableCrashReport(bool isRdmEnable, bool isMtaEnable)
{
    __android_log_print(ANDROID_LOG_INFO, "WeGame  ~!!@", "WGPlatform::WGEnableCrashReport bEnable rdm: %d; mta: %d;", isRdmEnable, isMtaEnable);
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGEnableCrashReport", "(ZZ)V");
    env->CallStaticVoidMethod(cls, mid, isRdmEnable, isMtaEnable);
}

bool WGPlatform::WGIsPlatformInstalled(int platform)
{
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGIsPlatformInstalled", "(I)Z");
    jboolean ret = env->CallStaticBooleanMethod(cls, mid, platform);
    return ret != 0;
}

bool WGPlatform::WGIsPlatformSupportApi(int platform)
{
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGIsPlatformSupportApi", "(I)Z");
    jboolean ret = env->CallStaticBooleanMethod(cls, mid, platform);
    return ret != 0;
}

static jstring charsToJString(JNIEnv *env, const char *pat, int len)
{
    jclass strClass = env->FindClass("java/lang/String");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(len);
    env->SetByteArrayRegion(bytes, 0, len, (const jbyte *)pat);
    jstring encoding = env->NewStringUTF("utf-8");
    return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}

static std::string jstringToString(JNIEnv *env, jstring jstr)
{
    jclass clsstring = env->FindClass("java/lang/String");
    jmethodID mlen = env->GetMethodID(clsstring, "length", "()I");
    if (jstr == NULL || env->CallIntMethod(jstr, mlen) < 1)
    {
        std::string empty("");
        return empty;
    }
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, NULL);
    char *rtn = (char *)malloc(alen + 1);
    memcpy(rtn, ba, alen);
    rtn[alen] = 0;
    env->ReleaseByteArrayElements(barr, ba, 0);
    std::string stemp(rtn);
    free(rtn);
    return stemp;
}

const std::string WGPlatform::WGGetPf()
{
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGGetPf", "()Ljava/lang/String;");
    jstring ret = (jstring)env->CallStaticObjectMethod(cls, mid);
    return jstringToString(env, ret);
}

const std::string WGPlatform::WGGetPfKey()
{
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGGetPfKey", "()Ljava/lang/String;");
    jstring ret = (jstring)env->CallStaticObjectMethod(cls, mid);
    return jstringToString(env, ret);
}

const std::string WGPlatform::WGGetVersion()
{
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGGetVersion", "()Ljava/lang/String;");
    jstring ret = (jstring)env->CallStaticObjectMethod(cls, mid);
    return jstringToString(env, ret);
}

const std::string WGPlatform::WGGetChannelId()
{
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGGetChannelId", "()Ljava/lang/String;");
    jstring ret = (jstring)env->CallStaticObjectMethod(cls, mid);
    return jstringToString(env, ret);
}

const std::string WGPlatform::WGGetRegisterChannelId()
{
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGGetRegisterChannelId", "()Ljava/lang/String;");
    jstring ret = (jstring)env->CallStaticObjectMethod(cls, mid);
    return jstringToString(env, ret);
}

void WGPlatform::WGSetObserver(WGPlatformObserver *pNotify)
{
    LOGD("WGPlatform::WGSetObserver needDelayWakeupNotify %d", needDelayWakeupNotify);
    LOGD("WGPlatform::WGSetObserver needDelayLoginNotify %d", needDelayLoginNotify);
    m_pNotify = pNotify;
    if (needDelayWakeupNotify)
    {
        LOGD("WGPlatform::WGSetObserver wakeup delay notify openid:%s", m_lastWakeup.open_id.c_str());
        m_pNotify->OnWakeupNotify(m_lastWakeup);
        needDelayWakeupNotify = false;
    }
    else if (needDelayLoginNotify)
    {
        for (size_t i = 0; i < m_lastLoginRet.token.size(); i++)
        {
            LOGD("WGPlatform::WGSetObserver login delay notify type:%d; value:%s", m_lastLoginRet.token.at(i).type, m_lastLoginRet.token.at(i).value.c_str());
        }
        m_pNotify->OnLoginNotify(m_lastLoginRet);
        needDelayLoginNotify = false;
    }
}

int WGPlatform::WGFeedback(unsigned char *game, unsigned char *txt)
{
    LOGD("WGPlatform::WGFeedBack txt:%s", txt);
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGFeedback", "(Ljava/lang/String;Ljava/lang/String;)Z");
    return env->CallStaticBooleanMethod(cls, mid, charsToJString(env, (const char *)game, strlen((const char *)game)), charsToJString(env, (const char *)txt, strlen((const char *)txt)));
}

void WGPlatform::WGReportEvent(unsigned char *name, unsigned char *body, bool isRealTime)
{
    LOGD("WGPlatform::WGEnableReport bEnable", "");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGReportEvent", "(Ljava/lang/String;Ljava/lang/String;Z)V");
    env->CallStaticVoidMethod(cls, mid, charsToJString(env, (const char *)name, strlen((const char *)name)), charsToJString(env, (const char *)body, strlen((const char *)body)), isRealTime);
}

void WGPlatform::WGSendToQQ(unsigned char *title, unsigned char *desc, unsigned char *url, unsigned char *imgUrl, const int &imgUrlLen)
{
    LOGD("WGPlatform::WGSendToQQ title:%s", title);
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGSendToQQ", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V");
    jstring a = charsToJString(env, (const char *)title, strlen((const char *)title));
    jstring b = charsToJString(env, (const char *)desc, strlen((const char *)desc));
    jstring c = charsToJString(env, (const char *)url, strlen((const char *)url));
    jstring d = charsToJString(env, (const char *)imgUrl, imgUrlLen);
    env->CallStaticVoidMethod(cls, mid, a, b, c, d, imgUrlLen);
}

void WGPlatform::WGSendToWeixin(const int &scene, unsigned char *title, unsigned char *desc, unsigned char *url, unsigned char *mediaTagName, unsigned char *thumbImgData, const int &thumbImgDataLen)
{
    LOGD("WGPlatform::WGSendToWeixin title:%s", title);
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGSendToWeixin", "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[BI)V");
    jstring jtitle = charsToJString(env, (const char *)title, strlen((const char *)title));
    jstring jdesc = charsToJString(env, (const char *)desc, strlen((const char *)desc));
    jstring jurl = charsToJString(env, (const char *)url, strlen((const char *)url));
    jbyteArray arr = env->NewByteArray(thumbImgDataLen);
    jstring jtag = charsToJString(env, (const char *)mediaTagName, strlen((const char *)mediaTagName));
    env->SetByteArrayRegion(arr, 0, thumbImgDataLen, (const jbyte *)thumbImgData);
    env->CallStaticVoidMethod(cls, mid, scene, jtitle, jdesc, jurl, jtag, arr, thumbImgDataLen);
    env->DeleteLocalRef(arr);
}

void WGPlatform::WGSendToWeixinWithPhoto(const int &scene, unsigned char *mediaTagName, unsigned char *imgData, const int &imgDataLen)
{
    LOGD("WGPlatform::WGSendToWeixinWithPhoto imgDataLen=%d", imgDataLen);
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGSendToWeixinWithPhoto", "(ILjava/lang/String;[BI)V");
    jbyteArray arr = env->NewByteArray(imgDataLen);
    env->SetByteArrayRegion(arr, 0, imgDataLen, (const jbyte *)imgData);
    jstring jtag = charsToJString(env, (const char *)mediaTagName, strlen((const char *)mediaTagName));
    env->CallStaticVoidMethod(cls, mid, scene, jtag, arr, imgDataLen);
    env->DeleteLocalRef(arr);
}

void WGPlatform::WGTestSpeed(std::vector<std::string> &addrList)
{
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass listCls = env->FindClass("java/util/ArrayList");
    jmethodID listInit = env->GetMethodID(listCls, "<init>", "()V");
    jmethodID listSize = env->GetMethodID(listCls, "size", "()I");
    jmethodID listAdd = env->GetMethodID(listCls, "add", "(Ljava/lang/Object;)Z");
    jobject list = env->NewObject(listCls, listInit);
    size_t i = 0;
    while (i++ < addrList.size())
    {
        JNIEnv *e = env;
        std::string &addr = addrList.at(i - 1);
        e->CallBooleanMethod(list, listAdd, charsToJString(e, addr.c_str(), addr.length()));
    }
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGTestSpeed", "(Ljava/util/ArrayList;)V");
    env->CallStaticVoidMethod(cls, mid, list);
}

const int WGPlatform::WGGetBestSchedulingIp(SchedulingInfo &ipPort, std::vector<std::string> &denyIpList)
{
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGGetBestSchedulingIp", "(Lcom/tencent/msdk/schedule/SchedulingInfo;Ljava/util/List;)I");
    jclass infoCls = env->FindClass("com/tencent/msdk/schedule/SchedulingInfo");
    jmethodID infoInit = env->GetMethodID(infoCls, "<init>", "()V");
    jobject info = env->NewObject(infoCls, infoInit);
    jfieldID ipField = env->GetFieldID(infoCls, "ip", "Ljava/lang/String;");
    jfieldID portField = env->GetFieldID(infoCls, "port", "I");
    jclass listCls = env->FindClass("java/util/ArrayList");
    jmethodID listInit = env->GetMethodID(listCls, "<init>", "()V");
    jmethodID listAdd = env->GetMethodID(listCls, "add", "(Ljava/lang/Object;)Z");
    jmethodID listGet = env->GetMethodID(listCls, "get", "(I)Ljava/lang/Object;");
    jobject list = env->NewObject(listCls, listInit);
    size_t i = 0;
    while (i++ < denyIpList.size())
    {
        JNIEnv *e = env;
        std::string &addr = denyIpList.at(i - 1);
        e->CallBooleanMethod(list, listAdd, charsToJString(e, addr.c_str(), addr.length()));
    }
    jint ret = env->CallStaticIntMethod(cls, mid, info, list);
    jstring jip = (jstring)env->GetObjectField(info, ipField);
    ipPort.ip = jstringToString(env, jip);
    ipPort.port = env->GetIntField(info, portField);
    LOGD("WGGetBestSchedulingIp  ip:%s; port: %d", ipPort.ip.c_str(), ipPort.port);
    return ret;
}

int WGPlatform::WGGetLoginRecord(LoginRet &lr)
{
    LOGD("WGPlatform::WGGetLoginRecord", "");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = env->FindClass("com/tencent/msdk/api/WGPlatform");
    jmethodID mid = env->GetStaticMethodID(cls, "WGGetLoginRecord", "(Lcom/tencent/msdk/api/LoginRet;)I");
    jclass retCls = env->FindClass("com/tencent/msdk/api/LoginRet");
    jmethodID retInit = env->GetMethodID(retCls, "<init>", "()V");
    jobject ret = env->NewObject(retCls, retInit);
    env->CallStaticIntMethod(cls, mid, ret);

    jfieldID pfField = env->GetFieldID(retCls, "pf", "Ljava/lang/String;");
    jstring jpf = (jstring)env->GetObjectField(ret, pfField);
    std::string pf = jstringToString(env, jpf);
    LOGD("WGPlatform:: pf = %s", pf.c_str());
    lr.pf = pf;

    jfieldID pfKeyField = env->GetFieldID(retCls, "pf_key", "Ljava/lang/String;");
    jstring jpfKey = (jstring)env->GetObjectField(ret, pfKeyField);
    std::string pfKey = jstringToString(env, jpfKey);
    LOGD("WGPlatform:: pfKey =  %s", pfKey.c_str());
    lr.pf_key = pfKey;

    lr.flag = 1;

    jfieldID descField = env->GetFieldID(retCls, "desc", "Ljava/lang/String;");
    jstring jdesc = (jstring)env->GetObjectField(ret, descField);
    std::string desc = jstringToString(env, jdesc);
    lr.desc = desc;

    jfieldID platformField = env->GetFieldID(retCls, "platform", "I");
    lr.platform = env->GetIntField(ret, platformField);
    LOGD("WGPlatform::WGGetLoginRecord platform %d", lr.platform);
    LOGD("WGPlatform::WGGetLoginRecord _ePlatform(plat) %d", lr.platform);

    jfieldID openIdField = env->GetFieldID(retCls, "open_id", "Ljava/lang/String;");
    jstring jopenId = (jstring)env->GetObjectField(ret, openIdField);
    std::string openId = jstringToString(env, jopenId);
    lr.open_id = openId;
    LOGD("WGPlatform::WGGetLoginRecord open_id %s", openId.c_str());

    jfieldID tokenField = env->GetFieldID(retCls, "token", "Ljava/util/Vector;");
    jobject vec = env->GetObjectField(ret, tokenField);
    jclass vecCls = env->GetObjectClass(vec);
    jmethodID vecSize = env->GetMethodID(vecCls, "size", "()I");
    jmethodID vecGet = env->GetMethodID(vecCls, "get", "(I)Ljava/lang/Object;");
    int size = env->CallIntMethod(vec, vecSize);
    LOGD("WGPlatform::WGGetLoginRecord Vector size %d", size);
    for (int i = 0; i < size; i++)
    {
        TokenRet token;
        jobject jtoken = env->CallObjectMethod(vec, vecGet, i);
        jclass tokenCls = env->GetObjectClass(jtoken);
        jfieldID typeField = env->GetFieldID(tokenCls, "type", "I");
        token.type = env->GetIntField(jtoken, typeField);
        jfieldID valueField = env->GetFieldID(tokenCls, "value", "Ljava/lang/String;");
        jstring jvalue = (jstring)env->GetObjectField(jtoken, valueField);
        token.value = jstringToString(env, jvalue);
        jfieldID expField = env->GetFieldID(tokenCls, "expiration", "I");
        token.expiration = env->GetIntField(jtoken, expField);
        lr.token.push_back(token);
    }

    jfieldID userIdField = env->GetFieldID(retCls, "user_id", "Ljava/lang/String;");
    jstring juserId = (jstring)env->GetObjectField(ret, userIdField);
    std::string userId = jstringToString(env, juserId);
    lr.user_id = userId;
    env->DeleteLocalRef(ret);
    return lr.platform;
}
