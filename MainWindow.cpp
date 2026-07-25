#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);

    if(initializeGalaxy())
    {
        detectCameras();
    }
}

bool MainWindow::initializeGalaxy()
{
    try
    {
        IGXFactory::GetInstance().Init();

        addLog("Galaxy SDK Initialized");

        return true;
    }
    catch(...)
    {
        addLog("Galaxy SDK Initialization Failed");

        return false;
    }
}

void MainWindow::detectCameras()
{
    gxdeviceinfo_vector deviceInfoList;

    IGXFactory::GetInstance().UpdateDeviceList(1000, deviceInfoList);

    int count = static_cast<int>(deviceInfoList.size());

    addLog(QString("Detected %1 Camera(s)").arg(count));

    if (count > 0)
    {
        m_camera1Connected = true;
        openCamera(0);
        addLog("Camera 1 Connected");
    }
    else
    {
        addLog("Camera 1 Not Connected");
    }

    if (count > 1)
    {
        m_camera2Connected = true;
        openCamera(1);
        addLog("Camera 2 Connected");
    }
    else
    {
        addLog("Camera 2 Not Connected");
    }
}

void MainWindow::openCamera(int index)
{
    try
    {
        // Open device
        // Open stream
        // Start grabbing
    }
    catch(...)
    {
        addLog(QString("Failed to Open Camera %1").arg(index + 1));
    }
}

MainWindow::~MainWindow()
{
    closeCameras();

    IGXFactory::GetInstance().Uninit();
}

void MainWindow::addLog(const QString &msg)
{
    ui->ocrResult->append(
        QTime::currentTime().toString("HH:mm:ss") +
        "  " + msg);
}

void MainWindow::closeCameras()
{
    try
    {
        if (m_stream1)
            m_stream1->StopGrab();

        if (m_stream2)
            m_stream2->StopGrab();

        m_stream1.reset();
        m_stream2.reset();

        m_device1.reset();
        m_device2.reset();
    }
    catch (...)
    {
    }
}