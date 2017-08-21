//
// Created by nikitas on 20.03.16.
//

#ifndef LINEDETECTOR_BASEDETECTOR_H
#define LINEDETECTOR_BASEDETECTOR_H

#include <fstream>

#include "opencv2/opencv.hpp"

//#include "utils/Logger.h"
//#include "utils/Stopwatch.h"

namespace ant {

    class BaseDetector {
    public:
        BaseDetector(const std::string &detector_name = "");

        const std::string &detectorName();

    private:
        const std::string m_detector_name;
    };

}

#endif //LINEDETECTOR_BASEDETECTOR_H
