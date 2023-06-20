#include <stdio.h>
#include <curl/curl.h>

int main(void)
{
    CURL *curl;
    CURLcode res = CURLE_OK;
    printf("initial CURLcode  %d \n", res);
    /* Each single name resolve string should be written using the format
       HOST:PORT:ADDRESS where HOST is the name libcurl will try to resolve,
       PORT is the port number of the service where libcurl wants to connect to
       the HOST and ADDRESS is the numerical IP address
     */
    // struct curl_slist *host = curl_slist_append(NULL, "example.com:443:127.0.0.1");
    struct curl_slist *host = curl_slist_append(NULL, "example.com:443:93.184.216.34");
    // 93.184.216.34:80
    // host = curl_slist_append(host, "google.com");
    printf("resolving  %s \n", host->data);
    // printf("%s \n", host->next->data);

    // return 0;
      curl = curl_easy_init();
      if(curl) {
        curl_easy_setopt(curl, CURLOPT_RESOLVE, host);
        curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
        res = curl_easy_perform(curl);
        printf("CURLcode after curl_easy_perform  %d \n", res);
        /* always cleanup */
        curl_easy_cleanup(curl);
      }

      curl_slist_free_all(host);

      return (int)res;
}