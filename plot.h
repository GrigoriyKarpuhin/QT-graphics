#ifndef PLOT_H
#define PLOT_H

#include <QtDataVisualization>
#include <QVBoxLayout>
#include <QSlider>
#include <Q3DTheme>
#include <QPoint>

using namespace QtDataVisualization;

class Plot : public QObject
{
    Q_OBJECT
public:
    explicit Plot(Q3DSurface *plot);
    explicit Plot(Q3DScatter *plotMod);
    ~Plot();

    void enableDistPlot(bool enable);
    void enableSincPlot(bool enable);
    void enableDistPlotMod(bool enable);
    void enableSincPlotMod(bool enable);

    void blueGradient();
    void pivotGradient();

    void blueGradientMod();
    void pivotGradientMod();

    void toggleModeNoSelect() { graph->setSelectionMode(QAbstract3DGraph::SelectionNone); }
    void toggleModeItem() { graph->setSelectionMode(QAbstract3DGraph::SelectionItem); }

    void toggleModeNoSelectMod() { graphMod->setSelectionMode(QAbstract3DGraph::SelectionNone); }
    void toggleModeItemMod() { graphMod->setSelectionMode(QAbstract3DGraph::SelectionItem); }

    void recountStepX(int newStep);
    void recountStepZ(int newStep);

    void recountStepXMod(int newStep);
    void recountStepZMod(int newStep);

    void adjustXMin(int min);
    void adjustXMax(int max);
    void adjustZMin(int min);
    void adjustZMax(int max);

    void adjustXMinMod(int min);
    void adjustXMaxMod(int max);
    void adjustZMinMod(int min);
    void adjustZMaxMod(int max);

    void setAxisMinSliderX(QSlider *slider) { axisMinSliderX = slider; }
    void setAxisMaxSliderX(QSlider *slider) { axisMaxSliderX = slider; }
    void setAxisMinSliderZ(QSlider *slider) { axisMinSliderZ = slider; }
    void setAxisMaxSliderZ(QSlider *slider) { axisMaxSliderZ = slider; }

    void gridShow(bool show);
    void labelShow(bool show);
    void labelBorderShow(bool show);

    void gridShowMod(bool show);
    void labelShowMod(bool show);
    void labelBorderShowMod(bool show);

private:
    Q3DSurface *graph;
    Q3DScatter *graphMod;
    QSurfaceDataProxy *distProxy;
    QSurfaceDataProxy *sincProxy;
    QSurface3DSeries *distSeries;
    QSurface3DSeries *sincSeries;
    QScatterDataProxy *distProxyMod;
    QScatterDataProxy *sincProxyMod;
    QScatter3DSeries *distSeriesMod;
    QScatter3DSeries *sincSeriesMod;
    Q3DTheme *theme;
    float rangeMinX;
    float rangeMinZ;
    float stepX;
    float stepZ;

    void fillDistProxy();
    void fillSincProxy();
    void fillDistProxyMod();
    void fillSincProxyMod();

    void setAxisXRange(float min, float max);
    void setAxisZRange(float min, float max);
    void setAxisXRangeMod(float min, float max);
    void setAxisZRangeMod(float min, float max);

    QSlider *axisMinSliderX;
    QSlider *axisMaxSliderX;
    QSlider *axisMinSliderZ;
    QSlider *axisMaxSliderZ;
};

#endif // PLOT_H
