#pragma once
#ifndef A10_MYWINDOW_H
#define A10_MYWINDOW_H

#include <QDialog>
#include <QTableView>
#include <QVBoxLayout>
#include "mymodel.h"

class AdoptionWindow : public QDialog {
    Q_OBJECT

public:
    explicit AdoptionWindow(std::vector<Pet> pets,QWidget *parent = nullptr);

private:
    QTableView *m_tableView;
    MyModel *m_model;

};
#endif //A10_MYWINDOW_H