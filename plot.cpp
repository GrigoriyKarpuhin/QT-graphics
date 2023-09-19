#include "plot.h"

#include <QtCore/qmath.h>

int sampleCountX = 50;
int sampleCountZ = 50;
const float sampleMin = -10.0f;
const float sampleMax = 10.0f;

Plot::Plot(Q3DSurface *plot)
    : graph(plot)
{
    graph->setAxisX(new QValue3DAxis);
    graph->setAxisY(new QValue3DAxis);
    graph->setAxisZ(new QValue3DAxis);

    distProxy = new QSurfaceDataProxy();
    distSeries = new QSurface3DSeries(distProxy);
    sincProxy = new QSurfaceDataProxy();
    sincSeries = new QSurface3DSeries(sincProxy);
    fillDistProxy();
    fillSincProxy();
}

Plot::~Plot()
{
    delete graph;
    delete graphMod;
}

void Plot::fillDistProxy()
{
    float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);
    for (int i = 0 ; i < sampleCountZ ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountX);
        float z = qMin(sampleMax, (i * stepZ + sampleMin));
        int index = 0;
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(sampleMax, (j * stepX + sampleMin));
            float R = qSqrt(z * z + x * x) + 0.01f;
            float y = (qSin(R) / R + 0.24f) * 1.61f;
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        *dataArray << newRow;
    }

    distProxy->resetArray(dataArray);
}

void Plot::fillSincProxy()
{
    float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);
    for (int i = 0 ; i < sampleCountZ ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountX);
        float z = qMin(sampleMax, (i * stepZ + sampleMin));
        int index = 0;
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(sampleMax, (j * stepX + sampleMin));
            float sincX = (x != 0.0f) ? (qSin(x) / x) : 1.0f;
            float sincZ = (z != 0.0f) ? (qSin(z) / z) : 1.0f;
            float y = sincX * sincZ + 0.4;
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        *dataArray << newRow;
    }

    sincProxy->resetArray(dataArray);
}

void Plot::enableDistPlot(bool enable)
{
    if (enable) {
        distSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        distSeries->setFlatShadingEnabled(true);

        graph->axisX()->setLabelFormat("%.2f");
        graph->axisZ()->setLabelFormat("%.2f");
        graph->axisX()->setRange(sampleMin, sampleMax);
        graph->axisY()->setRange(0.0f, 2.0f);
        graph->axisZ()->setRange(sampleMin, sampleMax);
        graph->axisX()->setLabelAutoRotation(30);
        graph->axisY()->setLabelAutoRotation(90);
        graph->axisZ()->setLabelAutoRotation(30);

        graph->removeSeries(sincSeries);
        graph->addSeries(distSeries);

        rangeMinX = sampleMin;
        rangeMinZ = sampleMin;
        stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
        stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

        rangeMinX = sampleMin;
        rangeMinZ = sampleMin;
        stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
        stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);
        axisMinSliderX->setMaximum(sampleCountX - 2);
        axisMinSliderX->setValue(0);
        axisMaxSliderX->setMaximum(sampleCountX - 1);
        axisMaxSliderX->setValue(sampleCountX - 1);
        axisMinSliderZ->setMaximum(sampleCountZ - 2);
        axisMinSliderZ->setValue(0);
        axisMaxSliderZ->setMaximum(sampleCountZ - 1);
        axisMaxSliderZ->setValue(sampleCountZ - 1);
    }
}

