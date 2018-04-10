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
 * @file PCMFrequencyReader.cpp
 * @author Christian Ponte
 * @date 10 April 2018
 *
 * @brief Brief description
 *
 * Long description
 *
 */

#include "PCMFrequencyReader.h"
#include <sstream>
#include <regex>

std::vector<double> PCMFrequencyReader::get_frequencies(const std::vector<unsigned short> &cores) {
    std::stringstream sstream;

    FILE *pipe = popen("sudo /opt/cesga/sistemas/pcm/pcm.x -i=1 0 2>&1", "r");
    std::array<char, 128> buffer;
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr){
        sstream << buffer.data();
    }
    pclose(pipe);

    std::string line;
    std::smatch m;
    std::regex rexp("^Nominal core frequency: ([[:digit:]]+) Hz$", std::regex_constants::extended);

    // Skip to nominal frequency
    while (std::getline(sstream, line) && !std::regex_search(line, m, rexp));
    const unsigned long nominal_freq = std::stoul(m[1]);

    std::vector<double> frequencies;
    for (unsigned short c : cores){
        rexp = std::regex(
                std::string("^[[:space:]]+") + std::to_string(c) +   // Core ID
                "[[:space:]]+[[:digit:]]" +                          // SKT
                "[[:space:]]+[[:digit:].]+" +                        // EXEC
                "[[:space:]]+[[:digit:].]+" +                        // IPC
                "[[:space:]]+([[:digit:].]+).*$",                    // FREQ + the rest
                std::regex_constants::extended);

        // Skip to selected core frequency
        while (std::getline(sstream, line) && !std::regex_search(line, m, rexp));
        frequencies.push_back(std::stod(m[1]) * nominal_freq / 1000000);
    }

    return frequencies;
}
