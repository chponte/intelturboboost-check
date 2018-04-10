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
 * @file CpuInfoFrequencyReader.cpp
 * @author Christian Ponte
 * @date 09 April 2018
 *
 * @brief Brief description
 *
 * Long description
 *
 */

#include "CPUInfoFrequencyReader.h"
#include <fstream>
#include <regex>

std::vector<double> CPUInfoFrequencyReader::get_frequencies(const std::vector<unsigned short> &cores) {
    std::vector<double> frequencies;
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    std::regex ex;
    std::smatch m;

    for (auto c : cores) {
        // Skip to appropriate core block
        ex = std::regex("^processor[[:space:]]+:[[:space:]]+" + std::to_string(c) + "$",
                        std::regex_constants::extended);
        while (std::getline(cpuinfo, line) && !std::regex_match(line, ex));
        // Look for core frequency
        ex = std::regex("^cpu MHz[[:space:]]+:[[:space:]]+([[:digit:].]+)$", std::regex_constants::extended);
        while (std::getline(cpuinfo, line) && !std::regex_search(line, m, ex));
        frequencies.push_back(std::stod(m[1]));
    }

    return frequencies;
}
