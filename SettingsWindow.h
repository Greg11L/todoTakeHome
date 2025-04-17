#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QColor>
#include <QCheckBox>

class QColorDialog;
class QPushButton;

class SettingsWindow : public QDialog {
    Q_OBJECT

public:
    SettingsWindow(QWidget *parent = nullptr);
    QColor selectedColor() const;
    bool invertText() const;
    static void applySettingsToSection(QWidget *sectionWidget, QWidget *parent = nullptr);

private:
    QColor currentColor;             // color of a todo
    QCheckBox *invertTextCheckBox;   // invert text color check box
    QPushButton *chooseColorButton;  // choose color button in settings window
};

#endif // SETTINGSWINDOW_H
