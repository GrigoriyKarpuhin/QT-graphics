#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    Q3DSurface *graph = new Q3DSurface();
    Q3DScatter *graphMod = new Q3DScatter();

    QWidget *container = QWidget::createWindowContainer(graph);
    QWidget *containerMod = QWidget::createWindowContainer(graphMod);

    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(container);
    stackedWidget->addWidget(containerMod);

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(stackedWidget, 1);
    hLayout->addLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);

   plotGroupBox = new QGroupBox(tr("График"));

    sinc1 = new QRadioButton(widget);
    sinc1->setText(QStringLiteral("Sinc1"));
    sinc1->setChecked(false);

    sinc2 = new QRadioButton(widget);
    sinc2->setText(QStringLiteral("Sinc2"));
    sinc2->setChecked(false);

    QVBoxLayout *graphsBox = new QVBoxLayout;
    graphsBox->addWidget(sinc1);
    graphsBox->addWidget(sinc2);
    plotGroupBox->setLayout(graphsBox);

    vLayout->addWidget(plotGroupBox);

    colorGroupBox = new QGroupBox(tr("Выбор градиента"));

    QLinearGradient grBl(0, 0, 1, 100);
    grBl.setColorAt(1.0, Qt::cyan);
    grBl.setColorAt(0.5, Qt::blue);
    grBl.setColorAt(0.0, Qt::darkMagenta);
    QPixmap pm(24, 100);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(grBl));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(0, 0, 24, 100);
    gradientBlue = new QPushButton(widget);
    gradientBlue->setIcon(QIcon(pm));
    gradientBlue->setIconSize(QSize(24, 100));

    QLinearGradient grPiv(0, 0, 1, 100);
    grPiv.setColorAt(1.0, QColor(68, 1, 84));
    grPiv.setColorAt(0.75, QColor(59, 82, 139));
    grPiv.setColorAt(0.5, QColor(33, 145, 140));
    grPiv.setColorAt(0.25, QColor(94, 201, 98));
    grPiv.setColorAt(0.0, QColor(253, 231, 37));
    pmp.setBrush(QBrush(grPiv));
    pmp.drawRect(0, 0, 24, 100);
    gradientPivot = new QPushButton(widget);
    gradientPivot->setIcon(QIcon(pm));
    gradientPivot->setIconSize(QSize(24, 100));

    QHBoxLayout *colorHBox = new QHBoxLayout;
    colorHBox->addWidget(gradientBlue);
    colorHBox->addWidget(gradientPivot);
    colorGroupBox->setLayout(colorHBox);

    vLayout->addWidget(colorGroupBox);

    selectionGroupBox = new QGroupBox(tr("Режим выбора"));

    noSelect = new QRadioButton(widget);
    noSelect->setText(tr("Без выбора"));
    noSelect->setChecked(false);

    item = new QRadioButton(widget);
    item->setText(tr("Точка"));
    item->setChecked(false);

    QVBoxLayout *selectBox = new QVBoxLayout;
    selectBox->addWidget(noSelect);
    selectBox->addWidget(item);
    selectionGroupBox->setLayout(selectBox);

    vLayout->addWidget(selectionGroupBox);

    axisMinSliderX = new QSlider(Qt::Horizontal, widget);
    axisMinSliderX->setMinimum(0);
    axisMinSliderX->setTickInterval(1);
    axisMinSliderX->setEnabled(true);

    axisMaxSliderX = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderX->setMinimum(1);
    axisMaxSliderX->setTickInterval(1);
    axisMaxSliderX->setEnabled(true);

    axisMinSliderZ = new QSlider(Qt::Horizontal, widget);
    axisMinSliderZ->setMinimum(0);
    axisMinSliderZ->setTickInterval(1);
    axisMinSliderZ->setEnabled(true);

    axisMaxSliderZ = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderZ->setMinimum(1);
    axisMaxSliderZ->setTickInterval(1);
    axisMaxSliderZ->setEnabled(true);

    column = new QLabel(tr("Диапазон столбцов"));
    row = new QLabel(tr("Диапазон строк"));

    vLayout->addWidget(column);
    vLayout->addWidget(axisMinSliderX);
    vLayout->addWidget(axisMaxSliderX);
    vLayout->addWidget(row);
    vLayout->addWidget(axisMinSliderZ);
    vLayout->addWidget(axisMaxSliderZ);

    stepsGroupBox = new QGroupBox(tr("Размер шага (x,z)"));

    stepsX = new QSpinBox(widget);
    stepsX->setRange(1, 100);
    stepsX->setSingleStep(1);
    stepsX->setValue(50);

    stepsZ = new QSpinBox(widget);
    stepsZ->setRange(1, 100);
    stepsZ->setSingleStep(1);
    stepsZ->setValue(50);

    QVBoxLayout *stepsBox = new QVBoxLayout;
    stepsBox->addWidget(stepsX);
    stepsBox->addWidget(stepsZ);
    stepsGroupBox->setLayout(stepsBox);

    vLayout->addWidget(stepsGroupBox);

    displayGroupBox = new QGroupBox(tr("Настройки отображения графика"));

    grid = new QCheckBox(widget);
    grid->setText(tr("Показывать сетку"));
    grid->setChecked(false);

    label = new QCheckBox(widget);
    label->setText(tr("Показывать ярлыки"));
    label->setChecked(false);

    labelBorder = new QCheckBox(widget);
    labelBorder->setText(tr("Показывать границу ярлыков"));
    labelBorder->setChecked(false);

    QVBoxLayout *displayBox = new QVBoxLayout;
    displayBox->addWidget(grid);
    displayBox->addWidget(label);
    displayBox->addWidget(labelBorder);
    displayGroupBox->setLayout(displayBox);

    vLayout->addWidget(displayGroupBox);

    saveButton = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton), "", this);
    saveButton->setShortcuts(QKeySequence::Save);
    saveButton->setStatusTip(tr("Сохранить настройки"));

    loadButton = new QAction(style()->standardIcon(QStyle::SP_DialogHelpButton), "", this);
    loadButton->setShortcuts(QKeySequence::Refresh);
    loadButton->setStatusTip(tr("Загрузить настройки"));

    menu = menuBar()->addMenu("");
    menu->addAction(saveButton);
    menu->addAction(loadButton);

    tb = addToolBar(tr("Панель инструментов"));
    tb->addAction(saveButton);
    tb->addAction(loadButton);

    translateGroupBox = new QGroupBox(tr("Выбор языка"));

    rus = new QRadioButton(widget);
    rus->setText(QStringLiteral("Русский язык"));
    rus->setChecked(false);

    eng = new QRadioButton(widget);
    eng->setText(QStringLiteral("English language"));
    eng->setChecked(false);

    QVBoxLayout *languageBox = new QVBoxLayout;
    languageBox->addWidget(rus);
    languageBox->addWidget(eng);
    translateGroupBox->setLayout(languageBox);

    vLayout->addWidget(translateGroupBox);

    modificationGroupBox = new QGroupBox(tr("Модификация"));

    surface = new QRadioButton(widget);
    surface->setText(tr("Поверхность"));
    surface->setChecked(false);

    scatter = new QRadioButton(widget);
    scatter->setText(tr("Разброс"));
    scatter->setChecked(false);

    QVBoxLayout *modificationBox = new QVBoxLayout;
    modificationBox->addWidget(surface);
    modificationBox->addWidget(scatter);
    modificationGroupBox->setLayout(modificationBox);

    vLayout->addWidget(modificationGroupBox);

    setCentralWidget(widget);

    plot = new Plot(graph);
    QObject::connect(sinc1, &QRadioButton::toggled,
                     plot, &Plot::enableDistPlot);
    QObject::connect(sinc2, &QRadioButton::toggled,
                     plot, &Plot::enableSincPlot);
    QObject::connect(gradientBlue, &QPushButton::pressed,
                     this, &MainWindow::disablePivot);
    QObject::connect(gradientBlue, &QPushButton::pressed,
                     plot, &Plot::blueGradient);
    QObject::connect(gradientPivot, &QPushButton::pressed,
                     this, &MainWindow::disableBlue);
    QObject::connect(gradientPivot, &QPushButton::pressed,
                     plot, &Plot::pivotGradient);
    QObject::connect(noSelect, &QPushButton::pressed,
                     plot, &Plot::toggleModeNoSelect);
    QObject::connect(item, &QPushButton::pressed,
                     plot, &Plot::toggleModeItem);
    QObject::connect(axisMinSliderX, &QSlider::valueChanged,
                     plot, &Plot::adjustXMin);
    QObject::connect(axisMaxSliderX, &QSlider::valueChanged,
                     plot, &Plot::adjustXMax);
    QObject::connect(axisMinSliderZ, &QSlider::valueChanged,
                     plot, &Plot::adjustZMin);
    QObject::connect(axisMaxSliderZ, &QSlider::valueChanged,
                     plot, &Plot::adjustZMax);
    QObject::connect(stepsX, QOverload< int >::of(&QSpinBox::valueChanged),
                     plot, &Plot::recountStepX);
    QObject::connect(stepsZ, QOverload< int >::of(&QSpinBox::valueChanged),
                     plot, &Plot::recountStepZ);
    QObject::connect(grid, &QCheckBox::toggled,
                     plot, &Plot::gridShow);
    QObject::connect(label, &QCheckBox::toggled,
                     plot, &Plot::labelShow);
    QObject::connect(labelBorder, &QCheckBox::toggled,
                     plot, &Plot::labelBorderShow);
    QObject::connect(saveButton, &QAction::triggered,
                     this, &MainWindow::saveSettings);
    QObject::connect(loadButton, &QAction::triggered,
                     this, &MainWindow::loadSettings);
    QObject::connect(eng, &QRadioButton::toggled,
                     this, &MainWindow::switchToEng);
    QObject::connect(rus, &QRadioButton::toggled,
                     this, &MainWindow::switchToRus);
    QObject::connect(surface, &QRadioButton::toggled,
                     this, &MainWindow::changeToSurface);
    QObject::connect(scatter, &QRadioButton::toggled,
                     this, &MainWindow::changeToScatter);

    plot->setAxisMinSliderX(axisMinSliderX);
    plot->setAxisMaxSliderX(axisMaxSliderX);
    plot->setAxisMinSliderZ(axisMinSliderZ);
    plot->setAxisMaxSliderZ(axisMaxSliderZ);


    plotMod = new Plot(graphMod);
    QObject::connect(sinc1, &QRadioButton::toggled,
                     plotMod, &Plot::enableDistPlotMod);
    QObject::connect(sinc2, &QRadioButton::toggled,
                     plotMod, &Plot::enableSincPlotMod);
    QObject::connect(gradientBlue, &QPushButton::pressed,
                     plotMod, &Plot::blueGradientMod);
    QObject::connect(gradientPivot, &QPushButton::pressed,
                     plotMod, &Plot::pivotGradientMod);
    QObject::connect(noSelect, &QPushButton::pressed,
                     plotMod, &Plot::toggleModeNoSelectMod);
    QObject::connect(item, &QPushButton::pressed,
                     plotMod, &Plot::toggleModeItemMod);
    QObject::connect(axisMinSliderX, &QSlider::valueChanged,
                     plotMod, &Plot::adjustXMinMod);
    QObject::connect(axisMaxSliderX, &QSlider::valueChanged,
                     plotMod, &Plot::adjustXMaxMod);
    QObject::connect(axisMinSliderZ, &QSlider::valueChanged,
                     plotMod, &Plot::adjustZMinMod);
    QObject::connect(axisMaxSliderZ, &QSlider::valueChanged,
                     plotMod, &Plot::adjustZMaxMod);
    QObject::connect(stepsX, QOverload< int >::of(&QSpinBox::valueChanged),
                     plotMod, &Plot::recountStepXMod);
    QObject::connect(stepsZ, QOverload< int >::of(&QSpinBox::valueChanged),
                     plotMod, &Plot::recountStepZMod);
    QObject::connect(grid, &QCheckBox::toggled,
                     plotMod, &Plot::gridShowMod);
    QObject::connect(label, &QCheckBox::toggled,
                     plotMod, &Plot::labelShowMod);
    QObject::connect(labelBorder, &QCheckBox::toggled,
                     plotMod, &Plot::labelBorderShowMod);

    plotMod->setAxisMinSliderX(axisMinSliderX);
    plotMod->setAxisMaxSliderX(axisMaxSliderX);
    plotMod->setAxisMinSliderZ(axisMinSliderZ);
    plotMod->setAxisMaxSliderZ(axisMaxSliderZ);

    sinc1->setChecked(true);
    item->setChecked(true);
    grid->setChecked(true);
    label->setChecked(true);
    labelBorder->setChecked(true);
    rus->setChecked(true);
    surface->setChecked(true);

    loadSettings();

    this->statusBar()->show();
}


