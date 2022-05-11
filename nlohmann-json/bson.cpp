#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

/* this will reset the seekg of the stream */
int size_of_ifstream(std::ifstream &stream) {
    int begin = stream.tellg();
    stream.seekg(0, std::ifstream::end);
    int end = stream.tellg();
    stream.seekg(0, std::ifstream::beg);
    return end - begin;
}

int main(int argc, const char **argv) {
    nlohmann::json j = R"({ "name": "wallace", "gender": "male" })"_json;
    std::vector<uint8_t> v_bson = nlohmann::json::to_bson(j);

    const std::string tmpfile = "/tmp/my-bson-tmp-file.txt";
    std::ofstream output(tmpfile);
    output.write(reinterpret_cast<char *>(v_bson.data()), v_bson.size());

    /* if you don't close(or flush) the ostream, the content will not be written to disk */
    output.close();

    std::ifstream input(tmpfile, std::ifstream::binary);
    int buffer_size = size_of_ifstream(input);
    std::vector<uint8_t> read_content(buffer_size);
    input.read(reinterpret_cast<char *>(read_content.data()), 200);

    nlohmann::json j2 = nlohmann::json::from_bson(read_content);
    std::cout << j2 << std::endl;

    return 0;
}