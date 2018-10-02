// ----- Headers --------------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"

// ----- Constructor / Destructor ---------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    inputImage(MyImage("Input Image")),
    outputImage(MyImage("Output Image"))
{
    ui->setupUi(this);

    // --- Build the application components ---
    buildDirectories();
    buildMenu();
    buildComboBoxes();
    buildLCDs();
    buildSliderBars();
    buildGraphics();

    /*
    // --- Test ---
    QString filePath = defaultDirectory.path() + QString("/color_bars.png");
    std::cout << "Auto loading from file: " << filePath.toStdString() << std::endl;

    inputImage.setImage(filePath);
    outputImage.setImage(filePath);

    updateInput();
    updateOutput();
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ----- Build Methods --------------------------------------------------------
void MainWindow::buildResources()
{
    imageFileList.clear();
    imageFileList.append("Astronaut");
    imageFileList.append("Color Bars (RGB)");
    imageFileList.append("Color Bars (10 Color)");
    imageFileList.append("Color Chart (Digital)");
    imageFileList.append("Color Chart (Patterned)");
    imageFileList.append("Color Chart (Photo)");
    imageFileList.append("Color Circle");
    imageFileList.append("Color Circle (false)");
    imageFileList.append("Color Disk");
    imageFileList.append("Color Names");
    imageFileList.append("Lenna");
    imageFileList.append("Strawberries");
    imageFileList.append("Venn Diagram");
    imageFileList.append("Visible Spectrum");
}

void MainWindow::buildDirectories()
{
    QString desktopPath = QDir::homePath() + QString("/Desktop");
    defaultDirectory = QDir(desktopPath);
}

void MainWindow::buildMenu()
{
    // --- New Menu Bars ---
    fileMenu = menuBar()->addMenu(tr("&File"));
    helpMenu = menuBar()->addMenu(tr("&Help"));

    // --- New Menu Actions ---
    openDefaultAction = new QAction(tr("Open &Default Image"), this);
    openAction = new QAction(tr("&Open from File"), this);
    resetAction = new QAction(tr("&Reset Image"), this);
    saveAction = new QAction(tr("&Save"), this);
    saveAsAction = new QAction(tr("Save &As..."), this);
    closeAction = new QAction(tr("&Close"), this);
    exitAction = new QAction(tr("&Exit"), this);
    aboutAction = new QAction(tr("&About This Application"), this);
    aboutQtAction = new QAction(tr("&About Qt"), this);
    aboutAuthorAction = new QAction(tr("&About Author"), this);

    // --- Set File Menu Shortcuts ---
    openDefaultAction->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_O));
    openAction->setShortcut(QKeySequence::Open);
    resetAction->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_R));
    saveAction->setShortcut(QKeySequence::Save);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    closeAction->setShortcut(QKeySequence::Close);
    exitAction->setShortcut(QKeySequence::Quit);

    // --- Connect menu actions to slots ---
    connect(openDefaultAction, SIGNAL(triggered()), this, SLOT(openDefault()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(resetAction, SIGNAL(triggered()), this, SLOT(reset()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(quit()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutAuthorAction, SIGNAL(triggered()), this, SLOT(aboutAuthor()));

    // --- Add the menu actions to the menu bar---
    fileMenu->addAction(openDefaultAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(resetAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(closeAction);
    fileMenu->addAction(exitAction);
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
    helpMenu->addAction(aboutAuthorAction);
}

void MainWindow::buildComboBoxes()
{
    buildResources();

    ui->comboBoxImageSelector->addItems(imageFileList);
    connect(ui->comboBoxImageSelector, SIGNAL(activated(int)), this, SLOT(openDefault()));
}

void MainWindow::buildSliderBars()
{
    // --- Connect the color sliders to their LCD value slot ---
    connect(ui->sliderRed, SIGNAL(valueChanged(int)), this, SLOT(updateRedValue()));
    connect(ui->sliderGreen, SIGNAL(valueChanged(int)), this, SLOT(updateGreenValue()));
    connect(ui->sliderBlue, SIGNAL(valueChanged(int)), this, SLOT(updateBlueValue()));
    connect(ui->sliderHue, SIGNAL(valueChanged(int)), this, SLOT(updateHueValue()));
    connect(ui->sliderSaturation, SIGNAL(valueChanged(int)), this, SLOT(updateSaturationValue()));
    connect(ui->sliderIntensity, SIGNAL(valueChanged(int)), this, SLOT(updateIntensityValue()));

    // --- Connect the color sliders to the color remap slots ---
    connect(ui->sliderRed, SIGNAL(sliderReleased()), this, SLOT(updateRedColor()));
    connect(ui->sliderGreen, SIGNAL(sliderReleased()), this, SLOT(updateGreenColor()));
    connect(ui->sliderBlue, SIGNAL(sliderReleased()), this, SLOT(updateBlueColor()));
    connect(ui->sliderHue, SIGNAL(sliderReleased()), this, SLOT(updateHSVColor()));
    connect(ui->sliderSaturation, SIGNAL(sliderReleased()), this, SLOT(updateHSVColor()));
    connect(ui->sliderIntensity, SIGNAL(sliderReleased()), this, SLOT(updateHSVColor()));

    // --- Set the range of the color sliders ---
    int tmpMin = 0;
    int tmpMax = 255;

    ui->sliderRed->setRange(tmpMin, tmpMax);
    ui->sliderGreen->setRange(tmpMin, tmpMax);
    ui->sliderBlue->setRange(tmpMin, tmpMax);

    ui->sliderRed->setValue(tmpMax);
    ui->sliderGreen->setValue(tmpMax);
    ui->sliderBlue->setValue(tmpMax);

    tmpMax = 100;

    ui->sliderHue->setRange(tmpMin, tmpMax);
    ui->sliderSaturation->setRange(tmpMin, tmpMax);
    ui->sliderIntensity->setRange(tmpMin, tmpMax);

    ui->sliderHue->setValue(tmpMax);
    ui->sliderSaturation->setValue(tmpMax);
    ui->sliderIntensity->setValue(tmpMax);
}

void MainWindow::buildLCDs()
{
    ui->lcdRed->setDigitCount(3);
    ui->lcdGreen->setDigitCount(3);
    ui->lcdBlue->setDigitCount(3);
    ui->lcdHue->setDigitCount(3);
    ui->lcdSaturation->setDigitCount(3);
    ui->lcdIntensity->setDigitCount(3);
}

void MainWindow::buildGraphics()
{
    item = new QGraphicsPixmapItem;

    inputScene = new QGraphicsScene(this);
    outputScene = new QGraphicsScene(this);

    ui->graphicsViewInput->setScene(inputScene);
    ui->graphicsViewOutput->setScene(outputScene);

    ui->graphicsViewInput->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    ui->graphicsViewOutput->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);

    ui->graphicsViewInput->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsViewOutput->setDragMode(QGraphicsView::ScrollHandDrag);
}

// ----- File Menu Action Slots -----------------------------------------------
void MainWindow::openDefault()
{
    menuStatus("File","Open from Image List");

    QString tmp = ui->comboBoxImageSelector->currentText();
    tmp = QString(":/") +  tmp; // used to define path to a resource file
    appendStatus(QString("Loading from default list ... ") + tmp);

    inputImage.setImage(tmp, -1);
    outputImage.setImage(tmp, -1);

    updateInput();
    updateOutput();
}

void MainWindow::open()
{
    menuStatus("File","Open");

    QFileDialog dialog(this);

    // --- Create a dialog window to generate a user path ---
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);

    dialog.setDirectory(defaultDirectory);
    dialog.setNameFilter(tr("Image (*.png)"));
    dialog.setDefaultSuffix("png");

    if (dialog.exec())
    {
        QStringList fileList = dialog.selectedFiles();
        QString filePath = fileList.at(0);

        appendStatus(QString("Loading from file ... ") + filePath);

        inputImage.setImage(filePath);
        outputImage.setImage(filePath);

        updateInput();
        updateOutput();
    }
    else {
        appendStatus(" ... open canceled");
    }
}

void MainWindow::reset()
{
    menuStatus("File","Reset");

    // --- Check if image data exists ---
    if(false)
    {
        appendStatus(QString("No data loaded."));
        return;
    }

    inputScene->clear();
    outputScene->clear();
    appendStatus(QString("Images cleared"));
}

void MainWindow::save()
{
    menuStatus("File","Save");

    // --- Check if image data exists ---
    if(false)
    {
        appendStatus(QString("No data loaded, save canceled."));
        return;
    }

    QString tmpName = "/_tmp.png";
    QString filePath = defaultDirectory.path() + tmpName;

    outputImage.saveImageToPNG(filePath);
    appendStatus(QString("Saving to file ... ") + filePath);
}

void MainWindow::saveAs()
{
    menuStatus("File","Save As...");

    if(false)
    {
        appendStatus(QString("No data loaded, save canceled."));
        return;
    }

    // --- Create a dialog window to generate a user path ---
    QFileDialog dialog(this);

    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);

    dialog.setDirectory(QDir::homePath() + QString("/Desktop"));
    dialog.setNameFilter(tr("Image (*.png)"));
    dialog.setDefaultSuffix("png");

    if (dialog.exec())
    {
        QStringList fileList = dialog.selectedFiles();
        QString filePath = fileList.at(0);
        appendStatus(QString("Saving to file ... ") + filePath);

        outputImage.saveImageToPNG(filePath);
    }
    else {
        appendStatus(" ... save canceled");
    }
}

void MainWindow::close()
{
    menuStatus("File","Close");

    // TODO: add an screen clear function here to close current image processing

}

void MainWindow::quit()
{
    menuStatus("File","Quit");
    QApplication::quit();
}

// ----- Help Menu Action Slots -----------------------------------------------
void MainWindow::about()
{
    menuStatus("Help","About Application");
}

void MainWindow::aboutQt()
{

}

void MainWindow::aboutAuthor()
{
    menuStatus("Help","About Author");
}

// ----- Status Bar Slots -----------------------------------------------------
void MainWindow::menuStatus(QString menuString, QString subMenuString)
{
    QString S = " >> ";
    QString tmp = menuString + S + subMenuString + S;
    statusBar()->showMessage(tmp);
}

void MainWindow::appendStatus(QString newString)
{
    statusBar()->showMessage(statusBar()->currentMessage()+newString);
}

void MainWindow::colorStatus()
{
    QString tmp = "Color adjusted >>\tRGB: [ ";
            tmp += QString::number(ui->sliderRed->value()) + ", ";
            tmp += QString::number(ui->sliderGreen->value()) + ", ";
            tmp += QString::number(ui->sliderBlue->value());
            tmp += " ]\t>>\tHSI: [ ";
            tmp += QString::number(ui->sliderHue->value()) + ", ";
            tmp += QString::number(ui->sliderSaturation->value()) + ", ";
            tmp += QString::number(ui->sliderIntensity->value());
            tmp += " ]";
    statusBar()->showMessage(tmp);
}

// ---- Graphics Slots -----------------------------------------------
void MainWindow::updateInput()
{
    inputScene->clear();
    inputScene->setSceneRect(0, 0, inputImage.image.cols, inputImage.image.rows);
    inputScene->addPixmap(QPixmap::fromImage(inputImage.getQImage()));
}

void MainWindow::updateOutput()
{
    outputScene->clear();
    outputScene->setSceneRect(0, 0, outputImage.image.cols, outputImage.image.rows);
    outputScene->addPixmap(QPixmap::fromImage(outputImage.getQImage()));
}

void MainWindow::updateRedColor()
{
    double tmp = 1.0 * ui->sliderRed->value() / ui->sliderRed->maximum();
    outputImage.adjustRGB(inputImage.image, 2, tmp);
    updateOutput();
    updateHSISliders();
}

void MainWindow::updateGreenColor()
{
    double tmp = 1.0 * ui->sliderGreen->value() / ui->sliderGreen->maximum();
    outputImage.adjustRGB(inputImage.image, 1, tmp);
    updateOutput();
    updateHSISliders();
}

void MainWindow::updateBlueColor()
{
    double tmp = 1.0 * ui->sliderBlue->value() / ui->sliderBlue->maximum();
    outputImage.adjustRGB(inputImage.image, 0, tmp);
    updateOutput();
    updateHSISliders();
}

void MainWindow::updateHSVColor()
{
    updateRGBSliders();

    double R = 1.0 * ui->sliderRed->value() / ui->sliderRed->maximum();
    double G = 1.0 * ui->sliderGreen->value() / ui->sliderGreen->maximum();
    double B = 1.0 * ui->sliderBlue->value() / ui->sliderBlue->maximum();

    outputImage.adjustRGB(inputImage.image, R, G, B);
    updateOutput();
}

// ---- Color Map Slots ------------------------------------------------------
void MainWindow::updateRedValue()
{
    ui->lcdRed->display(ui->sliderRed->value());
    colorStatus();
}

void MainWindow::updateGreenValue()
{
    ui->lcdGreen->display(ui->sliderGreen->value());
    colorStatus();
}

void MainWindow::updateBlueValue()
{
    ui->lcdBlue->display(ui->sliderBlue->value());
    colorStatus();
}

void MainWindow::updateHueValue()
{
    ui->lcdHue->display(ui->sliderHue->value());
    colorStatus();
}

void MainWindow::updateSaturationValue()
{
    ui->lcdSaturation->display(ui->sliderSaturation->value());
    colorStatus();
}

void MainWindow::updateIntensityValue()
{
    ui->lcdIntensity->display(ui->sliderIntensity->value());
    colorStatus();
}

void MainWindow::updateRGBSliders()
{
    double PI, R, G, B, H, S, I, angle1, angle2, angle3, angle4;

    PI = acos(-1);
    H = 1.0 * ui->sliderHue->value() / ui->sliderHue->maximum();
    S = 1.0 * ui->sliderSaturation->value() / ui->sliderSaturation->maximum();
    I = 1.0 * ui->sliderIntensity->value() / ui->sliderIntensity->maximum();

    H *= (2.0 * PI);
    angle1 = 0.0;
    angle2 = (1.0/3.0) * 2.0 * PI;
    angle3 = angle2 * 2.0;
    angle4 = angle2 * 3.0;

    if (angle1 <= H && H < angle2)
    {
        H -= angle1;
        B = I * (1.0 - S);
        R = I * (1.0 + S * cos(H) / cos(angle2 / 2.0 - H));
        G = 3.0 * I - (R + B);
    }
    else if (angle2 <= H && H < angle3)
    {
        H -= angle2;
        R = I * (1.0 - S);
        G = I * (1.0 + S * cos(H) / cos(angle2 / 2.0 - H));
        B = 3.0 * I - (R + G);
    }
    else
    {
        H -= angle3;
        G = I * (1.0 - S);
        B = I * (1.0 + S * cos(H) / cos(angle2 / 2.0 - H));;
        R = 3.0 * I - (G + B);
    }

    R *= 1.0 * ui->sliderRed->maximum();
    G *= 1.0 * ui->sliderGreen->maximum();
    B *= 1.0 * ui->sliderBlue->maximum();

    ui->sliderRed->setValue(round(R));
    ui->sliderGreen->setValue(round(G));
    ui->sliderBlue->setValue(round(B));

    colorStatus();
}

void MainWindow::updateHSISliders()
{
    double PI, R, G, B, H, S, I, theta, tmpNum, tmpDen, tmpMin;

    PI = acos(-1);
    R = 1.0 * ui->sliderRed->value() / ui->sliderRed->maximum();
    G = 1.0 * ui->sliderGreen->value() / ui->sliderGreen->maximum();
    B = 1.0 * ui->sliderBlue->value() / ui->sliderBlue->maximum();

    tmpNum = (R - G) + (R - B);
    tmpDen = pow((R - G), 2.0) + (R - B) * (G - B);
    theta = acos(0.5 * tmpNum / pow(tmpDen, 0.5));

    if (B > G)
    {
        H = 2.0 * PI - theta;
        tmpMin = G;
    }
    else
    {
        H = theta;
        tmpMin = B;
    }
    if (R < tmpMin)
    {
        tmpMin = R;
    }

    H /= (2.0 * PI);
    S = 1.0 - ( 3.0 / (R + G + B)) * tmpMin;
    I = (1.0 / 3.0) * (R + G + B);

    H *= 1.0 * ui->sliderHue->maximum();
    S *= 1.0 * ui->sliderSaturation->maximum();
    I *= 1.0 * ui->sliderIntensity->maximum();

    ui->sliderHue->setValue(round(H));
    ui->sliderSaturation->setValue(round(S));
    ui->sliderIntensity->setValue(round(I));

    colorStatus();
}


