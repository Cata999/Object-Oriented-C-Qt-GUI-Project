#include "gui.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>

GUI::GUI(Services & services, QWidget *parent)
: QWidget(parent), services(services) {
    setupUI();
    connectSignalsAndSlots();
    populateList();

}
void GUI::setupUI() {
    // 1. Only the main layout gets 'this'
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    // 2. Left Side: The List
    petList = new QListWidget(this);
    mainLayout->addWidget(petList);

    // 3. Right Side: The Form and Buttons
    QVBoxLayout* rightLayout = new QVBoxLayout();

    // The form
    QFormLayout* formLayout = new QFormLayout();
    breedEdit = new QLineEdit(this);
    nameEdit = new QLineEdit(this);
    ageEdit = new QLineEdit(this);
    photoEdit = new QLineEdit(this);

    formLayout->addRow("Breed:", breedEdit);
    formLayout->addRow("Name:", nameEdit);
    formLayout->addRow("Age:", ageEdit);
    formLayout->addRow("Photo Link:", photoEdit);

    rightLayout->addLayout(formLayout);

    // The buttons
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    addButton = new QPushButton("Add", this);
    removeButton = new QPushButton("Remove", this);
    updateButton= new QPushButton("Update", this);
    undoButton= new QPushButton("Undo", this);
    redoButton= new QPushButton("Redo", this);

    undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
    redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);

    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addWidget(updateButton);
    buttonsLayout->addWidget(undoButton);
    buttonsLayout->addWidget(redoButton);

    rightLayout->addLayout(buttonsLayout);

    // 4. Finally, add the right side to the main layout
    mainLayout->addLayout(rightLayout);

    this->setWindowTitle("Pet Shelter - Administrator");
    this->resize(600, 400);
}

void GUI :: connectSignalsAndSlots() {
    connect(addButton, &QPushButton::clicked, this, &GUI::addPet);
    connect(removeButton, &QPushButton::clicked, this, &GUI::removePet);
    connect(updateButton, &QPushButton::clicked, this, &GUI::updatePet);

    connect(petList, &QListWidget::itemSelectionChanged, this, &GUI::onListSelectionChanged);

    connect(undoButton, &QPushButton::clicked, this, &GUI::undo);
    connect(redoButton, &QPushButton::clicked, this, &GUI::redo);

    connect(undoShortcut, &QShortcut::activated, this, &GUI::undo);
    connect(redoShortcut, &QShortcut::activated, this, &GUI::redo);
}

void GUI::populateList() {
    petList->clear();
    Repository<Pet> repo = services.get_all_dogs();

    for (int i = 0; i< repo.get_size(); i++) {
        Pet p = repo.get_elements(i);
        QString itemText = QString::fromStdString(p.get_breed() + " | " + p.get_name());
        petList->addItem(itemText);
    }
}

void GUI::addPet() {
    std::string breed = breedEdit->text().toStdString();
    std::string name = nameEdit->text().toStdString();
    std::string photo = photoEdit->text().toStdString();
    int age = ageEdit->text().toInt();

    try {
        services.add_service(breed, name, age, photo);
        populateList();

        breedEdit->clear(); nameEdit->clear(); ageEdit->clear();
        photoEdit->clear();

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void GUI::removePet() {
    int selectedRow = petList->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "warning", "Please select a pet to remove.");
        return;
    }
    Pet p = services.get_all_dogs().get_elements(selectedRow);

    try {
        services.remove_service(p);
        populateList();
        breedEdit->clear(); nameEdit->clear(); ageEdit->clear();
        photoEdit->clear();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void GUI::updatePet() {
    int selectedRow = petList->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "warning", "Please select a pet to update.");
        return;
    }
    Pet oldPet = services.get_all_dogs().get_elements(selectedRow);
    std::string newBreed = breedEdit->text().toStdString();
    std::string newName = nameEdit->text().toStdString();
    int newAge = ageEdit->text().toInt();
    std::string newPhoto = photoEdit->text().toStdString();

    Pet newPet(newBreed, newName, newAge, newPhoto);
    try {
        services.update_pet_service(oldPet, newPet);
        populateList();
        //changed this into a single one to record in undoRedoUpdate
    }catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
    photoEdit->clear();
    nameEdit->clear();
    ageEdit->clear();
    breedEdit->clear();
}

void GUI::onListSelectionChanged() {
    int selectedRow = petList->currentRow();
    if (selectedRow < 0) {
        return;
    }
    if (selectedRow >= services.get_all_dogs().get_size()) {
        return;
    }

    Pet p = services.get_all_dogs().get_elements(selectedRow);
    breedEdit->setText(QString::fromStdString(p.get_breed()));
    nameEdit->setText(QString::fromStdString(p.get_name()));
    ageEdit->setText(QString::number(p.get_age()));
    photoEdit->setText(QString::fromStdString(p.get_photo()));
}

void GUI::undo() {
    try {
        services.undo();
        populateList();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Undo", e.what());
    }
}


void GUI::redo() {
    try {
        services.redo();
        populateList();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Redo", e.what());
    }
}