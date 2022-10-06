/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QFormLayout *formLayout_2;
    QSpinBox *puz_num;
    QLabel *label_2;
    QSpinBox *puz_height;
    QLabel *label_4;
    QSpinBox *puz_width;
    QLabel *label;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(240, 320);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 4, 0, 1, 1);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_2->setHorizontalSpacing(3);
        puz_num = new QSpinBox(Dialog);
        puz_num->setObjectName(QString::fromUtf8("puz_num"));
        puz_num->setMinimum(5);
        puz_num->setMaximum(99999);
        puz_num->setSingleStep(100);
        puz_num->setValue(50);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, puz_num);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        puz_height = new QSpinBox(Dialog);
        puz_height->setObjectName(QString::fromUtf8("puz_height"));
        puz_height->setMinimum(5);
        puz_height->setMaximum(50);
        puz_height->setSingleStep(5);
        puz_height->setValue(10);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, puz_height);

        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_4);

        puz_width = new QSpinBox(Dialog);
        puz_width->setObjectName(QString::fromUtf8("puz_width"));
        puz_width->setMinimum(5);
        puz_width->setMaximum(50);
        puz_width->setSingleStep(5);
        puz_width->setValue(10);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, puz_width);

        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);


        gridLayout->addLayout(formLayout_2, 0, 0, 1, 1);

#if QT_CONFIG(shortcut)
        label_2->setBuddy(puz_height);
        label_4->setBuddy(puz_width);
        label->setBuddy(puz_num);
#endif // QT_CONFIG(shortcut)

        retranslateUi(Dialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Dialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Dialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "Width", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "Height", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Puzzle Number", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
