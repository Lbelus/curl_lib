# curl_lib
Implementation of a custom libcurl.


### Description

Curl feature:

``/!\ HTTP/2 and HTTP/3 has not been implemented be weary with your credentials /!\``   

ssl encryption, tsl handshake, http, https, user agent, custom header, POST and GET.

Allow to build payload with a custom user agent and authenticate


Curl core implementation:
This curl implementation involves three main functions - init_my_curl, my_curl, and clean_my_curl.
The init_my_curl function initializes a 'my_curl' request based on the given URI and user argument. If the user argument is not a URL or uses a protocol other than HTTP, the function handles these cases accordingly.
The my_curl function performs a curl-like request using the provided uri_s_t structure, calling the perform_get_request function which connects to the server, sends a GET request, reads the server's response and writes it to the standard output.
The clean_my_curl function cleans up resources associated with the provided uri_s_t structure.
The project makes use of socket programming to handle HTTP requests and responses.
The project has been developped to meet but requirements only but is leaving structs and branching paths available for further updates.


## Explaining the netscape cookie jar format : 

Every elements of a cookie are separated by a ';'

|NUMBER	|TYPE EXAMPLE|	DESCRIPTION| HOW TO IDENTIFY|
|-------|------------|-------------|----|
|string |example.com |the domain name                               | Search for "Domain="|
|boolean|   FALSE    |include subdomains                            | If domain has a leading "." or not|
|string |	/foobar/ |path                                          | Search for "Path="|
|boolean|  TRUE      |send/receive over HTTPS only                  | Search for "Secure"|
|number |1462299217  | expires at - seconds since Jan 1st 1970, or 0| Search for "Expires="|
|string	|person	     |name of the cookie                            | First element of a cookie before '='|
|string	|daniel	     |value of the cookie                           | First element of a cookie after '='|


## User Agents selection

This custom lib curl is allowing the use of following user agents:
| User-agent designation        | User-agent                                                                                              |
|-------------------------------|---------------------------------------------------------------------------------------------------------|
| Google Chrome on Windows      | Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36 |
| Mozilla Firefox on Windows    | Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:89.0) Gecko/20100101 Firefox/89.0                          |
| Microsoft Edge on Windows     | Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.864.59 Safari/537.36 Edg/91.0.864.59 |
| Safari on macOS               | Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/14.1.1 Safari/605.1.15 |
| Google Chrome on macOS        | Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.114 Safari/537.36 |
| Mozilla Firefox on macOS      | Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:89.0) Gecko/20100101 Firefox/89.0                      |
| Safari on iPhone              | Mozilla/5.0 (iPhone; CPU iPhone OS 14_6 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/14.0 Mobile/15E148 Safari/604.1 |
| Google Chrome on Android      | Mozilla/5.0 (Linux; Android 11; Pixel 5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.114 Mobile Safari/537.36 |
| Mozilla Firefox on Android    | Mozilla/5.0 (Android 11; Mobile; rv:89.0) Gecko/89.0 Firefox/89.0                                       |
| Googlebot (Google's Web Crawler) | Mozilla/5.0 (compatible; Googlebot/2.1; +http://www.google.com/bot.html)                            |
| Bingbot (Bing's Web Crawler)  | Mozilla/5.0 (compatible; bingbot/2.0; +http://www.bing.com/bingbot.htm)                                 |
| Yahoo! Slurp (Yahoo's Web Crawler) | Mozilla/5.0 (compatible; Yahoo! Slurp; http://help.yahoo.com/help/us/ysearch/slurp)               |
| DuckDuckBot (DuckDuckGo's Web Crawler) | Mozilla/5.0 (compatible; DuckDuckBot/1.0; +http://duckduckgo.com/duckduckbot.html)           |
| Opera on Windows              | Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36 OPR/77.0.4054.90 |
| Opera on macOS                | Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.114 Safari/537.36 OPR/77.0.4054.90 |

You can also add you own user-agent by modifying the user_agent.txt file.




## Python extending

Create a virtual env
```bash
python3 -m venv myportenv-env
source myportenv-env/bin/activate
pip install -U pip setuptools
```

To build and install project 
```bash
python3 setup.py build
python3 setup.py install
```

### case usage 

You can read from any FD meaning a socket as well:
```python
import linkedin_api_module

cookie_jar = linkedin_api_module.login("useName", "passWord", "ANDROID OS", "https://www.linkedin.com/uas/authenticate")
linkedin_api_module.free_llist(cookie_jar)

```




## Installation

To install this project, follow these steps:

- Clone the repository to your local machine.
- In your terminal, navigate to the project folder.
- Run ``make`` command to compile the project. This will generate the executable my_curl.
- Run ``fclean`` to clean the build dir and the all binaries. 

## Usage
To use my_curl, use the following command format:

```c
#include <curl_api.h>

int main(void)
{
    node_t* cookie_jar = login("useName", "passWord", "ANDROID OS", "https://www.linkedin.com/uas/authenticate");
    free_llist(cookie_jar);
    return EXIT_SUCCESS;
}
```




Optimization : 

- The linkedlist sucks baaaad; 
- in ``req_res.c`` function : ``node_t* set_http_responser_header(int sockfd)`` : "\r" search should be implemented at readline level;
- improve quick fix on set_parse_struct(url_p_s_t* url_s, char* domain, char* path) in case the last char of the URL before '\0' is not a '\';
- curl_ft.c -> // refactor here string should be stored on user agent struct


### The Core Team
* [Lorris BELUS](//github.com/Lbelus) - Developer