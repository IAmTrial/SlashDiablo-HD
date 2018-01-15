#include "D2HDResolution.h"

std::vector<D2HD::D2HDResolution> D2HD::D2HDResolution::resolutions = {
    D2HD::D2HDResolution(640, 480),
    D2HD::D2HDResolution(800, 600),
    D2HD::D2HDResolution(800, 600),
    D2HD::D2HDResolution(856, 480),
    D2HD::D2HDResolution(1068, 600)
};

D2HD::D2HDResolution::D2HDResolution(const int width,
                                     const int height) : width(width), height(height) {
}

int D2HD::D2HDResolution::getWidth() const {
    return D2HD::D2HDResolution::width;
}

int D2HD::D2HDResolution::getHeight() const {
    return D2HD::D2HDResolution::height;
}

std::vector<D2HD::D2HDResolution>& D2HD::D2HDResolution::getResolutions() {
    if (resolutions.empty()) {
        resolutions = {
            D2HD::D2HDResolution(640, 480),
            D2HD::D2HDResolution(800, 600),
            D2HD::D2HDResolution(800, 600),
            D2HD::D2HDResolution(856, 480),
            D2HD::D2HDResolution(1068, 600)
        };
    }

    return D2HD::D2HDResolution::resolutions;
}
