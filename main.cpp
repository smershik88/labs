#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

struct CityInfo {
    std::string country;
    unsigned int population;
    unsigned int square;
};

using namespace std::string_literals;
using StringsArray_t = std::vector<std::string>;
using CityInfoMap_t = std::unordered_map<std::string, CityInfo>;

std::string trimString(std::string &str) {
    const std::size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) {
        return ""s;
    }
    const std::size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, last - first + 1);
}

bool readStringsFromFile(const std::string &file_name,
                         StringsArray_t &string_array) {
    std::ifstream fileStream{file_name};
    if (!fileStream.is_open()) {
        return false;
    }
    while (fileStream.good()) {
        std::string line{};
        std::getline(fileStream, line, '\n');
        string_array.push_back(line);
    }
    return true;
}

bool readTokensFromString(const std::string &str, StringsArray_t &tokens,
                          const char delim = ';') {
    if (str.length() < 2) {
        return false;
    }
    std::stringstream sstream{str};
    while (sstream.good()) {
        std::string token{};
        std::getline(sstream, token, delim);
        tokens.push_back(trimString(token));
    }
    return true;
}

CityInfo getCityInfo(const StringsArray_t &tokens_array) {
    if (tokens_array.size() < 4) {
        return CityInfo{};
    }
    return CityInfo{
        .country = tokens_array[1],
        .population = static_cast<unsigned int>(std::stoi(tokens_array[2])),
        .square = static_cast<unsigned int>(std::stoi(tokens_array[3]))};
}

bool pushCityInfo(CityInfoMap_t &city_info_map, const std::string &city_name,
                  const CityInfo &city_info) {
    bool result = false;
    if (city_info.country.empty()) {
        return result;
    }
    std::tie(std::ignore, result) =
        city_info_map.insert({city_name, city_info});
    return result;
}
bool fillCityInfoMap(CityInfoMap_t &city_info_map,
                     const StringsArray_t &string_array) {
    constexpr unsigned char tokens_in_string_number = 4;
    for (auto &&str : string_array) {
        StringsArray_t tokensArray{};
        if (!readTokensFromString(str, tokensArray) or
            tokensArray.size() != tokens_in_string_number) {
            std::cerr << "Error! Incorrect record if city: " << tokensArray[0]
                      << "!\n";
            return false;
        }
        if (!pushCityInfo(city_info_map, tokensArray[0],
                          getCityInfo(tokensArray))) {
            std::cerr << "Error! It was not possible to add information about "
                         "the city, perhaps the city record is duplicated!\n";
            return false;
        }
    }
    return true;
}

void printCityInfoMap(const CityInfoMap_t &city_info_map) {
    for (auto &&[city_name, city_info] : city_info_map) {
        std::cout << city_name << " : " << city_info.country << ", "
                  << city_info.population << ", " << city_info.square << '\n';
    }
}

void printCountriesWithCitiesMoreThan(const CityInfoMap_t &city_info_map,
                                      unsigned int population) {
    auto population_more_than =
        [population](const std::pair<std::string, CityInfo> city_info) {
            return city_info.second.population > population;
        };
    std::set<std::string> countries;
    for (auto &&[city_name, city_info] :
         city_info_map | std::views::filter(population_more_than)) {
        countries.insert(city_info.country);
    }
    for (auto &&country : countries) {
        std::cout << country << " \n";
    }
}

std::string getTheMostPopulated(const CityInfoMap_t &city_info_map,
                                const std::string &country) {
    std::string result{"Not found"};
    unsigned int max_population = 0;
    for (auto &&[city_name, city_info] : city_info_map) {
        if (city_info.country == country) {
            if (city_info.population > max_population) {
                max_population = city_info.population;
                result = city_name;
            }
        }
    }
    return result;
}

unsigned int getCityCountByCountry(const CityInfoMap_t &city_info_map,
                                   const std::string &country) {
    unsigned int result = 0;
    auto city_in_country =
        [country](const std::pair<std::string, CityInfo> city_info) {
            return city_info.second.country == country;
        };
    auto cities = city_info_map | std::views::filter(city_in_country);
    result = static_cast<unsigned int>(
        std::ranges::distance(cities.begin(), cities.end()));
    return result;
}

std::string getTheMostDenselyPopulated(const CityInfoMap_t &city_info_map) {
    std::string result{"Not found"};
    double max_population_density = 0;
    for (auto &&[city_name, city_info] : city_info_map) {
        if (const double density =
                static_cast<double>(city_info.population) / city_info.square;
            density > max_population_density) {
            max_population_density = density;
            result = city_name;
        }
    }
    return result;
}

int main(int argc, char *args[]) {
    const std::string path_to_file =
        argc > 1 ? std::string(args[1]) : "input.txt"s;

    std::cout << "Reading data from " << path_to_file << "...\n";

    StringsArray_t string_array{};
    if (!readStringsFromFile(path_to_file, string_array)) {
        std::cerr << "Error! Can't read file!\n";
        return EXIT_FAILURE;
    }
    std::cout << "Number of city records read: " << string_array.size()
              << "\n\n";

    CityInfoMap_t city_info_map{};
    if (!fillCityInfoMap(city_info_map, string_array)) {
        std::cerr << "Error during data processing, the program will be "
                     "terminated!\n";
        return EXIT_FAILURE;
    }

    std::cout << "============================================================="
                 "=====\n";
    printCityInfoMap(city_info_map);
    std::cout << "============================================================="
                 "=====\n\n";

    const std::string country = "Россия"s;

    std::cout << "The number of cities of the country \"" << country
              << "\" read from the file: ";
    std::cout << getCityCountByCountry(city_info_map, country) << "\n\n";

    std::cout << "The most populated city in the \"" << country << "\": ";
    std::cout << getTheMostPopulated(city_info_map, country) << "\n\n";

    std::cout << "The city with the highest population density: ";
    std::cout << getTheMostDenselyPopulated(city_info_map) << "\n\n";

    const unsigned int populate = 20000000;
    std::cout << "Countries with cities with a population of more than "
              << populate << " people:\n";
    printCountriesWithCitiesMoreThan(city_info_map, populate);

    return EXIT_SUCCESS;
}