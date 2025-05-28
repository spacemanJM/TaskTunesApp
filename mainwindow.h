#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qlistwidget.h>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QFileDialog>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_taskList_itemDoubleClicked(QListWidgetItem *item);

    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_volumeSlider_valueChanged(int value);

    void on_lightMode_clicked();

    void on_pausePlayButton_clicked();

    void on_previousSongButton_clicked();

    void on_nextSongButton_clicked();

    void on_shuffleButton_clicked();

    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QVector<QUrl> playlist;
    QStack<int> shuffleHistory;
    int currentSongIndex = 0;
    int randomNum = 0;
    bool isDarkMode = true;
    bool shuffleOn = false;
};
#endif // MAINWINDOW_H
