#pragma once
#include<drogon/drogon.h>
#include <drogon/HttpController.h>

using namespace drogon;

class wheather : public drogon::HttpController<wheather>
{
  public:
    METHOD_LIST_BEGIN

     ADD_METHOD_TO(wheather::wheather1, "/api?latitude={latitude}&longitude={longitude}", Get);

      

    METHOD_LIST_END

     void wheather1(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double &&latitude, double &&longitude) const;
     

};
