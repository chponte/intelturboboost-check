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

//
// Created by christian on 10/04/18.
//

#ifndef INTELTURBOBOOST_CHECK_FREQUENCYREADERBUILDER_H
#define INTELTURBOBOOST_CHECK_FREQUENCYREADERBUILDER_H

#include "Definitions.h"
#include "FrequencyReader.h"

#if FREQ_READER_IMPLEMENTATION == cpuinfo

#include "CPUInfoFrequencyReader.h"

#elif FREQ_READER_IMPLEMENTATION == PCM

#include "PCMFrequencyReader.h"

#endif

class FrequencyReaderBuilder {
public:
    FrequencyReaderBuilder() = delete;

    static FrequencyReader *build(const std::vector<unsigned short> &cores) {
#if FREQ_READER_IMPLEMENTATION == cpuinfo
        return new CPUInfoFrequencyReader(cores);
#elif FREQ_READER_IMPLEMENTATION == PCM
        return new PCMFrequencyReader(cores, PCM_EXECUTABLE_PATH);
#else
        return nullptr;
#endif
    }
};


#endif //INTELTURBOBOOST_CHECK_FREQUENCYREADERBUILDER_H
