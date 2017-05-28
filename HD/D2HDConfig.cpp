#include "D2HDConfig.h"

DWORD ReadColor(std::string sectionName, std::string keyName, DWORD defaultColor, std::string path);

void Config::ReadConfig() {
    std::string path = "./D2HD.ini";
    ReadMainSettings(path);
    ReadExperimentalSettings(path);
}

void Config::ReadMainSettings(std::string path) {
    std::string sectionName = "Settings";
    const DWORD defaultColor = 0xFFFFFFFF;

    DWORD tempColor = ReadColor(sectionName, "Left Panel Background Color", defaultColor, path);
    LeftPanelBackgroundColor = Color::FormatRGBtoBGR(tempColor);

    tempColor = ReadColor(sectionName, "Left Panel Border Color", defaultColor, path); 
    LeftPanelBorderColor = Color::FormatRGBtoBGR(tempColor);

    tempColor = ReadColor(sectionName, "Right Panel Border Color", defaultColor, path);
    RightPanelBorderColor = Color::FormatRGBtoBGR(tempColor);

    tempColor = ReadColor(sectionName, "Right Panel Background Color", defaultColor, path);
    RightPanelBackgroundColor = Color::FormatRGBtoBGR(tempColor);

    EnableD2MRPanelBorderStyle = GetPrivateProfileIntA(sectionName.c_str(), "Enable D2MR Border Panel Style", true, path.c_str());
    if (EnableD2MRPanelBorderStyle == true) {
        WritePrivateProfileStringA(sectionName.c_str(), "Enable D2MR Border Panel Style", "1", path.c_str());
    }

    InvertD2MRControlPanel = GetPrivateProfileIntA(sectionName.c_str(), "Invert D2MR Bottom Control Panel", true, path.c_str());
    if (InvertD2MRControlPanel == true) {
        WritePrivateProfileStringA(sectionName.c_str(), "Invert D2MR Bottom Control Panel", "1", path.c_str());
    }

    EnableD2MRBackgroundRibbon = GetPrivateProfileIntA(sectionName.c_str(), "Enable D2MR Panel Background Ribbon", true, path.c_str());
    if (EnableD2MRBackgroundRibbon == true) {
        WritePrivateProfileStringA(sectionName.c_str(), "Enable D2MR Panel Background Ribbon", "1", path.c_str());
    }
}

void Config::ReadExperimentalSettings(std::string path) {
    std::string sectionName = "Experimental";

    EnableCinematicsFix = GetPrivateProfileIntA(sectionName.c_str(), "Enable Cinematics Fix", false, path.c_str());
    if (EnableCinematicsFix == false) {
        WritePrivateProfileStringA(sectionName.c_str(), "Enable Cinematics Fix", "0", path.c_str());
    }
}

DWORD ReadColor(std::string sectionName, std::string keyName, DWORD defaultColor, std::string path) {
    DWORD color = GetPrivateProfileIntA(sectionName.c_str(), keyName.c_str(), defaultColor, path.c_str());
    if (color == defaultColor) {
        std::stringstream stream;
        stream << "0x" << std::hex << defaultColor;
        std::string defaultColorStr = stream.str();
        WritePrivateProfileStringA(sectionName.c_str(), keyName.c_str(), defaultColorStr.c_str(), path.c_str());
    }

    return color;
}
