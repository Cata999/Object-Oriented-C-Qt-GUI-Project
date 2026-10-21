#pragma once
#include "../domain/domain.h"
#include "../repository/repository.h"

class UndoRedoAction {
public:
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
    virtual ~UndoRedoAction() = default;
};

class UndoRedoAdd : public UndoRedoAction {
private:
    Pet addedPet;
    Repository<Pet>* repo;

public:
    UndoRedoAdd(const Pet& pet, Repository<Pet>* repo) : addedPet(pet), repo(repo) {}

    void executeUndo() override {
        if (repo)
            repo->remove(addedPet);
    }

    void executeRedo() override {
        if (repo)
            repo->add(addedPet);
    }
};

class UndoRedoRemove : public UndoRedoAction {
private:
    Pet removedPet;
    Repository<Pet>* repo;

public:
    UndoRedoRemove(const Pet& pet, Repository<Pet>* repo) : removedPet(pet), repo(repo) {}

    void executeUndo() override {
        if (repo)
            repo->add(removedPet);
    }

    void executeRedo() override {
        if (repo)
            repo->remove(removedPet);
    }
};

class UndoRedoUpdate : public UndoRedoAction {
private:
    Pet oldPet;
    Pet newPet;
    Repository<Pet>* repo;

public:
    UndoRedoUpdate(const Pet& oldPet, const Pet& newPet, Repository<Pet>* repo)
        : oldPet(oldPet), newPet(newPet), repo(repo) {}

    void executeUndo() override {
        if (!repo)
            return;
        int pos = repo->search_by_pet(newPet);
        if (pos != -1) {
            repo->get_elements(pos) = oldPet;
            repo->save_to_file(repo->filename);
        }
    }

    void executeRedo() override {
        if (!repo)
            return;
        int pos = repo->search_by_pet(oldPet);
        if (pos != -1) {
            repo->get_elements(pos) = newPet;
            repo->save_to_file(repo->filename);
        }
    }
};
