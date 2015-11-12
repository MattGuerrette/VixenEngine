#include <vix_curl_singleton.h>

namespace Vixen {

    void Curl::Initialize()
    {
        Curl& _manager = Curl::instance();

        curl_global_init(CURL_GLOBAL_DEFAULT);

        _manager.m_curl = curl_easy_init();
    }

    void Curl::DeInitialize()
    {
        Curl& _manager = Curl::instance();

        curl_easy_cleanup(_manager.m_curl);
    }

    std::string Curl::HTTPGet(std::string url)
    {
        Curl& _manager = Curl::instance();

        std::string _ret;

        curl_easy_setopt(_manager.m_curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(_manager.m_curl, CURLOPT_WRITEFUNCTION, Curl::WriteFunc);
        curl_easy_setopt(_manager.m_curl, CURLOPT_WRITEDATA, &_ret);

        EasyPerform();

        return _ret;
    }

    void Curl::HTTPPost(std::string url, const char* data)
    {
        Curl& _manager = Curl::instance();

        curl_easy_setopt(_manager.m_curl, CURLOPT_POSTFIELDS, "name=Matt&score=3000");

        EasyPerform();
    }

    CURLcode Curl::EasyPerform()
    {
        Curl& _manager = Curl::instance();

        CURLcode code = CURLE_OK;

        code = curl_easy_perform(_manager.m_curl);

        return code;
    }

    size_t Curl::WriteFunc(void* ptr, size_t size, size_t nmemb, std::string& s)
    {
        s += (const char*)ptr;

        return size*nmemb;
    }

    CURL* Curl::CurlInstance()
    {
        return Curl::instance().m_curl;
    }

}