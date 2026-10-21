#pragma once
#ifndef A6_7_SERVICES_H
#define A6_7_SERVICES_H
#include "../domain/domain.h"
#include "../repository/repository.h"
#include "undo_action.h"
#include <vector>
#include <memory>

class Services {
private:
    Repository<Pet> repository;
    int current_index;
    std::vector<std::unique_ptr<UndoRedoAction>> undoStack;
    std::vector<std::unique_ptr<UndoRedoAction>> redoStack;
public:
    Services(Repository<Pet> repository);
    void add_service(std::string breed, std::string name, int age, std::string photo);
    void remove_service(Pet& pet);
    void update_breed_service(Pet& pet, std::string breed);
    void update_name_service(Pet& pet, std::string name);
    void update_age_service(Pet& pet, int age);
    void update_photo_service(Pet& pet, std::string photo);
    void update_pet_service(const Pet& oldPet, const Pet& newPet);
    void undo();
    void redo();
    int get_size();

    Repository<Pet> get_all_dogs();
    Pet getNextPet();
    std::vector<Pet> get_by_breed_age(std::string breed, int age);
    void save_to_file(const std::string& filename);
    void load_from_file(const std::string& filename);
};
#endif //A6_7_SERVICES_H