MainWindow::~MainWindow()
{
}

void MainWindow::saveSettings()
{
    settings.clear();
    settings.setValue("plotDistanceFromZero", sinc1->isChecked());
    settings.setValue("plotSinc", sinc2->isChecked());
    settings.setValue("noneMode", noSelect->isChecked());
    settings.setValue("itemMode", item->isChecked());
    settings.setValue("axisMinSliderX", axisMinSliderX->value());
    settings.setValue("axisMaxSliderX", axisMaxSliderX->value());
    settings.setValue("axisMinSliderZ", axisMinSliderZ->value());
    settings.setValue("axisMaxSliderZ", axisMaxSliderZ->value());
    settings.setValue("xSteps", stepsX->value());
    settings.setValue("zSteps", stepsZ->value());
    settings.setValue("grid", grid->isChecked());
    settings.setValue("label", label->isChecked());
    settings.setValue("labelBorder", labelBorder->isChecked());
    settings.setValue("rusLang", rus->isChecked());
    settings.setValue("engLang", eng->isChecked());
    settings.setValue("surface", surface->isChecked());
    settings.setValue("scatter", scatter->isChecked());
    if(blueIsActive)
    {
        settings.setValue("blueGradient", true);
    } else if(pivotIsActive)
    {
        settings.setValue("pivotGradient", true);
    }
}

