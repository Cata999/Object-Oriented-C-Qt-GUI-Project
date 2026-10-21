
#ifndef USER_GUI_H
#define USER_GUI_H

#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>

#include "file_gui.h"
#include "../services/services.h"

class UserGUI : public QWidget {
    Q_OBJECT
private:
    Services &service;
    FileAdoptionList* adoptionList;

    std::vector<Pet> validPets;
    int currentPetIndex;

    QLineEdit* breedFilterEdit;
    QLineEdit* ageFilterEdit;
    QPushButton* filterButton;

    QLabel* lblPetDetails;
    QPushButton* btnNext;
    QPushButton* btnAdopt;
    QPushButton* showTableView;

    QListWidget* adoptedListWidget;
    QPushButton* OpenFile;
    FileGUI* FileWindow;
    void setupUI();
    void connectSignalsAndSlots();
    void displayCurrentPet();
    void openPhotoLink();
    void openFile();
    void populateAdoptedList();

private slots:
    void filterPets();
    void nextPet();
    void adoptPet();
    void tableView();

public:
    UserGUI(Services& service, FileAdoptionList* adoptionList, QWidget* parent = nullptr);
    ~UserGUI() = default;
};
#endif
