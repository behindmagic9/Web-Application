#include "simple.h"

void simple::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
    auto response = HttpResponse::newHttpViewResponse("ind");
    response->setStatusCode(k200OK);	
    std::cout << "reach" << std::endl;
    callback(response);
}
