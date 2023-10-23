#include"Rocket/common/log.h"
#include"Rocket/common/config.h"
#include<pthread.h>
#include<unistd.h>
void* fun(void*) {
    DEBUGLOG("debug this is thread in %s", "fun");
    INFOLOG("info this is thread in %s", "fun");
    return NULL;
}
int main() {
    Rocket::Config::SetGlobalConfig("../conf/Rocket.xml");

    Rocket::Logger::InitGlobalLogger();

    pthread_t thread;
    pthread_create(&thread, NULL, &fun, NULL);

    DEBUGLOG("test debug log %s", "11");
    INFOLOG("test info log %s", "11");

    pthread_join(thread, nullptr);
    return 0;


}