void Plot::enableSincPlot(bool enable)
{
    if (enable) {
        sincSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        sincSeries->setFlatShadingEnabled(true);

        graph->axisX()->setLabelFormat("%.2f");
        graph->axisZ()->setLabelFormat("%.2f");
        graph->axisX()->setRange(sampleMin, sampleMax);
        graph->axisY()->setRange(0.0f, 2.0f);
        graph->axisZ()->setRange(sampleMin, sampleMax);
        graph->axisX()->setLabelAutoRotation(30);
        graph->axisY()->setLabelAutoRotation(90);
        graph->axisZ()->setLabelAutoRotation(30);

        graph->removeSeries(distSeries);
        graph->addSeries(sincSeries);

        rangeMinX = sampleMin;
        rangeMinZ = sampleMin;
        stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
        stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

        rangeMinX = sampleMin;
        rangeMinZ = sampleMin;
        stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
        stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);
        axisMinSliderX->setMaximum(sampleCountX - 2);
        axisMinSliderX->setValue(0);
        axisMaxSliderX->setMaximum(sampleCountX - 1);
        axisMaxSliderX->setValue(sampleCountX - 1);
        axisMinSliderZ->setMaximum(sampleCountZ - 2);
        axisMinSliderZ->setValue(0);
        axisMaxSliderZ->setMaximum(sampleCountZ - 1);
        axisMaxSliderZ->setValue(sampleCountZ - 1);
    }
}

void Plot::blueGradient()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::darkMagenta);
    gr.setColorAt(0.5, Qt::blue);
    gr.setColorAt(1.0, Qt::cyan);
    graph->seriesList().at(0)->setBaseGradient(gr);
    graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

void Plot::pivotGradient()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, QColor(253, 231, 37));
    gr.setColorAt(0.25, QColor(94, 201, 98));
    gr.setColorAt(0.5, QColor(33, 145, 140));
    gr.setColorAt(0.75, QColor(59, 82, 139));
    gr.setColorAt(1.0, QColor(68, 1, 84));
    graph->seriesList().at(0)->setBaseGradient(gr);
    graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

void Plot::adjustXMin(int min)
{
    float minX = stepX * float(min) + rangeMinX;

    int max = axisMaxSliderX->value();
    if (min >= max) {
        max = min + 1;
        axisMaxSliderX->setValue(max);
    }
    float maxX = stepX * max + rangeMinX;

    setAxisXRange(minX, maxX);
}

void Plot::adjustXMax(int max)
{
    float maxX = stepX * float(max) + rangeMinX;

    int min = axisMinSliderX->value();
    if (max <= min) {
        min = max - 1;
        axisMinSliderX->setValue(min);
    }
    float minX = stepX * min + rangeMinX;

    setAxisXRange(minX, maxX);
}

void Plot::adjustZMin(int min)
{
    float minZ = stepZ * float(min) + rangeMinZ;

    int max = axisMaxSliderZ->value();
    if (min >= max) {
        max = min + 1;
        axisMaxSliderZ->setValue(max);
    }
    float maxZ = stepZ * max + rangeMinZ;

    setAxisZRange(minZ, maxZ);
}

void Plot::adjustZMax(int max)
{
    float maxX = stepZ * float(max) + rangeMinZ;

    int min = axisMinSliderZ->value();
    if (max <= min) {
        min = max - 1;
        axisMinSliderZ->setValue(min);
    }
    float minX = stepZ * min + rangeMinZ;

    setAxisZRange(minX, maxX);
}

void Plot::setAxisXRange(float min, float max)
{
    graph->axisX()->setRange(min, max);
}

void Plot::setAxisZRange(float min, float max)
{
    graph->axisZ()->setRange(min, max);
}

void Plot::recountStepX(int newStepSize)
{
    if(newStepSize < 10)
    {
        sampleCountX = 10;
    } else
    {
        sampleCountX = newStepSize;
    }
    fillDistProxy();
    fillSincProxy();
}

void Plot::recountStepZ(int newStep)
{
    if(newStep < 10)
    {
        sampleCountZ = 10;
    } else
    {
        sampleCountZ = newStep;
    }
    fillDistProxy();
    fillSincProxy();
}

void Plot::gridShow(bool show)
{
    show ? graph->activeTheme()->setGridEnabled(true) : graph->activeTheme()->setGridEnabled(false);
}

