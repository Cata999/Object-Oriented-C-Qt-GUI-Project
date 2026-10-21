#include "file_gui.h"


#include <QLayout>
#include <QMessageBox>

FileGUI::FileGUI(FileAdoptionList* adoptionList, QWidget* parent) : QWidget(parent), adoptionList(adoptionList) {
    setupUI();
    connectSignalsAndSlots();
}

void FileGUI::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    titleLabel = new QLabel("Select the file type!", this);
    titleLabel->setAlignment(Qt::AlignCenter);

    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setMinimumHeight(80);

    mainLayout->addWidget(titleLabel);

    btnCSV = new QPushButton("CSV file", this);
    btnCSV->setMinimumHeight(40);

    btnHTML = new QPushButton("HTML file", this);
    btnHTML->setMinimumHeight(40);

    mainLayout->addWidget(btnCSV);
    mainLayout->addWidget(btnHTML);

    this->setWindowTitle("Pet Shelter - File selection");
    this->resize(300, 200);
}

void FileGUI::connectSignalsAndSlots() {
    connect(btnCSV, &QPushButton::clicked, this, &FileGUI::openCSV);
    connect(btnHTML, &QPushButton::clicked, this, &FileGUI::openHTML);
}

void FileGUI::openCSV() {
    auto* csv_list = new CSVAdoptionList("adoption_list.csv" ,this->adoptionList->get_pets());
    try {
        csv_list->save_to_file();
        csv_list->open_file();    
    } catch(const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
    this->hide();
}

void FileGUI::openHTML() {
    auto* html_list = new HTMLAdoptionList("adoption_list.html" ,this->adoptionList->get_pets());
    try {
        html_list->save_to_file();
        html_list->open_file();
    } catch(const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
    this->hide();
}