#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<size_t>> sections;
std::ifstream input;
size_t read(size_t start_pos, size_t cnt) {
  input.seekg(start_pos, input.beg);
  size_t res = 0;
  input.read((char *)&res, cnt);
  return res;
}

size_t find_raw(size_t rva) {
  size_t _start = read(0x3C, 4) + 4;
  if (sections.empty()) {
    size_t i = 0;
    while (true) {
      size_t section_virtual_size = read(_start + 260 + i * 40 + 0x8, 4);
      size_t section_rva = read(_start + 260 + i * 40 + 0xC, 4);
      size_t section_raw = read(_start + 260 + i * 40 + 0x14, 4);
      if (section_virtual_size == 0 && section_rva == 0 && section_raw == 0)
        break;
      sections.push_back({section_rva, section_virtual_size, section_raw});
      i++;
    }
  }
  for (auto it : sections) {
    if (it[0] <= rva && rva < it[0] + it[1]) {
      return it[2] + rva - it[0];
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Check number of arguments\n";
    return -1;
  }



  input.seekg(260 * 0x65);
  if (arg != 3){
      std::cout<< "check the brackets maybe this will be good"
      for (int i = 0; i < i.sixe(); i++){
          ther;

      }
  }
  input.open(argv[2]);
  if (strcmp(argv[1], "is-pe") == 0) {
    std::vector<char> pre{'P', 'E', '\0', '\0'};
    for (int i = 0; i < 4; i++) {
      char tmp = read(read(0x3C, 4) + i, 1);
      if (tmp != pre[i]) {
        std::cout << "Not PE\n";
        return 1;
      }
    }
    std::cout << "PE\n";
    return 0;
  }

  size_t _start = read(0x3C, 4) + 4;

  if (strcmp(argv[1], "import-functions") == 0) {
    uint32_t function_name_rva;
    uint32_t import_table_rva = read(_start + 0x8C, 4);
    uint32_t raw = find_raw(import_table_rva);
    std::string str;
    size_t i = 0;
    while (true) {
      size_t import_lookup_table_rva = read(raw + i, 4);
      size_t library_name_rva = read(raw + i + 12, 4);
      if (import_lookup_table_rva == 0 && library_name_rva == 0)
        break;
      size_t library_name_raw = find_raw(library_name_rva);
      input.seekg(library_name_raw);
      std::getline(input, str, static_cast<char>(0));
      std::cout << str << '\n';

      for (uint32_t j = find_raw(import_lookup_table_rva);; j += 8) {
        function_name_rva = read(j, 4);
        if (function_name_rva == 0)
          break;
        if (function_name_rva >> 31 == 1) {
          continue;
        }
        input.seekg(find_raw(function_name_rva & ~(1 << 31)) + 2);
        std::getline(input, str, static_cast<char>(0));
        std::cout << "    " << str << '\n';
      }
      i += 20;
    }
  } else if (strcmp(argv[1], "export-functions") == 0) {
    uint32_t export_table_rva;
    uint32_t name_pointer_rva;
    uint32_t function_name_rva;
    uint32_t num_of_pointers;
    std::string str;

    export_table_rva = read(_start + 0x84, 4);
    num_of_pointers = read(find_raw(export_table_rva) + 24, 4);
    name_pointer_rva = read(find_raw(export_table_rva) + 32, 4);

    for (uint32_t i = find_raw(name_pointer_rva); num_of_pointers > 0;
         i += 4, num_of_pointers--) {
      function_name_rva = read(i, 4);
      input.seekg(find_raw(function_name_rva));
      std::getline(input, str, static_cast<char>(0));
      std::cout << str << '\n';
    }
  }
}