void Plot::labelShow(bool show)
{
    show ? graph->activeTheme()->setLabelTextColor(Qt::black) : graph->activeTheme()->setLabelTextColor(Qt::white);
}

void Plot::labelBorderShow(bool show)
{
    show ? graph->activeTheme()->setLabelBorderEnabled(true) : graph->activeTheme()->setLabelBorderEnabled(false);
}


//MODIFICATION


Plot::Plot(Q3DScatter *plotMod)
    :graphMod(plotMod)
{
    graphMod->setAxisX(new QValue3DAxis);
    graphMod->setAxisY(new QValue3DAxis);
    graphMod->setAxisZ(new QValue3DAxis);

    distProxyMod = new QScatterDataProxy();
    distSeriesMod = new QScatter3DSeries(distProxyMod);
    sincProxyMod = new QScatterDataProxy();
    sincSeriesMod = new QScatter3DSeries(sincProxyMod);
    fillDistProxyMod();
    fillSincProxyMod();
}

void Plot::fillDistProxyMod()
{
    float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

    QScatterDataArray *dataArray = new QScatterDataArray;
    dataArray->resize(sampleCountX * sampleCountZ);
    QScatterDataItem *ptrToDataArray = &dataArray->first();

    for (int i = 0 ; i < sampleCountZ ; i++) {
        float z = qMin(sampleMax, (i * stepZ + sampleMin));
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(sampleMax, (j * stepX + sampleMin));
            float R = qSqrt(z * z + x * x) + 0.01f;
            float y = (qSin(R) / R + 0.24f) * 1.61f;
            ptrToDataArray->setPosition(QVector3D(x, y, z));
            ptrToDataArray++;
        }
    }

    distProxyMod->resetArray(dataArray);
}

void Plot::fillSincProxyMod()
{
    float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

    QScatterDataArray *dataArray = new QScatterDataArray;
    dataArray->resize(sampleCountX * sampleCountZ);
    QScatterDataItem *ptrToDataArray = &dataArray->first();

    for (int i = 0 ; i < sampleCountZ ; i++) {
        float z = qMin(sampleMax, (i * stepZ + sampleMin));
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(sampleMax, (j * stepX + sampleMin));
            float sincX = (x != 0.0f) ? (qSin(x) / x) : 1.0f;
            float sincZ = (z != 0.0f) ? (qSin(z) / z) : 1.0f;
            float y = sincX * sincZ + 0.4;
            ptrToDataArray->setPosition(QVector3D(x, y, z));
            ptrToDataArray++;
        }
    }

    sincProxyMod->resetArray(dataArray);
}

void Plot::enableDistPlotMod(bool enable)
{
    if (enable) {

        graphMod->axisX()->setLabelFormat("%.2f");
        graphMod->axisZ()->setLabelFormat("%.2f");
        graphMod->axisX()->setRange(sampleMin, sampleMax);
        graphMod->axisY()->setRange(0.0f, 2.0f);
        graphMod->axisZ()->setRange(sampleMin, sampleMax);
        graphMod->axisX()->setLabelAutoRotation(30);
        graphMod->axisY()->setLabelAutoRotation(90);
        graphMod->axisZ()->setLabelAutoRotation(30);

        graphMod->removeSeries(sincSeriesMod);
        graphMod->addSeries(distSeriesMod);

        rangeMinX = sampleMin;
        rangeMinZ = sampleMin;
        stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
        stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

        rangeMinX = sampleMin;
        rangeMinZ = sampleMin;
        stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
        stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);
    }
}

void Plot::enableSincPlotMod(bool enable)
{
    if (enable) {

        graphMod->axisX()->setLabelFormat("%.2f");
        graphMod->axisZ()->setLabelFormat("%.2f");
        graphMod->axisX()->setRange(sampleMin, sampleMax);
        graphMod->axisY()->setRange(0.0f, 2.0f);
        graphMod->axisZ()->setRange(sampleMin, sampleMax);
        graphMod->axisX()->setLabelAutoRotation(30);
        graphMod->axisY()->setLabelAutoRotation(90);
        graphMod->axisZ()->setLabelAutoRotation(30);

        graphMod->removeSeries(distSeriesMod);
        graphMod->addSeries(sincSeriesMod);

        rangeMinX = sampleMin;
        rangeMinZ = sampleMin;
        stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
        stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

        rangeMinX = sampleMin;
        rangeMinZ = sampleMin;
        stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
        stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);
    }
}

