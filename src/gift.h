#ifndef GIFT_H
#define GIFT_H

#include <QObject>
#include <QGraphicsView>
#include <QFileDialog>
#include <QStandardPaths>
#include <QSettings>
#include <QProcess>
#include <QApplication>
#include <QDebug>
#include <QBuffer>
#include <QDir>

#include "graphicsview.h"
#include "imageloader.h"
#include "cropwidget.h"
#include "savedialog.h"

class Gift : public QObject
{
     Q_OBJECT
     Q_PROPERTY( bool processing READ isProcessing WRITE setProcessing NOTIFY stateChanged )
public:
    Gift(graphicsView *view = nullptr);
    ~Gift();
signals:
    void resetCoreFilters();
    void stateChanged(bool processing);
    void croppedImage();
public slots:
    void openFile();
    void applyFilter(QString filterChain);
    void reset();
    bool isProcessing();
    void saveFile();
    void compare(bool compare);
    void loadImage(QImage image);
    void imageInfo();
    void crop();
private slots:
    void updateTempImage(const QByteArray &byte, bool saveFiltered = false);
    void setProcessing(bool processing);

    void show_cropDialog(QPixmap localOriginlImage);
    void instantApplyFilter();
private:
    bool processing = false;
    QString currentFilterChain;

    graphicsView *view = nullptr;
    QSettings settings;
    QProcess *giftProcess;
    QProcess *instantGiftProcess;
    QImage scaledImage;
    QImage modifiedImage;

    ImageLoader *imageLoader = nullptr;
    SaveDialog * saveDialog = nullptr;
};

#endif // GIFT_H
