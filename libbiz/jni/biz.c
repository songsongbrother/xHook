#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <jni.h>
#include <android/log.h>
#include <string.h>
#include "xhook.h"
#include <sys/system_properties.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

//void getfilestr(FILE *fp);

//static int my_system_log_print(int prio, const char* tag, const char* fmt, ...)
//{
//    va_list ap;
//    char buf[1024];
//    int r;
//
//    snprintf(buf, sizeof(buf), "[%s] %s", (NULL == tag ? "" : tag), (NULL == fmt ? "" : fmt));
//
//    va_start(ap, fmt);
//    r = __android_log_vprint(prio, "xhook_system", buf, ap);
//    va_end(ap);
//    return r;
//}

//static int my_libtest_log_print(int prio, const char* tag, const char* fmt, ...)
//{
//    va_list ap;
//    char buf[1024];
//    int r;
//
//    snprintf(buf, sizeof(buf), "[%s] %s", (NULL == tag ? "" : tag), (NULL == fmt ? "" : fmt));
//
//    va_start(ap, fmt);
//    r = __android_log_vprint(prio, "xhook_libtest", buf, ap);
//    va_end(ap);
//    return r;
//}

//static FILE *my_fopen(const char* filename, const char* modes)
//{
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "fopen==%s", filename);
//    return fopen(filename,modes);
//}
//
//static FILE *my_popen(const char* filename, const char* modes)
//{
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "popen==%s", filename);
//    return fopen(filename,modes);
//}

//static int my_open(const char* file, int oflag,...)
//{
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "open==%s %d", file,oflag);
//        int r;
//    r = open(file,O_RDWR);
//    return r;
//}
//
//static ssize_t my_read(int fd,void *buf,size_t nbytes){
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "read==%d",fd);
//    return read(fd,buf,nbytes);
//}
//
//static int my_creat(const char *file,__mode_t mode){
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "creat==%s", file);
//    return creat(file,mode);
//}


//static char *my_strstr(const char* haystack, const char* needle)
//{
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "strstr==%s  %s", haystack,needle);
//    char *ret;
//    ret = strstr(haystack,needle);
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "strstr==ret===%s", ret);
//    return ret;
//}

//static char *my_strcpy(char* dest, const char* src)
//{
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "strcpy==%s  %s", dest,src);
////    if (strcmp(src,"267000:3F45E0:EDC3C4")==0) {
//        // 修改值
////        src = "feq#%dc87#988(^)78909-=89+1vfiqocxq58*@#~09$";
////        strcpy(src,"feq#%dc87#988(^)78909-=89+1vfiqocxq58*@#~09$");
////        return strcpy(dest,"267000:3F45E0:EDC3C4");
////    }
//    char *ret;
//    ret = strcpy(dest,src);
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "strcpy==ret===%s", ret);
//    return ret;
//}

//static int my_strcmp(const char* s1, const char* s2)
//{
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "strcmp==%s  %s", s1,s2);
//    return strcmp(s1,s2);
//}

//static int my_get_sys(const char* name, char* value)
//{
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "get_sys==%s  %s", name,value);
//    return __system_property_get(name,value);
//}


//static int my_sscanf(const char* s, const char* fmt, ...)
//{
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "sscanf==%s  %s", s,fmt);
//    va_list ap;
////    char buf[1024];
//    int r;
//
////    snprintf(buf, sizeof(buf), "[%s] %s", (NULL == s ? "" : s), (NULL == fmt ? "" : fmt));
//
//    va_start(ap, fmt);
//    r = vsscanf(s, fmt, ap);
//    va_end(ap);
//    return r;
//}

//static int my_sprintf(char* s, const char* fmt, ...)
//{
//
//    va_list ap;
////    char buf[1024];
//    int r;
//
////    snprintf(buf, sizeof(buf), "[%s] %s", (NULL == s ? "" : s), (NULL == fmt ? "" : fmt));
//
//    va_start(ap, fmt);
//    r = vsprintf(s, fmt, ap);
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "sprintf==%s  %s", s,fmt);
//    va_end(ap);
//    return r;
//}

//static size_t my_fread(void *ptr,size_t size,size_t n,FILE *stream){
////    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "fread==%zu  %zu", size,n);
//    getfilestr(stream);
//    return fread(ptr,size,n,stream);
//}

