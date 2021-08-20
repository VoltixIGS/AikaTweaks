#include "main.hpp"
#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

DEFINE_CONFIG(AikaTweaksConfig);

Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getAikaTweaksConfig().Init(modInfo);
    getLogger().info("Completed AikaTweaks setup!");
}

extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing AikaTweaks...");
    AikaTweaks::Install();
    getLogger().info("Installed AikaTweaks!");
}