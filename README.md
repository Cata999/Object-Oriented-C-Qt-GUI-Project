# 🐾 Keep Calm and Adopt a Pet — Shelter Management System

An Object-Oriented C++ desktop application built with **Qt 6**, designed to manage an animal shelter database and facilitate pet adoptions. The application features dual user roles (Administrator and User), multi-level Undo/Redo functionality via the Command Pattern, dynamic CSV/HTML exporting, and a Qt Model/View table representation.

---

## 📋 Table of Contents
- [Overview](#-overview)
- [Key Features](#-key-features)
  - [Administrator Mode](#administrator-mode)
  - [User (Adopter) Mode](#user-adopter-mode)
- [Software Architecture](#%EF%B8%8F-software-architecture)
- [Concepts & Design Patterns Used](#-concepts--design-patterns-used)
- [Project Structure](#-project-structure)
- [Build and Run](#%EF%B8%8F-build-and-run)

---

## 🌟 Overview

The **"Keep Calm and Adopt a Pet"** shelter application provides a clean, user-friendly graphical interface to manage dogs available for adoption.

The system supports two distinct modes accessible from the startup launcher:
1. **Administrator Mode:** Allows shelter personnel to maintain the pet catalog (add, remove, update dogs), inspect current listings, and safely undo/redo database modifications.
2. **User Mode:** Allows prospective adopters to cycle through available dogs, filter by breed and age, preview photos, adopt pets into a personal list, export the adoption list to CSV/HTML, and inspect adoption records in a custom Qt Table Model.

---

## 🚀 Key Features

### Administrator Mode
- **CRUD Operations:** Add new dogs, remove adopted dogs, and update existing records (Breed, Name, Age, Photo URL).
- **Synchronized Form:** Selecting an item in the pet list automatically populates the editing form.
- **Multi-Level Undo & Redo:**
  - Implemented using the **Command Pattern** with polymorphic action objects.
  - Interactive **Undo** and **Redo** GUI buttons.
  - Global keyboard shortcuts: `Ctrl+Z` (Undo) and `Ctrl+Y` (Redo).
- **Data Validation & Error Handling:** Validates capitalized names/breeds, age boundaries, and valid photo links before applying mutations.

### User (Adopter) Mode
- **Interactive Carousel Browsing:** Cycle through shelter dogs one at a time with automatic photo link preview; infinitely loops back to the beginning.
- **Custom Filtering:** Filter dogs matching a specific breed and minimum age.
- **Adoption Cart:** Adopt dogs directly into a personal adoption list.
- **Dual Export Formats (Polymorphic Exporters):**
  - **CSV:** Formatted comma-separated values file opened via the default system viewer.
  - **HTML:** Formatted HTML table with hyperlinked photo links opened directly in the default web browser.
- **Qt Model/View Table View:** An independent window displaying the adoption registry using `QTableView` backed by a custom `QAbstractTableModel`.

---

## 🏛️ Software Architecture

The project strictly adheres to a **Layered Architecture (Separation of Concerns)**:

```mermaid
flowchart TD
    subgraph UI ["Presentation Layer (Qt6 GUI)"]
        StartupGUI["StartupGUI (Launcher)"]
        GUI["Admin GUI"]
        UserGUI["UserGUI"]
        AdoptionWindow["AdoptionWindow (QTableView)"]
        FileGUI["FileGUI (Export Dialog)"]
        MyModel["MyModel (QAbstractTableModel)"]
    end

    subgraph ServiceLayer ["Service / Controller Layer"]
        Services["Services"]
        UndoRedoAction["UndoRedoAction (Abstract Command)"]
        UndoRedoAdd["UndoRedoAdd"]
        UndoRedoRemove["UndoRedoRemove"]
        UndoRedoUpdate["UndoRedoUpdate"]
    end

    subgraph RepoLayer ["Repository / Persistence Layer"]
        Repo["Repository&lt;Pet&gt; (Template)"]
        FileAdoptionList["FileAdoptionList (Abstract)"]
        CSVAdoptionList["CSVAdoptionList"]
        HTMLAdoptionList["HTMLAdoptionList"]
    end

    subgraph DomainLayer ["Domain Layer"]
        Pet["Pet Entity"]
        PetValidator["PetValidator"]
        Exceptions["Custom Exceptions"]
    end

    StartupGUI --> GUI
    StartupGUI --> UserGUI
    UserGUI --> AdoptionWindow
    UserGUI --> FileGUI
    AdoptionWindow --> MyModel

    GUI --> Services
    UserGUI --> Services
    Services --> Repo
    Services --> UndoRedoAction
    UndoRedoAction <|-- UndoRedoAdd
    UndoRedoAction <|-- UndoRedoRemove
    UndoRedoAction <|-- UndoRedoUpdate

    Repo --> Pet
    FileAdoptionList <|-- CSVAdoptionList
    FileAdoptionList <|-- HTMLAdoptionList
    FileAdoptionList --> Pet
    Services --> Exceptions
    Repo --> Exceptions
```

---

## 💡 Concepts & Design Patterns Used

### 1. Object-Oriented Programming (OOP) Pillars
- **Encapsulation:** Class `Pet` bundles state and behaviors together, exposing controlled getters/setters and operators while hiding representation details.
- **Inheritance & Polymorphism:**
  - Base class `UndoRedoAction` with pure virtual methods `executeUndo()` and `executeRedo()`.
  - Base class `FileAdoptionList` defining pure virtual `save_to_file()` and `open_file()`, derived into `CSVAdoptionList` and `HTMLAdoptionList`.
  - Proper virtual destructor cleanup across polymorphic hierarchies.

### 2. Design Patterns
- **Command Pattern:** Each administrative mutation is encapsulated as a heap-allocated command object (`UndoRedoAdd`, `UndoRedoRemove`, `UndoRedoUpdate`) pushed onto an undo stack.
- **Model-View Architecture (Qt):** Decoupling data representation from presentation by inheriting `QAbstractTableModel` in `MyModel` and rendering it through `QTableView`.
- **Strategy Pattern:** Interchangeable file export behaviors (CSV vs. HTML) accessed through an abstract base pointer (`FileAdoptionList*`).

### 3. Modern C++ (C++14) & Memory Safety
- **Smart Pointers & RAII:** `std::vector<std::unique_ptr<UndoRedoAction>>` manages dynamic lifetime of commands with automatic memory reclamation.
- **Move Semantics:** Utilizes `std::move` for efficient transfers of command ownership between stacks without copying.
- **Templates / Generic Programming:** `Repository<T>` is generic and can persist and manage arbitrary domain types.
- **STL Algorithms:** Expressive use of `std::find`, `std::copy_if`, and lambdas for searching and filtering collections.

### 4. Exception Handling & Robustness
- Custom exception hierarchy derived from `std::runtime_error` (`RepositoryException`, `FileException`, `UpdateException`, `ValidationException`).
- Startup exception barrier in `main.cpp` catching fatal errors and displaying clear feedback via `QMessageBox::critical`.

---

## 📂 Project Structure

```text
├── domain/               # Domain entity (Pet)
│   ├── domain.h
│   └── domain.cpp
├── repository/           # Generic Repository & File Exporters (CSV, HTML)
│   ├── repository.h
│   └── repository.cpp
├── services/             # Business logic & Undo/Redo Command implementation
│   ├── services.h
│   ├── services.cpp
│   └── undo_action.h
├── Exceptions/           # Custom exception classes and domain validator
│   ├── exceptions.h
│   └── exceptions.cpp
├── gui/                  # Qt6 GUI Windows & Custom Table Model
│   ├── select_gui.h/cpp  # Startup mode selection launcher
│   ├── gui.h/cpp         # Administrator window
│   ├── user_gui.h/cpp    # User/Adopter window
│   ├── file_gui.h/cpp    # File export selection dialog
│   ├── mymodel.h/cpp     # QAbstractTableModel implementation
│   └── mywindow.h/cpp    # QTableView adoption list window
├── pets.txt              # Persistent storage file for shelter pets
├── adoption_list.csv     # Exported CSV adoption list
├── CMakeLists.txt        # CMake build configuration
└── main.cpp              # Application entry point
```

---

## 🛠️ Build and Run

### Prerequisites
- **C++14** compatible compiler (GCC, Clang, or MSVC)
- **CMake** 3.16 or higher
- **Qt 6** (Widgets component)

### Build Instructions
```bash
# Clone the repository
git clone https://github.com/Cata999/Object-Oriented-C-Qt-GUI-Project.git
cd Object-Oriented-C-Qt-GUI-Project

# Generate build files
cmake -B build -S .

# Build executable
cmake --build build --config Release
```

Ensure `pets.txt` is located in the working directory alongside the generated executable.
