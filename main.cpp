#include <iostream>
#include "entry.h"
#include <map>
#include <algorithm>
#include <fstream>

#define DEFAULT_FILE_NAME "passwords.store"

void write_to_file(const std::map<std::string, PasswordManager::SecretEntry>
    &entry) {
  std::ofstream ofs(DEFAULT_FILE_NAME);
  boost::archive::text_oarchive oa(ofs);
  // write class instance to archive
  oa << entry;
}

std::map<std::string, PasswordManager::SecretEntry> read_from_file() {
  std::map<std::string, PasswordManager::SecretEntry> entry;
  std::ifstream ifs(DEFAULT_FILE_NAME);
  boost::archive::text_iarchive ia(ifs);
  // write class instance to archive
  ia >> entry;
  return entry;
}

void run_entries() {
  std::ifstream ifile;
  std::map<std::string, PasswordManager::SecretEntry> entry_maps;
  ifile.open(DEFAULT_FILE_NAME);
  if (ifile) {
    ifile.close();
    entry_maps = read_from_file();
  }
  std::string select_option;
  std::string name;
  std::string login;
  std::string password;
  std::string comment;
  while(select_option != "0") {
      std::cout << "Press 1 to add an Entry or 2 to print and entry 3 to \n"
                   "Update and 4 to delete \n";
      std::cout << "Print 0 to exit" << std::endl;
      std::getline(std::cin, select_option);
      std::cout << "You have selected - " << select_option << std::endl;
      std::cin.clear();
      if (select_option == "1") {
          std::cout << "Adding an Entry \n";
          std::cout << "Enter your name: \n";
          std::getline(std::cin, name);
          std::cout << "Enter your login: \n";
          std::getline(std::cin, login);
          std::cout << "Enter your password: \n";
          std::getline(std::cin, password);
          std::cout << "Add Comment: \n";
          std::getline(std::cin, comment);

          std::hash<std::string> hash_obj;
          unsigned long key = hash_obj(name);
          PasswordManager::SecretEntry entry = PasswordManager::create_entity(
              key, name, login, password,comment);

          std::transform(name.begin(), name.end(), name.begin(),
                                 ::tolower);
          entry_maps.insert(std::pair<std::string,
              PasswordManager::SecretEntry>(name,entry));

          // write_to_file(entry_maps);

      }
      else if (select_option == "2") {
        if (entry_maps.empty()) {
          std::cout << "No Entry in the Maps" << std::endl;
          continue;
        }
        std::string name_pattern;
        std::cout << "Search for the Entry \n";
        std::cout << "Enter name term: \n";
        std::getline(std::cin, name_pattern);
        for (const auto &entry: entry_maps){
          if (entry.first.find(name_pattern) < entry.first.size()) {
            std::cout << "Inside entry" << std::endl;
            std::cout << PasswordManager::pretty_read_print(
                entry.second) << std::endl;
          }
        }
        // std::map<std::string, PasswordManager::SecretEntry>
        //    file_entry = read_from_file();
        // std::cout << "Inside File Entry" << std::endl;
        // std::cout << PasswordManager::pretty_read_print(
        //    file_entry) << std::endl;
      }
      else if (select_option == "3") {
        std::string parameter;
        std::string value;
        std::string name_pattern;
        std::string update_confirm;
        std::vector<std::string> delete_key;
        std::map<std::string, PasswordManager::SecretEntry> temp_entry_maps;

        std::cout << "Search for the Entry to Update \n";
        std::cout << "Enter name term: \n";
        std::getline(std::cin, name_pattern);
        for (const auto &entry: entry_maps){
          if (entry.first.find(name_pattern) < entry.first.size()) {
            std::cout << "Found Entry: " << std::endl;
            std::cout << entry.first << std::endl;

            std::cout << "Do you want to update yes/no \n";
            std::getline(std::cin, update_confirm);
            if (update_confirm != "yes") {
              continue;
            }

            std::cout << "Name of entry parameter to change \n";
            std::cout << "Enter parameter name (name|login|password|comment): \n";
            std::getline(std::cin, parameter);
            std::cout << "Enter parameter value: \n";
            std::getline(std::cin, value);
            PasswordManager::SecretEntry new_entry =
                PasswordManager::update_entry(
                entry.second, parameter, value);
            if (parameter == "name") {
              temp_entry_maps[value] = new_entry;
              delete_key.push_back(entry.first);
            }
            else {
              temp_entry_maps[entry.first] = new_entry;
            }
          }
        }
        for (const auto &entry: temp_entry_maps) {
          entry_maps[entry.first] = entry.second;
        }
        for(const auto key: delete_key) {
          entry_maps.erase(key);
        }
      }
      else if (select_option == "4") {
        std::string name_pattern;
        std::string delete_confirm;
        std::vector<std::string> delete_key;
        std::cout << "Search for the Entry to Delete \n";
        std::cout << "Enter name term: \n";
        std::getline(std::cin, name_pattern);
        for (const auto &entry: entry_maps){
          if (entry.first.find(name_pattern) < entry.first.size()) {
            std::cout << entry.first << std::endl;
            std::cout << "Do you want to delete yes/no \n";
            std::getline(std::cin, delete_confirm);
            if (delete_confirm == "yes") {
              delete_key.push_back(entry.first);
            }
          }
        }
        for(const auto key: delete_key) {
          entry_maps.erase(key);
        }
      }

  }

  if (!entry_maps.empty()) {
    write_to_file(entry_maps);
  }
}

int main() {
  //int numer;
  std::cout << "Hello, Guys! Welcome to my channel!" << std::endl;
  // std::string name = "deepak";
  // std::string pattern = "deepak";
  // std::cout << name.find(pattern) << std::endl;
  // std::cin >> numer;
  // std::cout << "Number " << numer << std::endl;
  run_entries();
  return 0;
}
