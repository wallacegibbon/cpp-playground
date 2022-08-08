// the std::filesystem need c++17 support, to compile this file:
//  g++ --std=c++17 miscellaneous/get_mac_addresses.cpp

#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>

std::string get_address_from_device(std::filesystem::path device_path) {
	std::ifstream input(device_path / "address");
	std::string result;
	input >> result;
	return result + "@" + device_path.filename().string();
}

std::set<std::string> GetMacAddresses() {
	std::set<std::string> result;
	for (const auto &f :
		std::filesystem::directory_iterator("/sys/class/net"))
	{
		result.insert(get_address_from_device(f.path()));
	}
	return result;
}

int main(int argc, const char **argv) {
	std::set<std::string> mac_addresses = GetMacAddresses();
	for (auto &addr : mac_addresses)
		std::cout << addr << std::endl;
	return 0;
}
