#include <QApplication>
#include "ToDoWindow.h"

// main function to launch the app
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
