/*
 * This file is part of IntelTurboBoost-Check.
 * Copyright (C) 2018 by Christian Ponte
 *
 * IntelTurboBoost-Check is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * IntelTurboBoost-Check is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with IntelTurboBoost-Check. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file CpuInfoFrequencyReader.h
 * @author Christian Ponte
 * @date 09 April 2018
 *
 * @brief Brief description
 *
 * Long description
 *
 */

#ifndef INTELTURBOBOOST_CHECK_CPUINFOFREQUENCYREADER_H
#define INTELTURBOBOOST_CHECK_CPUINFOFREQUENCYREADER_H

#include "FrequencyReader.h"

class CPUInfoFrequencyReader : public FrequencyReader {
public:
    explicit CPUInfoFrequencyReader(const std::vector<unsigned short> &cores) : FrequencyReader(cores) {};

    std::vector<double> get_frequencies() override;
};

#endif //INTELTURBOBOOST_CHECK_CPUINFOFREQUENCYREADER_H
