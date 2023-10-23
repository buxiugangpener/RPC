#ifndef ROCKET_COMMON_CONFIG_H
#define ROCKET_COMMON_CONFIG_H
#include<string>


namespace Rocket {

    class Config {
    public:
        std::string m_log_level;
    public:
        Config(const char* xmlfile);

    public:
        static Config* GetGlobalConfig();
        static void SetGlobalConfig(const char* xmlfile);

    };

}


#endif