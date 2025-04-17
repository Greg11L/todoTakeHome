#ifndef TODOWINDOW_H
#define TODOWINDOW_H

#include <QMainWindow>
#include <QWidget>

class QScrollArea;
class QLineEdit;
class QVBoxLayout;
class QLineEdit;
class QTextEdit;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralWidget;     // Central widget of the main window
    QScrollArea *scrollArea;    // Scroll area widget for scrolling todos
    QVBoxLayout *layout;        // Layout for scroll area contents
    QLineEdit *lineEdit;        // Line edit widget for title
    QTextEdit *textEdit;        // to-do text edit
    QPushButton *addButton;    // Buttton to create a new to-do

    // start with one blank to-do baseline
    int todoSectionCount = 0;

    void addTodoSection();
    void deleteSection(QWidget*);
    void completeSection(QTextEdit*);
};

#endif // TODOWINDOW_H
