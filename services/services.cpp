#include "services.h"

#include <utility>

Services::Services(Repository<Pet> repository) {
    this->repository = std::move(repository);
    current_index = 0;
}

void Services::add_service(std::string breed, std::string name, int age, std::string photo) {
    Pet pet = Pet(breed, name, age, photo);
    this->repository.add(pet);
    this->undoStack.push_back(std::make_unique<UndoRedoAdd>(pet, &this->repository));
    this->redoStack.clear();
}

void Services::remove_service(Pet &pet) {
    this->repository.remove(pet);
    this->undoStack.push_back(std::make_unique<UndoRedoRemove>(pet, &this->repository));
    this->redoStack.clear();
}
void Services::update_breed_service(Pet& pet,const std::string new_breed) {
    int pos = this->repository.search_by_pet(pet);
    if (pos != -1) {
        this->repository.get_elements(pos).set_breed(new_breed);
        this->save_to_file(this->repository.filename);
    }
    else throw UpdateException("breed, pet does not exist.");
}
void Services::update_name_service(Pet& pet, const std::string new_name) {
    /*
     *Function to update the name of a pet
     */
    int pos = this->repository.search_by_pet(pet);
    if (pos != -1) {
        this->repository.get_elements(pos).set_name(new_name);
        this->save_to_file(this->repository.filename);
    }
    else throw UpdateException("name, pet does not exist.");
}
void Services::update_age_service(Pet& pet, const int new_age) {
    /*
     *Updates the age of a pet
     */
    int pos = this->repository.search_by_pet(pet);
    if (pos != -1) {
        this->repository.get_elements(pos).set_age(new_age);
        this->save_to_file(this->repository.filename);

    }
    else throw UpdateException("age, pet does not exist.");
}
void Services::update_photo_service(Pet& pet, const std::string new_photo) {
    /*
     *Updates the photo of a pet
     */
    int pos = this->repository.search_by_pet(pet);
    if (pos != -1) {
        this->repository.get_elements(pos).set_photo(new_photo);
        this->save_to_file(this->repository.filename);
    }
    else throw UpdateException("photo, pet does not exist.");
}

Repository<Pet> Services::get_all_dogs() {
    /*
     *Function to get all the pets from the repo
     */
    return this->repository;
}
int Services::get_size() {
    /*
     *Function to get the size of the repo
     */
    return this->repository.get_size();
}

Pet Services::getNextPet() {
    /*
     *Returns the pet on the current index, if the index reaches the size, it is reset to 0.
     */
    if (repository.get_size() == 0) return Pet(); // Handle empty case

    Pet p = repository.get_elements(current_index);
    current_index++;
    if (current_index == repository.get_size()) {
        current_index = 0;
    }
    return p;
}
std::vector<Pet> Services::get_by_breed_age(std::string breed, int age) {
    /*
     *returns a list of pets that have a given breed and age >= age
     */
    return this->repository.get_by_breed_age(breed, age);
}

void Services::save_to_file(const std::string& filename) {
    this->repository.save_to_file(filename);
}
void Services::load_from_file(const std::string& filename) {
    this->repository.load_from_file(filename);
}

void Services::update_pet_service(const Pet& oldPet, const Pet& newPet) {
    int pos = this->repository.search_by_pet(oldPet);
    if (pos == -1) {
        throw UpdateException("Pet does not exist.");
    }
    // If identity changes, check new identity isn't already taken
    if (!(oldPet == newPet)) {
        int targetPos = this->repository.search_by_pet(newPet);
        if (targetPos != -1) {
            throw UpdateException("A pet with the new breed and name already exists.");
        }
    }
    this->repository.get_elements(pos) = newPet;
    this->repository.save_to_file(this->repository.filename);

    this->undoStack.push_back(std::make_unique<UndoRedoUpdate>(oldPet, newPet, &this->repository));
    this->redoStack.clear();
}

void Services::undo() {
    if (this->undoStack.empty()) {
        throw std::runtime_error("No more operations to undo!");
    }
    auto action = std::move(this->undoStack.back());
    this->undoStack.pop_back();
    action->executeUndo();
    this->redoStack.push_back(std::move(action));
}

void Services::redo() {
    if (this->redoStack.empty()) {
        throw std::runtime_error("No more operations to redo!");
    }
    auto action = std::move(this->redoStack.back());
    this->redoStack.pop_back();
    action->executeRedo();
    this->undoStack.push_back(std::move(action));
}