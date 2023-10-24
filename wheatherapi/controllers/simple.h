#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class simple : public drogon::HttpSimpleController<simple>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    // list path definitions here;
    PATH_ADD("/get", Get);
    PATH_LIST_END
};