void MainWindow::loadSettings()
{
    if (settings.contains("plotDistanceFromZero"))
    {
        sinc1->setChecked(settings.value("plotDistanceFromZero").toBool());
    }
    if (settings.contains("plotSinc"))
    {
        sinc2->setChecked(settings.value("plotSinc").toBool());
    }
    if (settings.contains("blueGradient"))
    {
        plot->blueGradient();
        plotMod->blueGradientMod();
    }
    if (settings.contains("pivotGradient"))
    {
        plot->pivotGradient();
        plotMod->pivotGradientMod();
    }
    if (settings.contains("noneMode"))
    {
        noSelect->setChecked(settings.value("noneMode").toBool());
    }
    if (settings.contains("itemMode"))
    {
        item->setChecked(settings.value("itemMode").toBool());
    }
    if (settings.contains("axisMinSliderX"))
    {
        axisMinSliderX->setValue(settings.value("axisMinSliderX").toInt());
    }
    if (settings.contains("axisMaxSliderX"))
    {
        axisMaxSliderX->setValue(settings.value("axisMaxSliderX").toInt());
    }
    if (settings.contains("axisMinSliderZ"))
    {
        axisMinSliderZ->setValue(settings.value("axisMinSliderZ").toInt());
    }
    if (settings.contains("axisMaxSliderZ"))
    {
        axisMaxSliderZ->setValue(settings.value("axisMaxSliderZ").toInt());
    }
    if (settings.contains("xSteps"))
    {
        stepsX->setValue(settings.value("xSteps").toInt());
    }
    if (settings.contains("zSteps"))
    {
        stepsZ->setValue(settings.value("zSteps").toInt());
    }
    if (settings.contains("grid"))
    {
        grid->setChecked(settings.value("grid").toBool());
    }
    if (settings.contains("label"))
    {
        label->setChecked(settings.value("label").toBool());
    }
    if (settings.contains("labelBorder"))
    {
        labelBorder->setChecked(settings.value("labelBorder").toBool());
    }
    if (settings.contains("rusLang"))
    {
        rus->setChecked(settings.value("rusLang").toBool());
    }
    if (settings.contains("engLang"))
    {
        eng->setChecked(settings.value("engLang").toBool());
    }
    if (settings.contains("surface"))
    {
        surface->setChecked(settings.value("surface").toBool());
    }
    if (settings.contains("scatter"))
    {
        scatter->setChecked(settings.value("scatter").toBool());
    }
}

