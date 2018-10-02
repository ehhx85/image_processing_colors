#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// --- Header Definitions ---
#include <cstdlib>
#include <iostream>
#include <math.h>

#include <QMainWindow>

#include <QAction>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QLCDNumber>
#include <QList>
#include <QSlider>
#include <QString>
#include <QTimer>

#include "myimage.h"

// --- Main Window Class ---
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // --- File Menu Slots ---
    void openDefault();
    void open();
    void reset();
    void save();
    void saveAs();
    void close();
    void quit();

    // --- Help Menu Slots ---
    void about();
    void aboutQt();
    void aboutAuthor();

    // --- Status Bar Slots ---
    void menuStatus(QString menuString,
                    QString subMenuString);
    void appendStatus(QString newString);
    void colorStatus();

    // --- Graphics Slots ---
    void updateInput();
    void updateOutput();

    void updateRedColor();
    void updateGreenColor();
    void updateBlueColor();
    void updateHSVColor();

    // --- Color Map Slots ---
    void updateRGBSliders();
    void updateHSISliders();

    void updateRedValue();
    void updateGreenValue();
    void updateBlueValue();
    void updateHueValue();
    void updateSaturationValue();
    void updateIntensityValue();


private:
    // --- Main Window ---
    Ui::MainWindow *ui;

    // --- Directories ---
    QDir defaultDirectory;

    // --- Menus ---
    QMenu *fileMenu;
    QMenu *helpMenu;

    // --- Actions ---
    QAction *openDefaultAction;
    QAction *openAction;
    QAction *resetAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *closeAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *aboutAuthorAction;

    // --- Graphics ---
    QGraphicsPixmapItem *item;

    QGraphicsScene *inputScene;
    QGraphicsScene *outputScene;

    // --- Images ---
    QList<QString> imageFileList;

    MyImage inputImage;
    MyImage outputImage;

    // --- Build Methods ---
    void buildComboBoxes();
    void buildDirectories();
    void buildGraphics();
    void buildLCDs();
    void buildMenu();
    void buildResources();
    void buildSliderBars();

};

#endif // MAINWINDOW_H
