#include "user_gui.h"
#include "mymodel.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QString>
#include <QDesktopServices>
#include <QTableView>
#include <QUrl>

#include "mywindow.h"

UserGUI::UserGUI(Services& service,FileAdoptionList* adoptionList, QWidget* parent)
    : QWidget(parent), service(service), adoptionList(adoptionList), currentPetIndex(0) {
    Repository<Pet> repo = service.get_all_dogs();
    for (int i = 0; i < repo.get_size(); i++) {
        validPets.push_back(repo.get_elements(i));
    }
    setupUI();
    connectSignalsAndSlots();
    displayCurrentPet();
    populateAdoptedList();
}
void UserGUI::setupUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    QVBoxLayout* leftLayout = new QVBoxLayout();

    QFormLayout* filterLayout = new QFormLayout();
    breedFilterEdit = new QLineEdit(this);
    ageFilterEdit = new QLineEdit(this);
    filterLayout->addRow("Filter Breed (leave empty for all):", breedFilterEdit);
    filterLayout->addRow("Filter by Min Age:", ageFilterEdit);

    filterButton = new QPushButton("Search",this);
    leftLayout->addLayout(filterLayout);
    leftLayout->addWidget(filterButton);

    lblPetDetails = new QLabel("No pets available", this);
    lblPetDetails->setAlignment(Qt::AlignCenter);

    QFont font = lblPetDetails->font();
    font.setPointSize(14);
    font.setBold(true);
    lblPetDetails->setFont(font);
    lblPetDetails->setMinimumHeight(100);

    leftLayout->addWidget(lblPetDetails);

    QHBoxLayout* actionLayout = new QHBoxLayout();
    btnAdopt = new QPushButton("Adopt",this);
    btnNext = new QPushButton("Next",this);
    showTableView = new QPushButton("Show table",this);
    actionLayout->addWidget(btnAdopt);
    actionLayout->addWidget(btnNext);
    actionLayout->addWidget(showTableView);

    leftLayout->addLayout(actionLayout);
    mainLayout->addLayout(leftLayout);

    QVBoxLayout* rightLayout = new QVBoxLayout();

    QLabel* listTitle = new QLabel("My adoption List", this);
    rightLayout->addWidget(listTitle);

    adoptedListWidget = new QListWidget(this);
    rightLayout->addWidget(adoptedListWidget);

    OpenFile = new QPushButton("Open File (CSV/HTML)", this);
    rightLayout->addWidget(OpenFile);

    mainLayout->addLayout(rightLayout);

    this->setWindowTitle("Pet Shelter - User Mode");
    this->resize(700, 400);

}

void UserGUI::connectSignalsAndSlots() {
    connect(filterButton, &QPushButton::clicked, this, &UserGUI::filterPets);
    connect(btnNext, &QPushButton::clicked, this, &UserGUI::nextPet);
    connect(btnAdopt, &QPushButton::clicked, this, &UserGUI::adoptPet);
    connect(OpenFile, &QPushButton::clicked, this, &UserGUI::openFile);
    connect(showTableView, &QPushButton::clicked, this, &UserGUI::tableView);
}
void UserGUI::displayCurrentPet() {
    if (validPets.empty()) {
        lblPetDetails->setText("No pets match your criteria.");
        return;
    }
    Pet p = validPets[currentPetIndex];
    QString details = QString("Breed: %1\nName: %2\nAge: %3\nPhoto: %4")
    .arg(QString::fromStdString(p.get_breed()), QString::fromStdString(p.get_name()))
    .arg(p.get_age())
    .arg(QString::fromStdString(p.get_photo()));
    lblPetDetails->setText(details);
    //std::string command = "start " + p.get_photo();
    //system(command.c_str());
    openPhotoLink();
}

void UserGUI::openPhotoLink() {
    if (validPets.empty()) return;

    Pet p = validPets[currentPetIndex];
    std::string command = "start " + p.get_photo();
    system(command.c_str());
}

void UserGUI::filterPets() {
    std::string breed = breedFilterEdit->text().toStdString();

    int age = 0;
    if (!ageFilterEdit->text().isEmpty()) {
        age = ageFilterEdit->text().toInt();
    }
    validPets = service.get_by_breed_age(breed, age);
    currentPetIndex = 0;
    displayCurrentPet();
}

void UserGUI::nextPet() {
    if (validPets.empty()) {
        return;
    }
    currentPetIndex++;
    if (currentPetIndex >= validPets.size()) {
        currentPetIndex = 0;
    }
    displayCurrentPet();
}
void UserGUI::adoptPet() {
    if (validPets.empty()) {
        QMessageBox::warning(this, "Warning", "No pets to adopt!");
        return;
    }
    Pet p = validPets[currentPetIndex];
    if (adoptionList != nullptr) {
        adoptionList->add_pet(p);
    }

    QMessageBox::information(this, "Success", QString::fromStdString("You adopted " + p.get_name() + "!"));

    populateAdoptedList();
    this->nextPet();

}
void UserGUI::populateAdoptedList() {
    adoptedListWidget->clear();
    for (const Pet& p : adoptionList->get_pets()) {
        QString itemText = QString::fromStdString(p.get_name() + " (" + p.get_breed() + ")");
        adoptedListWidget->addItem(itemText);
    }

}

void UserGUI::openFile() {
    if (!FileWindow) {
        FileWindow = new FileGUI(adoptionList);
    }
    FileWindow->show();
}

void UserGUI::tableView() {

    auto* adoptionWindow = new AdoptionWindow(this->adoptionList->get_pets(),this);
    adoptionWindow->show();

}