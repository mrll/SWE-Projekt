/********************************************************************************
** Form generated from reading UI file 'LasercutterJj9320.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LASERCUTTERJJ9320_H
#define LASERCUTTERJJ9320_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *codeTab;
    QGridLayout *gridLayout_3;
    QPushButton *openButton;
    QLabel *label1;
    QLabel *label2;
    QPushButton *saveButton;
    QLabel *label3;
    QRadioButton *relativeRadioButton;
    QRadioButton *absoluteRadioButton;
    QLabel *label4;
    QPlainTextEdit *codeLog;
    QTextEdit *codeEdit;
    QWidget *simTab;
    QGridLayout *gridLayout;
    QGroupBox *autoGroupBox;
    QGridLayout *gridLayout_4;
    QPushButton *runCodeButton;
    QLabel *cmdCountLabel;
    QLabel *codeSizeLabel;
    QLabel *label5;
    QLabel *label6;
    QLabel *codeLogLabel;
    QGroupBox *statusGroupBox;
    QGridLayout *gridLayout_5;
    QLabel *commandLineLabel;
    QLabel *label9;
    QLabel *label8;
    QLabel *laserMoveStateLabel;
    QLabel *label7;
    QLabel *commandLabel;
    QLabel *laserPosYLabel;
    QLabel *laserPosXLabel;
    QLabel *laserOnStateLabel;
    QSpacerItem *verticalSpacer;
    QGroupBox *manualGroupBox;
    QVBoxLayout *verticalLayout;
    QLineEdit *manualPositionYInput;
    QLineEdit *manualPositionXInput;
    QPushButton *manualLaserMoveButton;
    QPushButton *manualLaserStateButton;
    QGraphicsView *simGView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 650);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 650));
        MainWindow->setDocumentMode(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        codeTab = new QWidget();
        codeTab->setObjectName(QString::fromUtf8("codeTab"));
        gridLayout_3 = new QGridLayout(codeTab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        openButton = new QPushButton(codeTab);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setMaximumSize(QSize(320, 16777215));

        gridLayout_3->addWidget(openButton, 1, 2, 1, 2);

        label1 = new QLabel(codeTab);
        label1->setObjectName(QString::fromUtf8("label1"));

        gridLayout_3->addWidget(label1, 0, 0, 1, 1);

        label2 = new QLabel(codeTab);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setMaximumSize(QSize(320, 16777215));

        gridLayout_3->addWidget(label2, 0, 2, 1, 2);

        saveButton = new QPushButton(codeTab);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(saveButton->sizePolicy().hasHeightForWidth());
        saveButton->setSizePolicy(sizePolicy2);
        saveButton->setMaximumSize(QSize(320, 16777215));

        gridLayout_3->addWidget(saveButton, 2, 2, 1, 2);

        label3 = new QLabel(codeTab);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setMaximumSize(QSize(320, 16777215));

        gridLayout_3->addWidget(label3, 3, 2, 1, 2);

        relativeRadioButton = new QRadioButton(codeTab);
        relativeRadioButton->setObjectName(QString::fromUtf8("relativeRadioButton"));
        relativeRadioButton->setMaximumSize(QSize(155, 16777215));
        relativeRadioButton->setChecked(false);

        gridLayout_3->addWidget(relativeRadioButton, 4, 2, 1, 1);

        absoluteRadioButton = new QRadioButton(codeTab);
        absoluteRadioButton->setObjectName(QString::fromUtf8("absoluteRadioButton"));
        absoluteRadioButton->setMaximumSize(QSize(155, 16777215));
        absoluteRadioButton->setChecked(true);

        gridLayout_3->addWidget(absoluteRadioButton, 4, 3, 1, 1);

        label4 = new QLabel(codeTab);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setMaximumSize(QSize(320, 16777215));

        gridLayout_3->addWidget(label4, 5, 2, 1, 2);

        codeLog = new QPlainTextEdit(codeTab);
        codeLog->setObjectName(QString::fromUtf8("codeLog"));
        sizePolicy1.setHeightForWidth(codeLog->sizePolicy().hasHeightForWidth());
        codeLog->setSizePolicy(sizePolicy1);
        codeLog->setMinimumSize(QSize(320, 0));
        codeLog->setMaximumSize(QSize(320, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier"));
        codeLog->setFont(font);
        codeLog->setReadOnly(true);

        gridLayout_3->addWidget(codeLog, 6, 2, 1, 2);

        codeEdit = new QTextEdit(codeTab);
        codeEdit->setObjectName(QString::fromUtf8("codeEdit"));
        sizePolicy1.setHeightForWidth(codeEdit->sizePolicy().hasHeightForWidth());
        codeEdit->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Courier"));
        font1.setPointSize(14);
        codeEdit->setFont(font1);
        codeEdit->setLineWrapMode(QTextEdit::WidgetWidth);

        gridLayout_3->addWidget(codeEdit, 1, 0, 6, 2);

        tabWidget->addTab(codeTab, QString());
        simTab = new QWidget();
        simTab->setObjectName(QString::fromUtf8("simTab"));
        gridLayout = new QGridLayout(simTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        autoGroupBox = new QGroupBox(simTab);
        autoGroupBox->setObjectName(QString::fromUtf8("autoGroupBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(autoGroupBox->sizePolicy().hasHeightForWidth());
        autoGroupBox->setSizePolicy(sizePolicy3);
        autoGroupBox->setMinimumSize(QSize(240, 0));
        gridLayout_4 = new QGridLayout(autoGroupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        runCodeButton = new QPushButton(autoGroupBox);
        runCodeButton->setObjectName(QString::fromUtf8("runCodeButton"));
        sizePolicy2.setHeightForWidth(runCodeButton->sizePolicy().hasHeightForWidth());
        runCodeButton->setSizePolicy(sizePolicy2);
        runCodeButton->setMinimumSize(QSize(200, 0));

        gridLayout_4->addWidget(runCodeButton, 4, 0, 1, 2);

        cmdCountLabel = new QLabel(autoGroupBox);
        cmdCountLabel->setObjectName(QString::fromUtf8("cmdCountLabel"));
        cmdCountLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(cmdCountLabel, 2, 1, 1, 1);

        codeSizeLabel = new QLabel(autoGroupBox);
        codeSizeLabel->setObjectName(QString::fromUtf8("codeSizeLabel"));
        codeSizeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(codeSizeLabel, 3, 1, 1, 1);

        label5 = new QLabel(autoGroupBox);
        label5->setObjectName(QString::fromUtf8("label5"));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        label5->setFont(font2);

        gridLayout_4->addWidget(label5, 3, 0, 1, 1);

        label6 = new QLabel(autoGroupBox);
        label6->setObjectName(QString::fromUtf8("label6"));
        label6->setFont(font2);

        gridLayout_4->addWidget(label6, 2, 0, 1, 1);

        codeLogLabel = new QLabel(autoGroupBox);
        codeLogLabel->setObjectName(QString::fromUtf8("codeLogLabel"));
        codeLogLabel->setFont(font2);

        gridLayout_4->addWidget(codeLogLabel, 1, 0, 1, 1);


        gridLayout->addWidget(autoGroupBox, 4, 1, 1, 2);

        statusGroupBox = new QGroupBox(simTab);
        statusGroupBox->setObjectName(QString::fromUtf8("statusGroupBox"));
        sizePolicy3.setHeightForWidth(statusGroupBox->sizePolicy().hasHeightForWidth());
        statusGroupBox->setSizePolicy(sizePolicy3);
        statusGroupBox->setMinimumSize(QSize(240, 0));
        gridLayout_5 = new QGridLayout(statusGroupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        commandLineLabel = new QLabel(statusGroupBox);
        commandLineLabel->setObjectName(QString::fromUtf8("commandLineLabel"));

        gridLayout_5->addWidget(commandLineLabel, 5, 0, 1, 1);

        label9 = new QLabel(statusGroupBox);
        label9->setObjectName(QString::fromUtf8("label9"));
        label9->setFont(font2);

        gridLayout_5->addWidget(label9, 4, 0, 1, 1);

        label8 = new QLabel(statusGroupBox);
        label8->setObjectName(QString::fromUtf8("label8"));
        label8->setFont(font2);

        gridLayout_5->addWidget(label8, 2, 0, 1, 1);

        laserMoveStateLabel = new QLabel(statusGroupBox);
        laserMoveStateLabel->setObjectName(QString::fromUtf8("laserMoveStateLabel"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(laserMoveStateLabel->sizePolicy().hasHeightForWidth());
        laserMoveStateLabel->setSizePolicy(sizePolicy4);
        laserMoveStateLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(laserMoveStateLabel, 1, 1, 1, 1);

        label7 = new QLabel(statusGroupBox);
        label7->setObjectName(QString::fromUtf8("label7"));
        label7->setFont(font2);

        gridLayout_5->addWidget(label7, 0, 0, 1, 1);

        commandLabel = new QLabel(statusGroupBox);
        commandLabel->setObjectName(QString::fromUtf8("commandLabel"));
        commandLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(commandLabel, 5, 1, 1, 1);

        laserPosYLabel = new QLabel(statusGroupBox);
        laserPosYLabel->setObjectName(QString::fromUtf8("laserPosYLabel"));
        laserPosYLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(laserPosYLabel, 3, 1, 1, 1);

        laserPosXLabel = new QLabel(statusGroupBox);
        laserPosXLabel->setObjectName(QString::fromUtf8("laserPosXLabel"));
        laserPosXLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(laserPosXLabel, 3, 0, 1, 1);

        laserOnStateLabel = new QLabel(statusGroupBox);
        laserOnStateLabel->setObjectName(QString::fromUtf8("laserOnStateLabel"));
        sizePolicy4.setHeightForWidth(laserOnStateLabel->sizePolicy().hasHeightForWidth());
        laserOnStateLabel->setSizePolicy(sizePolicy4);
        laserOnStateLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(laserOnStateLabel, 1, 0, 1, 1);


        gridLayout->addWidget(statusGroupBox, 3, 1, 1, 2);

        verticalSpacer = new QSpacerItem(23, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 2, 1, 1);

        manualGroupBox = new QGroupBox(simTab);
        manualGroupBox->setObjectName(QString::fromUtf8("manualGroupBox"));
        sizePolicy3.setHeightForWidth(manualGroupBox->sizePolicy().hasHeightForWidth());
        manualGroupBox->setSizePolicy(sizePolicy3);
        manualGroupBox->setMinimumSize(QSize(240, 0));
        verticalLayout = new QVBoxLayout(manualGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        manualPositionYInput = new QLineEdit(manualGroupBox);
        manualPositionYInput->setObjectName(QString::fromUtf8("manualPositionYInput"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(manualPositionYInput->sizePolicy().hasHeightForWidth());
        manualPositionYInput->setSizePolicy(sizePolicy5);
        manualPositionYInput->setMinimumSize(QSize(160, 0));

        verticalLayout->addWidget(manualPositionYInput);

        manualPositionXInput = new QLineEdit(manualGroupBox);
        manualPositionXInput->setObjectName(QString::fromUtf8("manualPositionXInput"));
        sizePolicy5.setHeightForWidth(manualPositionXInput->sizePolicy().hasHeightForWidth());
        manualPositionXInput->setSizePolicy(sizePolicy5);
        manualPositionXInput->setMinimumSize(QSize(160, 0));
        manualPositionXInput->setCursorPosition(4);

        verticalLayout->addWidget(manualPositionXInput);

        manualLaserMoveButton = new QPushButton(manualGroupBox);
        manualLaserMoveButton->setObjectName(QString::fromUtf8("manualLaserMoveButton"));

        verticalLayout->addWidget(manualLaserMoveButton);

        manualLaserStateButton = new QPushButton(manualGroupBox);
        manualLaserStateButton->setObjectName(QString::fromUtf8("manualLaserStateButton"));

        verticalLayout->addWidget(manualLaserStateButton);


        gridLayout->addWidget(manualGroupBox, 5, 1, 1, 2);

        simGView = new QGraphicsView(simTab);
        simGView->setObjectName(QString::fromUtf8("simGView"));

        gridLayout->addWidget(simGView, 2, 0, 5, 1);

        tabWidget->addTab(simTab, QString());

        verticalLayout_2->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        QWidget::setTabOrder(openButton, saveButton);
        QWidget::setTabOrder(saveButton, relativeRadioButton);
        QWidget::setTabOrder(relativeRadioButton, absoluteRadioButton);
        QWidget::setTabOrder(absoluteRadioButton, codeLog);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Lasercutter", 0, QApplication::UnicodeUTF8));
        openButton->setText(QApplication::translate("MainWindow", "\303\226ffnen", 0, QApplication::UnicodeUTF8));
        label1->setText(QApplication::translate("MainWindow", "Steuercode:", 0, QApplication::UnicodeUTF8));
        label2->setText(QApplication::translate("MainWindow", "Datei:", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("MainWindow", "Speichern", 0, QApplication::UnicodeUTF8));
        label3->setText(QApplication::translate("MainWindow", "Wertangaben:", 0, QApplication::UnicodeUTF8));
        relativeRadioButton->setText(QApplication::translate("MainWindow", "Relativ", 0, QApplication::UnicodeUTF8));
        absoluteRadioButton->setText(QApplication::translate("MainWindow", "Absolut", 0, QApplication::UnicodeUTF8));
        label4->setText(QApplication::translate("MainWindow", "Fehlermeldungen:", 0, QApplication::UnicodeUTF8));
        codeLog->setPlainText(QApplication::translate("MainWindow", "Keine Fehler.\n"
                "Code in Ordnung.\n"
                "----------------\n"
                "", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(codeTab), QApplication::translate("MainWindow", "Steuercode", 0, QApplication::UnicodeUTF8));
        autoGroupBox->setTitle(QApplication::translate("MainWindow", "Automatik", 0, QApplication::UnicodeUTF8));
        runCodeButton->setText(QApplication::translate("MainWindow", "Steuercode fahren", 0, QApplication::UnicodeUTF8));
        cmdCountLabel->setText(QApplication::translate("MainWindow", "19", 0, QApplication::UnicodeUTF8));
        codeSizeLabel->setText(QApplication::translate("MainWindow", "300 x 500", 0, QApplication::UnicodeUTF8));
        label5->setText(QApplication::translate("MainWindow", "Gr\303\266\303\237e:", 0, QApplication::UnicodeUTF8));
        label6->setText(QApplication::translate("MainWindow", "Anzahl Befehle:", 0, QApplication::UnicodeUTF8));
        codeLogLabel->setText(QApplication::translate("MainWindow", "Steuercode OK!", 0, QApplication::UnicodeUTF8));
        statusGroupBox->setTitle(QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        commandLineLabel->setText(QApplication::translate("MainWindow", "Line 7:", 0, QApplication::UnicodeUTF8));
        label9->setText(QApplication::translate("MainWindow", "Aktueller Befehl:", 0, QApplication::UnicodeUTF8));
        label8->setText(QApplication::translate("MainWindow", "Laserposition:", 0, QApplication::UnicodeUTF8));
        laserMoveStateLabel->setText(QApplication::translate("MainWindow", "Stand", 0, QApplication::UnicodeUTF8));
        label7->setText(QApplication::translate("MainWindow", "Laserstatus:", 0, QApplication::UnicodeUTF8));
        commandLabel->setText(QApplication::translate("MainWindow", "MOVE 150, 100", 0, QApplication::UnicodeUTF8));
        laserPosYLabel->setText(QApplication::translate("MainWindow", "500", 0, QApplication::UnicodeUTF8));
        laserPosXLabel->setText(QApplication::translate("MainWindow", "300", 0, QApplication::UnicodeUTF8));
        laserOnStateLabel->setText(QApplication::translate("MainWindow", "Aus", 0, QApplication::UnicodeUTF8));
        manualGroupBox->setTitle(QApplication::translate("MainWindow", "Manuell", 0, QApplication::UnicodeUTF8));
        manualPositionYInput->setInputMask(QApplication::translate("MainWindow", "9999; ", 0, QApplication::UnicodeUTF8));
        manualPositionYInput->setText(QApplication::translate("MainWindow", "100", 0, QApplication::UnicodeUTF8));
        manualPositionYInput->setPlaceholderText(QApplication::translate("MainWindow", "Y Koordinate", 0, QApplication::UnicodeUTF8));
        manualPositionXInput->setInputMask(QApplication::translate("MainWindow", "9999; ", 0, QApplication::UnicodeUTF8));
        manualPositionXInput->setText(QApplication::translate("MainWindow", "100", 0, QApplication::UnicodeUTF8));
        manualPositionXInput->setPlaceholderText(QApplication::translate("MainWindow", "X Koordinate", 0, QApplication::UnicodeUTF8));
        manualLaserMoveButton->setText(QApplication::translate("MainWindow", "Manuell fahren", 0, QApplication::UnicodeUTF8));
        manualLaserStateButton->setText(QApplication::translate("MainWindow", "Laser an/aus", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(simTab), QApplication::translate("MainWindow", "Lasersteuerung", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LASERCUTTERJJ9320_H
