#include "ToDoWindow.h"
#include "SettingsWindow.h"
#include "AppSettings.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QColorDialog>

// construct the application's main window
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // set the central widget for the main window
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // create a scroll area
    scrollArea = new QScrollArea(centralWidget);
    scrollArea->setWidgetResizable(true);

    // create a widget to hold the contents of the scroll area
    QWidget *scrollAreaWidgetContents = new QWidget(scrollArea);
    scrollArea->setWidget(scrollAreaWidgetContents);

    // create a layout for the scroll area contents
    layout = new QVBoxLayout(scrollAreaWidgetContents);

    // generate an initial to-do section
    addTodoSection();

    // set the layout for the central widget
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(scrollArea);

    // button to add a todo
    QPushButton *addButton = new QPushButton("New To-do", this);
    mainLayout->addWidget(addButton);

    // add button wiring
    connect(addButton, &QPushButton::clicked, this,
        [=]() {
            if (todoSectionCount >= AppSettings::todoSectionsMax) return;
            addTodoSection();
        });

    // initial window size (resizable)
    resize(AppSettings::windowWidth, AppSettings::windowHeight);
}

MainWindow::~MainWindow(){}
void MainWindow::addTodoSection()
{
    if (todoSectionCount >= AppSettings::todoSectionsMax) return;

    QWidget *sectionWidget = new QWidget(scrollArea);
    QVBoxLayout *sectionLayout = new QVBoxLayout(sectionWidget);
    QHBoxLayout *topRowLayout = new QHBoxLayout();

    // complete button
    QPushButton *completeButton = new QPushButton(sectionWidget);
    completeButton->setFixedWidth(40);
    completeButton->setFlat(true);
    completeButton->setIconSize(completeButton->size());
    completeButton->setIcon(QIcon(":/assets/complete-button1.png"));
    completeButton->setToolTip("Mark this to-do complete");
    topRowLayout->addWidget(completeButton, 1);

    // title line
    QLineEdit *newLineEdit = new QLineEdit(sectionWidget);
    newLineEdit->setPlaceholderText(QString("To-do Title").arg(todoSectionCount));
    newLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    topRowLayout->addWidget(newLineEdit, 4);

    // settings button
    QPushButton *settingsButton = new QPushButton(sectionWidget);
    settingsButton->setFixedWidth(40);
    settingsButton->setFlat(true);
    settingsButton->setIconSize(settingsButton->size());
    settingsButton->setIcon(QIcon(":/assets/setting-button1.png"));
    settingsButton->setToolTip("Settings for this section");
    topRowLayout->addWidget(settingsButton, 1);

    // delete button
    QPushButton *deleteButton = new QPushButton(sectionWidget);
    deleteButton->setFixedWidth(40);
    deleteButton->setFlat(true);
    deleteButton->setIconSize(deleteButton->size());
    deleteButton->setIcon(QIcon(":/assets/delete-button1.png"));
    deleteButton->setToolTip("Delete this section");
    topRowLayout->addWidget(deleteButton, 1);

    // add top row and text edit to section layout
    sectionLayout->addLayout(topRowLayout);

    // to-do text box
    QTextEdit *todoTextArea = new QTextEdit(sectionWidget);
    todoTextArea->setPlaceholderText("What are you looking to do today?");
    todoTextArea->setMinimumHeight(AppSettings::todoTextBoxMinSize);
    sectionLayout->addWidget(todoTextArea);

    // add full section to main scroll area layout
    layout->addWidget(sectionWidget);
    todoSectionCount++;

    // complete button wiring
    connect(completeButton, &QPushButton::clicked, this,
            [=]() {
                MainWindow::completeSection(todoTextArea);
            });

    // settings button wiring
    connect(settingsButton, &QPushButton::clicked, this,
            [=]() {
                SettingsWindow::applySettingsToSection(sectionWidget, this);
            });

    // delete button wiring
    connect(deleteButton, &QPushButton::clicked, this,
        [=]() {
            deleteSection(sectionWidget);
        });
}

void MainWindow::deleteSection(QWidget *sectionWidget)
{
    layout->removeWidget(sectionWidget);
    sectionWidget->deleteLater();
    todoSectionCount--;
}

void MainWindow::completeSection(QTextEdit* textEdit)
{
    static bool imageShown = false;

    if (imageShown)
    {
        // reset the background to default (remove the image)
        textEdit->setStyleSheet("");
        // make the todo text section editable again
        textEdit->setReadOnly(false);
    }
    else
    {
        // apply the background image with opacity (semi-transparent)
        textEdit->setStyleSheet(R"(
            QTextEdit
            {
                border-image: url(:/assets/complete_backing1.png) 0 0 0 0 stretch stretch;
            }
        )");

        // set QTextEdit to read-only when the overlay is shown
        textEdit->setReadOnly(true);
    }
    // toggle the completed background image visibility
    imageShown = !imageShown;
}