void MainWindow::disablePivot()
{
    pivotIsActive = false;
    blueIsActive = true;
}

void MainWindow::disableBlue()
{
    pivotIsActive = true;
    blueIsActive = false;
}

void MainWindow::switchToEng()
{
    QApplication::removeTranslator(translator);
    translator = new QTranslator(this);
    translator->load(":/i18n/lab4_en_GB.qm");
    QApplication::installTranslator(translator);
    updateLang();
}

void MainWindow::switchToRus()
{
    QApplication::removeTranslator(translator);
    updateLang();
}

void MainWindow::updateLang()
{
    plotGroupBox->setTitle(tr("График"));
    colorGroupBox->setTitle(tr("Выбор градиента"));
    selectionGroupBox->setTitle(tr("Режим выбора"));
    noSelect->setText(tr("Без выбора"));
    item->setText(tr("Точка"));
    column->setText(tr("Диапазон столбцов"));
    row->setText(tr("Диапазон строк"));
    stepsGroupBox->setTitle(tr("Размер шага (x,z)"));
    displayGroupBox->setTitle(tr("Настройки отображения графика"));
    grid->setText(tr("Показывать сетку"));
    label->setText(tr("Показывать ярлыки"));
    labelBorder->setText(tr("Показывать границу ярлыков"));
    saveButton->setStatusTip(tr("Сохранить настройки"));
    loadButton->setStatusTip(tr("Загрузить настройки"));
    translateGroupBox->setTitle(tr("Выбор языка"));
    modificationGroupBox->setTitle(tr("Модификация"));
    surface->setText(tr("Поверхность"));
    scatter->setText(tr("Разброс"));
}

void MainWindow::changeToSurface()
{
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::changeToScatter()
{
    stackedWidget->setCurrentIndex(1);
}
