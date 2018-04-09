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

#include "CpuInfoFrequencyReader.h"
#include <fstream>
#include <regex>

double parse_frequency(std::ifstream &pos) {
    std::string line;
    std::regex freq_exp("^cpu MHz[[:space:]]+:[[:space:]]+([[:digit:].]+)$", std::regex_constants::extended);
    std::smatch m;

    while (std::getline(pos, line) && !std::regex_search(line, m, freq_exp));

    return std::stod(m[1]);
}

std::vector<double> CpuInfoFrequencyReader::get_frequencies(const std::vector<unsigned short> &cores) {
    std::vector<std::regex> regex_core_identifiers;
    std::vector<double> frequencies;
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;

    for (unsigned short core : cores) {
        regex_core_identifiers.emplace_back(std::regex(
                "^processor[[:space:]]+:[[:space:]]+" + std::to_string(core) + "$",
                std::regex_constants::extended));
    }

    while (std::getline(cpuinfo, line)) {
        for (const std::regex &r : regex_core_identifiers) {
            if (std::regex_match(line, r)) {
                frequencies.push_back(parse_frequency(cpuinfo));
            }
        }
    }

    return frequencies;
}
