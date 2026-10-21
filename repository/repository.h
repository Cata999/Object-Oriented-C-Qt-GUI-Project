#ifndef A6_7_REPOSITORY_H
#define A6_7_REPOSITORY_H
#include <algorithm>
#include <fstream>
#include <sstream>
#include "../Exceptions/exceptions.h"
#include <vector>

template<typename T>
class Repository {
private:
    std::vector<T> pets;

public:
    std::string filename;

    Repository() = default;

    Repository(const std::string &filename) {
        this->filename = filename;
        this->load_from_file(this->filename);
    }

    void add(const T &pet) {
        if (search_by_pet(pet) != -1) {
            throw RepositoryException("Pet already exists\n");
        }

        pets.push_back(pet);
        this->save_to_file(this->filename);
    }

    void remove(const T &pet) {
        int pos = search_by_pet(pet);
        if (pos != -1) {
            pets[pos] = pets.back();
            pets.pop_back();
            this->save_to_file(this->filename);
        } else throw RepositoryException("Pet not found\n");
    }

    int search_by_pet(const T &pet) {
        auto it = std::find(pets.begin(), pets.end(), pet);
        if (it != pets.end()) {
            return std::distance(pets.begin(), it);
        }
        return -1;
    }

    T &get_elements(int index) {
        return pets[index];
    }

    int get_size() const {
        return pets.size();
    }

    std::vector<T> get_by_breed_age(const std::string breed, int age) const {
        std::vector<T> result;
        for (const auto &pet: pets) {
            if (!breed.empty()) {
                std::copy_if(pets.begin(), pets.end(), std::back_inserter(result), [breed, age](const T &pet) {
                    return pet.get_age() >= age && pet.get_breed() == breed;
                });
            } else {
                if (pet.get_age() >= age) {
                    result.push_back(pet);
                }
            }
        }
        return result;
    }

    void save_to_file(const std::string &filename) {
        std::ofstream file(filename);

        if (!file.is_open()) {
            throw FileException("Failed to open file for writing!");
        }
        for (const auto &pet: pets) {
            file << pet.get_breed() << ",";
            file << pet.get_name() << ",";
            file << pet.get_age() << ",";
            file << pet.get_photo()
                    << "\n";
        }
        file.close();
    }

    void load_from_file(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw FileException("Failed to open file for reading!");
        }
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);

            std::string breed, name, age, photo;

            std::getline(ss, breed, ',');
            std::getline(ss, name, ',');
            std::getline(ss, age, ',');
            std::getline(ss, photo, ',');
            if (!photo.empty() && photo.back() == '\r') {
                photo.pop_back();
            }
            if (!breed.empty()) {
                int age_i = std::stoi(age);
                Pet pet(breed, name, age_i, photo);
                pets.push_back(pet);
            }
        }
        file.close();
    }
};

class FileAdoptionList {
protected:
    std::string filename;
    std::vector<Pet> adoption_list;

public:
    FileAdoptionList(const std::string &filename,std::vector<Pet> &adoption_list) : filename(filename), adoption_list(adoption_list) {
    }

    virtual ~FileAdoptionList() = default;

    void add_pet(const Pet &pet) {
        adoption_list.push_back(pet);
    }

    const std::vector<Pet> &get_pets() const {
        return adoption_list;
    }

    virtual void save_to_file() = 0;

    virtual void open_file() = 0;
};

class CSVAdoptionList : public FileAdoptionList {
public:
    CSVAdoptionList(const std::string &filename, std::vector<Pet> adoption_list ) : FileAdoptionList(filename, adoption_list) {
    }

    void save_to_file() override {
        std::ofstream file("adoption_list.csv");
        if (!file.is_open()) throw FileException("Could not open CSV!");

        for (const auto &pet: this->adoption_list) {
            file << pet.get_breed() << "," << pet.get_name() << ","
                    << pet.get_age() << "," << pet.get_photo() << "\n";
        }
        file.close();
    }

    void open_file() override {
        std::string command = "start adoption_list.csv";
        system(command.c_str());
    }
};

class HTMLAdoptionList : public FileAdoptionList {
public:
    HTMLAdoptionList(const std::string &filename, std::vector<Pet> adoption_list) : FileAdoptionList(filename, adoption_list) {
    }

    void save_to_file() override {
        std::ofstream file("adoption_list.html");
        if (!file.is_open()) throw FileException("Could not open HTML!");

        file << "<!DOCTYPE html>\n";
        file << "<html>\n";
        file << "<head>\n";
        file << "    <title>Adoption List</title>\n";
        file << "</head>\n";
        file << "<body>\n";
        file << "<table border=\"1\">\n";
        file << "    <tr>\n";
        file << "        <td>Breed</td>\n";
        file << "        <td>Name</td>\n";
        file << "        <td>Age</td>\n";
        file << "        <td>Photo link</td>\n";
        file << "    </tr>\n";

        for (const auto &pet: adoption_list) {
            file << "    <tr>\n";
            file << "        <td>" << pet.get_breed() << "</td>\n";
            file << "        <td>" << pet.get_name() << "</td>\n";
            file << "        <td>" << pet.get_age() << "</td>\n";
            file << "        <td><a href=\"" << pet.get_photo() << "\">Link</a></td>\n";
            file << "    </tr>\n";
        }
        file << "</table>\n";
        file << "</body>\n";
        file << "</html>\n";

        file.close();
    }
    void open_file() override {
        std::string command = "start adoption_list.html" ;
        system(command.c_str());
    }
};
#endif //A6_7_REPOSITORY_H
