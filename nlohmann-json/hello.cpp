#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>

int main(int argc, const char **argv) {
    nlohmann::json j1 = R"({ "name": "wallace", "gender": "male", "languages": ["c", "c++"]})"_json;

    std::cout << "==== print JSON object ====" << std::endl;
    std::cout << j1 << std::endl;

    std::cout << "==== print stringified JSON object ====" << std::endl;
    std::cout << j1.dump() << std::endl;

    std::cout << "==== print beautified JSON object ====" << std::endl;
    /* std::setw will make the print indented (even if there are only one element inside the JSON) */
    std::cout << std::setw(4) << j1 << std::endl;

    std::cout << "==== getting a value ====" << std::endl;
    std::cout << j1["name"] << std::endl;
    std::cout << j1["languages"][0] << std::endl;
    std::cout << j1["languages"][2] << std::endl;
    std::cout << j1["languages"][2].is_null() << std::endl;

    std::cout << "==== getting a value explicitly ====" << std::endl;
    std::cout << j1["name"].get<std::string>() << std::endl;

    std::cout << "==== setting a value ====" << std::endl;
    j1["languages"][2] = "erlang";
    std::cout << j1 << std::endl;

    /* you can also directly set field even if it's parent does not exist.
     * (they will be created automaticlly, just like `mkdir -p`)
     */
    j1["languages"][4]["name"]["type"] = "cool";
    j1["languages"][5][1][2] = "cool";
    std::cout << j1 << std::endl;

    std::cout << "==== getting JSON from file ====" << std::endl;
    /* make sure you are in the cpp-playground directory, or the file path is wrong */
    std::ifstream json_file("./nlohmann-json/test.json");
    json_file >> j1;
    std::cout << j1 << std::endl;

    return 0;
}