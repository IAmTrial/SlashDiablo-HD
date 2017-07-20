#pragma once

#include <string>

enum VersionID {
    INVALID = -1,
    VERSION_113c,
    VERSION_113d
};

namespace D2Version {
    extern VersionID versionID;
    void Init();
    std::string GetGameVersion();
};


