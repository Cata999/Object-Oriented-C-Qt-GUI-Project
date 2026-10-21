#include "mymodel.h"

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int MyModel::rowCount(const QModelIndex & parent) const
{
    if (parent.isValid()) return 0;
    return static_cast<int>(m_pets.size());
}

int MyModel::columnCount(const QModelIndex & parent) const
{
    if (parent.isValid()) return 0;
    return 4; // Breed, Name, Age, Photo Link
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= static_cast<int>(m_pets.size()))
        return QVariant();

    const Pet& pet = m_pets.at(index.row());

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:
                return QString::fromStdString(pet.get_breed());
            case 1:
                return QString::fromStdString(pet.get_name());
            case 2:
                return pet.get_age();
            case 3:
                return QString::fromStdString(pet.get_photo());
        }
    }
    return QVariant();
}

void MyModel::setPets(const std::vector<Pet>& pets) {
    beginResetModel();
    m_pets = pets;
    endResetModel();
}
QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return QString("Breed");
            case 1: return QString("Name");
            case 2: return QString("Age");
            case 3: return QString("Photo Link / URL");
        }
    }
    return QVariant();
}