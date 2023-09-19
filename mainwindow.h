#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plot.h"

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QGroupBox>
#include <QApplication>
#include <QtDataVisualization>
#include <QSpinBox>
#include <QLabel>
#include <QCheckBox>
#include <QToolBar>
#include <QMenuBar>
#include <QStyle>
#include <QStatusBar>
#include <QShortcut>
#include <QSettings>
#include <QTranslator>
#include <QLocale>
#include <QApplication>
#include <QStackedWidget>

using namespace QtDataVisualization;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void saveSettings();
    void loadSettings();

    void disableBlue();
    void disablePivot();

    void switchToEng();
    void switchToRus();
    void updateLang();

    void changeToSurface();
    void changeToScatter();
private:
    QAction *saveButton, *loadButton;
    QMenu *menu;
    QSettings settings;
    QCheckBox *grid, *label, *labelBorder;
    QRadioButton *sinc1, *sinc2;
    QPushButton *gradientBlue, *gradientPivot;
    QRadioButton *noSelect, *item;
    QSlider *axisMinSliderX, *axisMaxSliderX, *axisMinSliderZ, *axisMaxSliderZ;
    QSpinBox *stepsX, *stepsZ;
    Plot *plot;
    bool blueIsActive, pivotIsActive;
    QTranslator *translator;
    QRadioButton *rus, *eng;
    QGroupBox *plotGroupBox;
    QGroupBox *colorGroupBox;
    QGroupBox *selectionGroupBox;
    QLabel *row, *column;
    QGroupBox *stepsGroupBox;
    QGroupBox *displayGroupBox;
    QToolBar *tb;
    QGroupBox *translateGroupBox;
    QGroupBox *modificationGroupBox;
    QRadioButton *surface, *scatter;
    QStackedWidget *stackedWidget;
    Plot *plotMod;
};

#endif // MAINWINDOW_H
