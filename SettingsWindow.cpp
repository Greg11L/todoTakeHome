#include "SettingsWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QDialogButtonBox>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // color selector
    chooseColorButton = new QPushButton("Set To-do window color", this);
    layout->addWidget(chooseColorButton);
    // color selection button wiring
    connect(chooseColorButton, &QPushButton::clicked, this,
        [=]() {
        QColor color = QColorDialog::getColor(currentColor, this, "Pick a Color");
        if (color.isValid())
        {
            currentColor = color;
        }
    });

    // invert text color checkbox
    invertTextCheckBox = new QCheckBox("Invert text color", this);
    layout->addWidget(invertTextCheckBox);

    // OK / Cancel buttons
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &SettingsWindow::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &SettingsWindow::reject);
}

// selected color getter
QColor SettingsWindow::selectedColor() const
{
    return currentColor;
}
// inverted text getter
bool SettingsWindow::invertText() const
{
    return invertTextCheckBox->isChecked();
}

void SettingsWindow::applySettingsToSection(QWidget *sectionWidget, QWidget *parent)
{
    SettingsWindow dialog(parent);
    if (dialog.exec() == QDialog::Accepted)
    {
        QColor color = dialog.selectedColor();
        // track if text inverted
        bool whiteText = dialog.invertText();
        QString style = QString("background-color: %1;").arg(color.name());

        if (whiteText)
        {
            style += " color: white;";
        }

        sectionWidget->setStyleSheet(style);
    }
}
