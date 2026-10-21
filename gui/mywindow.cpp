#include "mywindow.h"
#include "services.h"
#include <QHeaderView>

AdoptionWindow::AdoptionWindow(std::vector<Pet> pets,QWidget *parent) : QDialog(parent) {
    setWindowTitle("Adoption Registry");
    resize(750, 400);

    QVBoxLayout *layout = new QVBoxLayout(this);
    m_tableView = new QTableView(this);


    m_model = new MyModel(this);
    m_model->setPets(pets);
    m_tableView->setModel(m_model);

    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setAlternatingRowColors(true);


    layout->addWidget(m_tableView);
}

