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
 * @file FrequencyReader.h
 * @author Christian Ponte
 * @date 09 April 2018
 *
 * @brief Interface definition for multiple classes providing with alternatives for reading the processor frequencies.
 *
 * Reading the frequency is not a portable solution between systems, therefore we need multiple implementations of the
 * same interface to provide the program with multiple methods without altering the program flow.
 *
 */

#ifndef INTELTURBOBOOST_CHECK_FREQUENCYREADER_H
#define INTELTURBOBOOST_CHECK_FREQUENCYREADER_H

#include <vector>

class FrequencyReader {
public:
    explicit FrequencyReader(const std::vector<unsigned short> &cores) : cores(cores) {};

    virtual std::vector<double> get_frequencies() = 0;

protected:
    const std::vector<unsigned short> &cores;
};

#endif //INTELTURBOBOOST_CHECK_FREQUENCYREADER_H
