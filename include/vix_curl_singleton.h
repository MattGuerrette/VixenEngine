#ifndef VIX_CURL_SINGLETON_H
#define VIX_CURL_SINGLETON_H

#include "vix_platform.h"
#include "vix_singleton.h"
#include "vix_curl.h"
#include "vix_stringutil.h"

namespace Vixen {

    class VIX_API Curl : public Singleton<Curl>
    {
    public:
        static void     Initialize();
        static void     DeInitialize();
        /*static CURLcode EasySetOperation(CURLoption option, ...);*/
        static CURLcode EasyPerform();
        

        ////////////////////////////////////////////////////////
        // Utilities
        ////////////////////////////////////////////////////////

        static std::string HTTPGet(std::string url);
        static void        HTTPPost(std::string url, const char* data);
       
   
        static size_t WriteFunc(void* ptr, size_t size, size_t nmemb, std::string& s);

        static CURL* CurlInstance();

    private:
        CURL* m_curl;
    };

}

#endif