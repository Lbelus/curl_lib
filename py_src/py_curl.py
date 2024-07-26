import curl_api_module

cookie_jar = curl_api_module.login("useName", "passWord", "ANDROID OS", "https://www.linkedin.com/uas/authenticate")
curl_api_module.free_llist(cookie_jar)
