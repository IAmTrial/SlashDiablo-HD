#pragma once

#ifndef D2HDRESOLUTION_H
#define D2HDRESOLUTION_H

#include <vector>

namespace D2HD {
class D2HDResolution {
public:
    D2HDResolution(const int width, const int height);
    int getWidth() const;
    int getHeight() const;

    static std::vector<D2HDResolution>& getResolutions();

private:
    static std::vector<D2HDResolution> resolutions;

    int width;
    int height;
};
}

#endif // D2HDRESOLUTION_H