void Plot::blueGradientMod()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::darkMagenta);
    gr.setColorAt(0.5, Qt::blue);
    gr.setColorAt(1.0, Qt::cyan);
    graphMod->seriesList().at(0)->setBaseGradient(gr);
    graphMod->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

void Plot::pivotGradientMod()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, QColor(253, 231, 37));
    gr.setColorAt(0.25, QColor(94, 201, 98));
    gr.setColorAt(0.5, QColor(33, 145, 140));
    gr.setColorAt(0.75, QColor(59, 82, 139));
    gr.setColorAt(1.0, QColor(68, 1, 84));
    graphMod->seriesList().at(0)->setBaseGradient(gr);
    graphMod->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

void Plot::adjustXMinMod(int min)
{
    float minX = stepX * float(min) + rangeMinX;

    int max = axisMaxSliderX->value();
    if (min >= max) {
        max = min + 1;
        axisMaxSliderX->setValue(max);
    }
    float maxX = stepX * max + rangeMinX;

    setAxisXRangeMod(minX, maxX);
}

void Plot::adjustXMaxMod(int max)
{
    float maxX = stepX * float(max) + rangeMinX;

    int min = axisMinSliderX->value();
    if (max <= min) {
        min = max - 1;
        axisMinSliderX->setValue(min);
    }
    float minX = stepX * min + rangeMinX;

    setAxisXRangeMod(minX, maxX);
}

void Plot::adjustZMinMod(int min)
{
    float minZ = stepZ * float(min) + rangeMinZ;

    int max = axisMaxSliderZ->value();
    if (min >= max) {
        max = min + 1;
        axisMaxSliderZ->setValue(max);
    }
    float maxZ = stepZ * max + rangeMinZ;

    setAxisZRangeMod(minZ, maxZ);
}

void Plot::adjustZMaxMod(int max)
{
    float maxX = stepZ * float(max) + rangeMinZ;

    int min = axisMinSliderZ->value();
    if (max <= min) {
        min = max - 1;
        axisMinSliderZ->setValue(min);
    }
    float minX = stepZ * min + rangeMinZ;

    setAxisZRangeMod(minX, maxX);
}

void Plot::setAxisXRangeMod(float min, float max)
{
    graphMod->axisX()->setRange(min, max);
}

void Plot::setAxisZRangeMod(float min, float max)
{
    graphMod->axisZ()->setRange(min, max);
}

void Plot::recountStepXMod(int newStepSize)
{
    if(newStepSize < 10)
    {
        sampleCountX = 10;
    } else
    {
        sampleCountX = newStepSize;
    }
    fillDistProxyMod();
    fillSincProxyMod();
}

void Plot::recountStepZMod(int newStep)
{
    if(newStep < 10)
    {
        sampleCountZ = 10;
    } else
    {
        sampleCountZ = newStep;
    }
    fillDistProxyMod();
    fillSincProxyMod();
}

void Plot::gridShowMod(bool show)
{
    show ? graphMod->activeTheme()->setGridEnabled(true) : graphMod->activeTheme()->setGridEnabled(false);
}

void Plot::labelShowMod(bool show)
{
    show ? graphMod->activeTheme()->setLabelTextColor(Qt::black) : graphMod->activeTheme()->setLabelTextColor(Qt::white);
}

void Plot::labelBorderShowMod(bool show)
{
    show ? graphMod->activeTheme()->setLabelBorderEnabled(true) : graphMod->activeTheme()->setLabelBorderEnabled(false);
}
