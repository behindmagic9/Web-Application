#include <drogon/drogon.h>
int main() {
    //Set HTTP listener address and port
    drogon::app().addListener("127.0.0.1",8888);
    drogon::app().run();
    return 0;
}