//void *my_memcpy(void *a,const void *b,size_t c){
//    // 打印出元素字节
////    char buf[1024];
////    if (c<1024) {
////        memcpy
////    }
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "memcpy==%s", b);
//    return memcpy(a,b,c);
//}

 size_t my_strlen(const char* s){

     // 当以{开头时，单独打印出数据
     if(s[0]=='{'){
         // 分割打印数据

         int len = strlen(s);
         if (len>200) {
             // d长度大于200
             char buf[201]={0};
             int n = 0;

             while ((len-n)>200) {
                 memcpy(buf,s+n,200);
                 buf[200] = '\0';
                 __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "strlen==%s", buf);
                 n+=200;
             }

             memcpy(buf,s+n,len-n);
             buf[len-n+1] = '\0';
             __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "strlen==%s", buf);

         }else{
             __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "strlen==%s", s);
         }

     }else{
          __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "strlen==%s", s);
     }

    return strlen(s);
}

//FILE *my_freopen(const char *filename,const char *mode,FILE *stream){
//    __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "freopen==%s", filename);
//    return freopen(filename,mode,stream);
//}

//void getfilestr(FILE *fp) {
//    int MAXSIZE = 0xFFF;
//    char proclnk[0xFFF];
//    char filename[0xFFF];
//    int fno;
//    ssize_t r;
//
//    // test.txt created earlier
//    if (fp != NULL) {
//        fno = fileno(fp);
//        sprintf(proclnk, "/proc/self/fd/%d", fno);
//        r = readlink(proclnk, filename, MAXSIZE);
//        if (r < 0) {
//            __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "fread==%s","failed to readlink");
//            return;
//        }
//        filename[r] = '\0';
//
//        if (strcmp(filename,"/data/app/com.tencent.mtt-2/base.apk")==0) {
//        }
//        else if(strcmp(filename,"/data/app/com.qihoo.magic-1/base.apk")==0){
//        }
//        else if(strcmp(filename,"/data/app/com.tencent.mtt-2/base.apk")==0){
//        }
//        else if(strcmp(filename,"/data/app/com.tencent.mtt-2/base.apk")==0){
//        }
//        else if(strcmp(filename,"/data/app/com.tencent.mtt-2/base.apk")==0){
//        }
//        else{
//         __android_log_print(ANDROID_LOG_ERROR, "smid_hook", "fread==fp -> fno -> filename: %p -> %d -> %s",fp, fno, filename);
//        }
//    }
//    return;
//}

void Java_com_qiyi_biz_NativeHandler_start(JNIEnv* env, jobject obj)
{
    (void)env;
    (void)obj;

    // xhook_register("^/system/.*\\.so$",  "__android_log_print", my_system_log_print,  NULL);
    // xhook_register("^/vendor/.*\\.so$",  "__android_log_print", my_system_log_print,  NULL);
    // xhook_register(".*/libtest\\.so$", "__android_log_print", my_libtest_log_print, NULL);
    
//    xhook_register(".*/libdu\\.so$","fopen",my_fopen,NULL);
//    xhook_register(".*/libdu\\.so$","popen",my_popen,NULL);
//    xhook_register(".*/libdu\\.so$","open",my_open,NULL);
    xhook_register(".*/libdu\\.so$","strlen",my_strlen,NULL);
//    xhook_register(".*/libdu\\.so$","strstr",my_strstr,NULL);
//    xhook_register(".*/libdu\\.so$","strcpy",my_strcpy,NULL);
//    xhook_register(".*/libdu\\.so$","strcmp",my_strcmp,NULL);
//     xhook_register(".*/libdu\\.so$","memcpy",my_memcpy,NULL);
//     xhook_register(".*/libdu\\.so$","__system_property_get",my_get_sys,NULL);
//     xhook_register(".*/libdu\\.so$","strcasecmp",my_strcasecmp,NULL);
//    xhook_register(".*/libdu\\.so$","sscanf",my_sscanf,NULL);
//    xhook_register(".*/libdu\\.so$","creat",my_creat,NULL);
//    xhook_register(".*/libdu\\.so$","read",my_read,NULL);
//    xhook_register(".*/libdu\\.so$","fread",my_fread,NULL);
//    xhook_register(".*/libdu\\.so$","sprintf",my_sprintf,NULL);
//    xhook_register(".*/libdu\\.so$","freopen",my_freopen,NULL);
    

    //just for testing
    // xhook_ignore(".*/liblog\\.so$", "__android_log_print"); //ignore __android_log_print in liblog.so
    // xhook_ignore(".*/libjavacore\\.so$", NULL); //ignore all hooks in libjavacore.so
    
    // xhook_ignore(".*/libc\\.so$", "fopen");
    // xhook_ignore(".*/libc\\.so$", "strlen");
}
