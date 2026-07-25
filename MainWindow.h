#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QMutex>

#include "GalaxyIncludes.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow;

//==========================================================
// Daheng Capture Callback
//==========================================================
class CaptureEvent : public ICaptureEventHandler
{
public:
    CaptureEvent(MainWindow* wnd, int index);

    virtual void DoOnImageCaptured(CImageDataPointer& objImageDataPointer,
                                   void* pUserParam);

private:
    MainWindow* m_mainWindow;
    int m_cameraIndex;
};

//==========================================================
// Main Window
//==========================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

    void frameReady(int cameraIndex, const QImage& image);

private slots:

    void onFrameReady(int cameraIndex, const QImage& image);

private:

    //--------------------------------------------------
    // SDK
    //--------------------------------------------------
    bool initializeGalaxy();
    void detectCameras();
    bool openCamera(int index);
    void startGrab(int index);
    void stopGrab(int index);
    void closeCameras();

    //--------------------------------------------------
    // UI
    //--------------------------------------------------
    void initializeGraphicsView();
    void addLog(const QString& text);

    //--------------------------------------------------
    // Callback Helper
    //--------------------------------------------------
    friend class CaptureEvent;

    void processImage(int cameraIndex,
                      CImageDataPointer& image);

private:

    Ui::MainWindow *ui;

    //--------------------------------------------------
    // Graphics Views
    //--------------------------------------------------
    QGraphicsScene* sceneLive = nullptr;
    QGraphicsScene* sceneCam1 = nullptr;
    QGraphicsScene* sceneCam2 = nullptr;

    QGraphicsPixmapItem* itemLive = nullptr;
    QGraphicsPixmapItem* itemCam1 = nullptr;
    QGraphicsPixmapItem* itemCam2 = nullptr;

    //--------------------------------------------------
    // Galaxy SDK
    //--------------------------------------------------
    bool m_sdkInitialized = false;

    bool m_camera1Connected = false;
    bool m_camera2Connected = false;

    gxdeviceinfo_vector m_deviceList;

    CGXDevicePointer m_device1;
    CGXDevicePointer m_device2;

    CGXStreamPointer m_stream1;
    CGXStreamPointer m_stream2;

    CGXFeatureControlPointer m_feature1;
    CGXFeatureControlPointer m_feature2;

    CGXFeatureControlPointer m_streamFeature1;
    CGXFeatureControlPointer m_streamFeature2;

    //--------------------------------------------------
    // Callback Objects
    //--------------------------------------------------
    CaptureEvent* m_capture1 = nullptr;
    CaptureEvent* m_capture2 = nullptr;

    //--------------------------------------------------
    // Thread Safety
    //--------------------------------------------------
    QMutex m_mutex;
};