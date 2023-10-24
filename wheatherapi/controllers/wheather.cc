#include "wheather.h"
#include<iomanip>
#include<string>

HttpViewData convertJsonToHttpViewData(const Json::Value& jsonData) {
    HttpViewData viewData;
    for (const auto& key : jsonData.getMemberNames()) {
        if (key == "temperature" || key == "windSpeed") {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << jsonData[key].asDouble();  // Set precision to 2 decimal places
            viewData.insert(key, ss.str());
        } else {
            viewData.insert(key, jsonData[key].asString());
        }
    }
    return viewData;
}

void parse(const HttpResponsePtr &resp, const std::function<void(const HttpResponsePtr &)> &callback) {
    if (resp) {
        Json::Value root;
        std::string body(resp->getBody().data(),resp->getBody().length());
        std::stringstream ss(body);
        ss >> root;
	std::string time = root["data"]["time"].asString();
        double temperature = root["data"]["values"]["temperature"].asDouble();
        int humidity = root["data"]["values"]["humidity"].asInt();
        double windSpeed = root["data"]["values"]["windSpeed"].asDouble();
        std::string time_t = time.substr(0,10);

        std::cout << temperature << std::endl;
        std::cout << humidity << std::endl;
        std::cout << windSpeed << std::endl;
        std::cout << time_t << std::endl;

        Json::Value jsonData;
        jsonData["temperature"] = temperature;
        jsonData["humidity"] = humidity;
        jsonData["windSpeed"] = windSpeed;
        jsonData["time"] = time_t;

       // HttpViewData viewData = convertJsonToHttpViewData(jsonData);

       // auto response = HttpResponse::newHttpViewResponse("wheather", viewData);
       // response->setStatusCode(HttpStatusCode::k200OK);
        std::cout << "reach1" << std::endl;
       auto response = HttpResponse::newHttpJsonResponse(jsonData);
        response->setStatusCode(HttpStatusCode::k200OK);
        callback(response);

    } else {
   	 std::cout << "error " << std::endl;
        auto errorResponse = HttpResponse::newHttpResponse();
        errorResponse->setBody("Error occurred while processing the request");
        errorResponse->setStatusCode(HttpStatusCode::k404NotFound);
        callback(errorResponse);
    }
}

void wheather::wheather1(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, double &&latitude, double &&longitude) const {
    auto client = HttpClient::newHttpClient("https://api.tomorrow.io");
    auto newReq = HttpRequest::newHttpRequest();
    newReq->setMethod(Get);
    newReq->setPath("/v4/weather/realtime");
    std::string location = std::to_string(latitude) + "," + std::to_string(longitude);
    newReq->setParameter("location", location);
    newReq->setParameter("apikey", "eo5VW45tYUJERBikVlpdZmCdqnNpkk5c");

    client->sendRequest(newReq, [callback](ReqResult result, const HttpResponsePtr &response) {
        if (result == ReqResult::Ok) {
            parse(response, callback);
        } else {
            auto error = HttpResponse::newHttpResponse();
                std::cout << "error2 " << std::endl;
            error->setBody("Error occurred while parsing");
            error->setStatusCode(HttpStatusCode::k404NotFound);
            callback(error);
        }
    });
}
     


