#include <curl/curl.h>

int main(void)
{
	CURL *curl;
	long flags = 0;

	curl_global_init(flags);
}
