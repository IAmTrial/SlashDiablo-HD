#include "D2HDConfig.h"

void Config::ReadConfig() {
    char path[] = "./D2HD.ini";
    std::string sectionName = "Settings";
    const DWORD defaultColor = 0xFFFFFFFF;
    DWORD tempColor;

    tempColor = GetPrivateProfileIntA(sectionName.c_str(), "Left Panel Background Color", defaultColor, path);
    if (tempColor == defaultColor) {
        std::stringstream stream;
        stream << "0x" << std::hex << defaultColor;
        std::string defaultColorStr = stream.str();
        WritePrivateProfileStringA(sectionName.c_str(), "Left Panel Background Color", defaultColorStr.c_str(), path);
    }

    LeftPanelBackgroundColor = Color::FormatRGBtoBGR(tempColor);

    tempColor = GetPrivateProfileIntA(sectionName.c_str(), "Left Panel Border Color", defaultColor, path);
    if (tempColor == defaultColor) {
        std::stringstream stream;
        stream << "0x" << std::hex << defaultColor;
        std::string defaultColorStr = stream.str();
        WritePrivateProfileStringA(sectionName.c_str(), "Left Panel Border Color", defaultColorStr.c_str(), path);
    }
    LeftPanelBorderColor = Color::FormatRGBtoBGR(tempColor);

    tempColor = GetPrivateProfileIntA(sectionName.c_str(), "Right Panel Border Color", defaultColor, path);
    if (tempColor == defaultColor) {
        std::stringstream stream;
        stream << "0x" << std::hex << defaultColor;
        std::string defaultColorStr = stream.str();
        WritePrivateProfileStringA(sectionName.c_str(), "Right Panel Border Color", defaultColorStr.c_str(), path);
    }
    RightPanelBorderColor = Color::FormatRGBtoBGR(tempColor);

    tempColor = GetPrivateProfileIntA(sectionName.c_str(), "Right Panel Background Color", defaultColor, path);
    if (tempColor == defaultColor) {
        std::stringstream stream;
        stream << "0x" << std::hex << defaultColor;
        std::string defaultColorStr = stream.str();
        WritePrivateProfileStringA(sectionName.c_str(), "Right Panel Background Color", defaultColorStr.c_str(), path);
    }
    RightPanelBackgroundColor = Color::FormatRGBtoBGR(tempColor);

    // Experimental config lines

    sectionName = "Experimental";
}
