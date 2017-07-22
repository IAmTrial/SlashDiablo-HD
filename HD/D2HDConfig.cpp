#include "D2HDConfig.h"

std::string Config::archiveName;
std::string Config::configPath = "./D2HD.ini";

DWORD ReadColor(std::string sectionName, std::string keyName, DWORD defaultColor);

void Config::ReadConfig() {
    ReadMainSettings();
    ReadExperimentalSettings();
}

void Config::ReadMainSettings() {
    const std::string sectionName = "Settings";

#if USE_CUSTOM_MPQ_FILE
    char tempArchiveName[MAX_PATH] = { '\0' };
    GetPrivateProfileStringA(sectionName.c_str(), "MPQ Name", nullptr, tempArchiveName, MAX_PATH, configPath.c_str());

    if (std::strcmp(tempArchiveName, "") == 0) {
        std::strcpy(tempArchiveName, "D2MultiRes.mpq");
        WritePrivateProfileStringA(sectionName.c_str(), "MPQ Name", tempArchiveName, configPath.c_str());
    }

    archiveName = std::string(tempArchiveName);
#endif

    const DWORD defaultColor = 0xFFFFFFFF;

    DWORD tempColor = ReadColor(sectionName, "Left Panel Background Color", defaultColor);
    LeftPanelBackgroundColor = Color::FormatRGBtoBGR(tempColor);

    tempColor = ReadColor(sectionName, "Left Panel Border Color", defaultColor);
    LeftPanelBorderColor = Color::FormatRGBtoBGR(tempColor);

    tempColor = ReadColor(sectionName, "Right Panel Border Color", defaultColor);
    RightPanelBorderColor = Color::FormatRGBtoBGR(tempColor);

    tempColor = ReadColor(sectionName, "Right Panel Background Color", defaultColor);
    RightPanelBackgroundColor = Color::FormatRGBtoBGR(tempColor);

    EnableD2MRPanelBorderStyle = GetPrivateProfileIntA(sectionName.c_str(), "Enable D2MR Border Panel Style", true, configPath.c_str());
    if (EnableD2MRPanelBorderStyle == true) {
        WritePrivateProfileStringA(sectionName.c_str(), "Enable D2MR Border Panel Style", "1", configPath.c_str());
    }

    InvertD2MRControlPanel = GetPrivateProfileIntA(sectionName.c_str(), "Invert D2MR Bottom Control Panel", true, configPath.c_str());
    if (InvertD2MRControlPanel == true) {
        WritePrivateProfileStringA(sectionName.c_str(), "Invert D2MR Bottom Control Panel", "1", configPath.c_str());
    }

    EnableD2MRBackgroundRibbon = GetPrivateProfileIntA(sectionName.c_str(), "Enable D2MR Panel Background Ribbon", true, configPath.c_str());
    if (EnableD2MRBackgroundRibbon == true) {
        WritePrivateProfileStringA(sectionName.c_str(), "Enable D2MR Panel Background Ribbon", "1", configPath.c_str());
    }

    Enable800ControlPanel = GetPrivateProfileIntA(sectionName.c_str(), "Enable 800x600 Style Control Panel", false, configPath.c_str());
    if (Enable800ControlPanel == false) {
        WritePrivateProfileStringA(sectionName.c_str(), "Enable 800x600 Style Control Panel", "0", configPath.c_str());
    }

    int registryResolution = GetPrivateProfileIntA(sectionName.c_str(), "Resolution", 0, configPath.c_str());
    if (registryResolution == 0 || registryResolution < 0 || registryResolution > NUMBER_OF_CUSTOM_RESOLUTIONS) {
        WritePrivateProfileStringA(sectionName.c_str(), "Resolution", "0", configPath.c_str());
    }

    CustomWidth = GetPrivateProfileIntA(sectionName.c_str(), "Custom Width (can't be larger than 1344)", 1068, configPath.c_str());
    if (CustomWidth == 1068) {
        WritePrivateProfileStringA(sectionName.c_str(), "Custom Width (can't be larger than 1344)", "1068", configPath.c_str());
    } else if (CustomWidth >= 1344 || CustomWidth < 320) {
        CustomWidth = 1344;
    }

    CustomHeight = GetPrivateProfileIntA(sectionName.c_str(), "Custom Height (can't be larger than 700)", 600, configPath.c_str());
    if (CustomHeight == 600) {
        WritePrivateProfileStringA(sectionName.c_str(), "Custom Height (can't be larger than 700)", "600", configPath.c_str());
    } else if (CustomHeight >= 700 || CustomHeight < 240) {
        CustomHeight = 700;
    }
}

void Config::ReadExperimentalSettings() {
    std::string sectionName = "Experimental";
}

void __stdcall Config::WriteRegistryResolution(int mode) {
    const std::string sectionName = "Settings";
    WritePrivateProfileStringA(sectionName.c_str(), "Resolution", std::to_string(mode).c_str(), configPath.c_str());
}

void __stdcall Config::ReadRegistryResolution(int* mode) {
    const std::string sectionName = "Settings";
    *mode = GetPrivateProfileIntA(sectionName.c_str(), "Resolution", 0, configPath.c_str());
}

DWORD ReadColor(std::string sectionName, std::string keyName, DWORD defaultColor) {
    DWORD color = GetPrivateProfileIntA(sectionName.c_str(), keyName.c_str(), defaultColor, Config::configPath.c_str());
    if (color == defaultColor) {
        std::stringstream stream;
        stream << "0x" << std::hex << defaultColor;
        std::string defaultColorStr = stream.str();
        WritePrivateProfileStringA(sectionName.c_str(), keyName.c_str(), defaultColorStr.c_str(), Config::configPath.c_str());
    }

    return color;
}
