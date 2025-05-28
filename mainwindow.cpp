#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QFileDialog>
#include <QVector>
#include <QStandardPaths>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet(
        "QMainWindow {"
        " background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        " stop:0 #2a2a2a stop:1 #000000);"
        "}"
        );

    //Play Music
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(.01);

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::handleMediaStatusChanged);

    //Songs
    playlist.append(QUrl("qrc:/resources/audio/SICKO_MODE_by_Travis_Scott.wav"));
    playlist.append(QUrl("qrc:/resources/audio/Axel_F_by_Crazy_Frog.mp3"));
    playlist.append(QUrl("qrc:/resources/audio/Boom,_Boom,_Boom,_Boom!!_by_Vengaboys.mp3"));
    playlist.append(QUrl("qrc:/resources/audio/Crab_Rave_by_Noisestorm.mp3"));
    playlist.append(QUrl("qrc:/resources/audio/First_of_the_Year_(Equinox)_by_Skrillex.mp3"));
    playlist.append(QUrl("qrc:/resources/audio/We_R_Who_We_R_by_Kesha.mp3"));
    playlist.append(QUrl("qrc:/resources/audio/HOT_TO_GO!_by_Chappell_Roan.mp3"));
    playlist.append(QUrl("qrc:/resources/audio/Ievan_Polkka_by_Hatsune_Miku.mp3"));
    playlist.append(QUrl("qrc:/resources/audio/Everytime_We_Touch_by_Cascada.mp3"));
    playlist.append(QUrl("qrc:/resources/audio/Just_Can't_Get_Enough_by_Black_Eyed_Peas.mp3"));
    playlist.append(QUrl("qrc:/resources/audio/NISSAN_ALTIMA_by_Doechii.mp3"));
    playlist.append(QUrl("qrc:/resources/audio/Rock_'n'_Roll_by_Skrillex.mp3"));
    playlist.append(QUrl("qrc:/resources/audio/Rock_Your_Body_by_Justin_Timberlake.mp3"));


    //Start Playing
    player->setSource(playlist[currentSongIndex]);
    player->play();

    qDebug() << "Player Status: " << player->mediaStatus();

    //Add Icon
    QIcon addIcon(":/resources/icons/Add.png");
    ui->addButton->setIcon(addIcon);
    ui->addButton->setIconSize(QSize(20,20));

    //Delete Icon
    QIcon deleteIcon(":/resources/icons/Delete.png");
    ui->deleteButton->setIcon(deleteIcon);
    ui->deleteButton->setIconSize(QSize(20,20));

    //Save Icon
    QIcon saveIcon(":/resources/icons/Save.png");
    ui->saveButton->setIcon(saveIcon);
    ui->saveButton->setIconSize(QSize(20,20));

    //Load Icon
    QIcon loadIcon(":/resources/icons/Load.png");
    ui->loadButton->setIcon(loadIcon);
    ui->loadButton->setIconSize(QSize(20,20));

    //Light Mode Icon
    QIcon lightModeIcon(":/resources/icons/lightMode.png");
    ui->lightMode->setIcon(lightModeIcon);
    ui->lightMode->setIconSize(QSize(20,20));

    //Pause Icon
    QIcon pauseIcon(":/resources/icons/Pause.png");
    ui->pausePlayButton->setIcon(pauseIcon);
    ui->pausePlayButton->setIconSize(QSize(20,20));

    //Previous Song Icon
    QIcon previousIcon(":/resources/icons/Previous.png");
    ui->previousSongButton->setIcon(previousIcon);
    ui->previousSongButton->setIconSize(QSize(20,20));

    //Next Song Icon
    QIcon nextIcon(":/resources/icons/Next.png");
    ui->nextSongButton->setIcon(nextIcon);
    ui->nextSongButton->setIconSize(QSize(20,20));

    //Shuffle Icon
    QIcon shuffleOffIcon(":/resources/icons/shuffleOff.png");
    ui->shuffleButton->setIcon(shuffleOffIcon);
    ui->shuffleButton->setIconSize(QSize(20,20));


    //Task List Style
    ui->taskList->setStyleSheet(
        "QListWidget {"
        " background-color: #1e1e1e;"
        " color: #ffffff;"
        " border: 1px solid #444444;"
        " font-size: 16px;"
        "}"
        "QListWidget::item:selected {"
        " background-color: #3a3a3a;"
        " color: #ffffff;"
        "}"
        );

    //Task Input Style
    ui->taskInput->setStyleSheet(
        "QLineEdit {"
        " background-color: #3a3a3a;"
        " color: white;"
        " border: 1px solid #5a5a5a;"
        " border-radius: 5px;"
        " padding: 4px;"
        "}"
        "QLineEdit:focus {"
        " border: 1px solid #a0a0a0;"
        "}"
    );

    //Due Date Input Style
    ui->dueDate->setStyleSheet(
        "QDateEdit {"
        " background-color: #3a3a3a;"
        " color: white;"
        " border: 1px solid #5a5a5a;"
        " border-radius: 5px;"
        " padding: 4px;"
        "}"
        "QDateEdit::drop-down {"
        " subcobtrol-origin: padding;"
        " subcontrol-position: top right;"
        " width: 20px;"
        " border-left: 1px solid #5a5a5a;"
        "}"
    );

    //Add Button Style
    ui->addButton->setStyleSheet(
        "QPushButton {"
        " background-color: #228B22;"
        " color: white;"
        " font-weight: bold;"
        " border-radius: 8px;"
        " padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        " background-color: #006400;"
        "}"
    );

    //Delete Button Style
    ui->deleteButton->setStyleSheet(
        "QPushButton {"
        " background-color: #f44336;"
        " color: white;"
        " font-weight: bold;"
        " border-radius: 8px;"
        " padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        " background-color: #A00000;"
        "}"
    );

    //Save Button Style
    ui->saveButton->setStyleSheet(
        "QPushButton {"
        " background-color: #7f7f7f;"
        " color: white;"
        " font-weight: bold;"
        " border-radius: 8px;"
        " padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        " background-color: #3f3f3f;"
        "}"
        );

    //Load Button Style
    ui->loadButton->setStyleSheet(
        "QPushButton {"
        " background-color: #7f7f7f;"
        " color: white;"
        " font-weight: bold;"
        " border-radius: 8px;"
        " padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        " background-color: #3f3f3f;"
        "}"
        );

    //Volume Slider Style
    ui->pausePlayButton->setText(" Pause");
    ui->volumeSlider->setStyleSheet(
        "QSlider::groove:horizontal {"
        " border: 1px solid #444444;"
        " height: 6px;"
        " background: #bbbbbb;"
        " margin: 0px;"
        " border-radius: 3px;"
        "}"
        "QSlider::handle:horizontal {"
        " background: #ffffff;"
        " border: 1px solid #888888;"
        " width: 12px;"
        " margin: -5px 0;"
        " border-radius: 6px;"
        "}"
        );

    //Pause / Play button Style
    ui->pausePlayButton->setText("");
    ui->pausePlayButton->setStyleSheet(
        "QPushButton {"
        " background-color: #7f7f7f;"
        " color: white;"
        " font-weight: bold;"
        " border-radius: 8px;"
        " padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        " background-color: #3f3f3f;"
        "}"
        );

    //Previous Song Button Style
    ui->previousSongButton->setText("");
    ui->previousSongButton->setStyleSheet(
        "QPushButton {"
        " background-color: #7f7f7f;"
        " color: white;"
        " font-weight: bold;"
        " border-radius: 8px;"
        " padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        " background-color: #3f3f3f;"
        "}"
        );

    //Next Song Button Style
    ui->nextSongButton->setText("");
    ui->nextSongButton->setStyleSheet(
        "QPushButton {"
        " background-color: #7f7f7f;"
        " color: white;"
        " font-weight: bold;"
        " border-radius: 8px;"
        " padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        " background-color: #3f3f3f;"
        "}"
        );

    //Shuffle Button Style
    ui->shuffleButton->setText("");
    ui->shuffleButton->setStyleSheet(
        "QPushButton {"
        " background-color: #7f7f7f;"
        " color: white;"
        " font-weight: bold;"
        " border-radius: 8px;"
        " padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        " background-color: #3f3f3f;"
        "}"
        );

    //Due Date Label Style
    ui->dueDateLabel->setStyleSheet(
        "QLabel {"
        " color: white;"
        " font-weight: bold;"
        "}"
    );

    //Task Name Label Style
    ui->taskNameLabel->setStyleSheet(
        "QLabel {"
        " color: white;"
        " font-weight: bold;"
        "}"
        );

    //Light Mode Button Style
    ui->lightMode->setStyleSheet(
        "QPushButton {"
        " background-color: #2e2e2e;"
        " color: #f0f0f0;"
        " font-weight: bold;"
        " border: 1px solid #555555;"
        " border-radius: 8px;"
        " padding: 6px 12px;"
        "}"
        "QPushButton:hover {"
        " background-color: #3c3c3c;"
        "}"
        "QPushButton:pressed {"
        " background-color: #4a4a4a;"
        "}"
        );

    //Volume Label Style
    ui->volumeLabel->setStyleSheet(
        "color: white;"
        "font-weight: bold;"
    );

    //Now Playing Label Style
    QUrl currentSongUrl = playlist[currentSongIndex];
    QString fileName = currentSongUrl.fileName();
    fileName.chop(4);
    fileName.replace('_', ' ');
    ui->nowPlayingLabel->setText("Now Playing: " + fileName);
    ui->nowPlayingLabel->setStyleSheet(
        " QLabel {"
        " color: white;"
        " font-weight: bold;"
        "}"
    );
}

void MainWindow::handleMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if(status == QMediaPlayer::EndOfMedia) {
        on_nextSongButton_clicked();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Add Tasks
void MainWindow::on_addButton_clicked() {
    QString taskText = ui->taskInput->text();
    QDate dueDate = ui->dueDate->date();
    if(taskText.isEmpty()) {
        return;
    }
    QString fullTask = QString("%1 (Due: %2)")
                           .arg(taskText)
                           .arg(dueDate.toString("yyyy-MM-dd"));
    ui->taskList->addItem(fullTask);
    ui->taskInput->clear();
}

//Delete Tasks
void MainWindow::on_deleteButton_clicked() {
    QListWidgetItem *item = ui->taskList->currentItem();
    if(item) {
        ui->taskList->takeItem(ui->taskList->row(item));
        delete item;
    }
}

//Strike-Through Done Tasks
void MainWindow::on_taskList_itemDoubleClicked(QListWidgetItem *item) {
    QFont font = item->font();
    bool isDone = font.strikeOut();

    font.setStrikeOut(!isDone);
    item->setFont(font);
}

//Save Tasks to File
void MainWindow::on_saveButton_clicked() {
    QString filePath = QFileDialog::getSaveFileName(
        this,
        tr("Save Tasks"),
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
        tr("Task Files (*.txt);;All Files (*)")
    );

    if(filePath.isEmpty()) return;

    if(!filePath.endsWith(".txt", Qt::CaseInsensitive)) {
        filePath += ".txt";
    }

        QFile file(filePath);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Could not open file for writing:";
            return;
        }
        QTextStream out(&file);
        for(int i = 0; i < ui->taskList->count(); i++) {
            QListWidgetItem *item = ui->taskList->item(i);
            QString text = item->text();
            bool done = item->font().strikeOut();
            out << (done ? "1" : "0") << "\t" << text << "\n";
        }
        file.close();
        qDebug() << "Tasks saved.";
    }

//Load Tasks from File
void MainWindow::on_loadButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Load Tasks"),
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
        tr("Task Files (*.txt);;All Files (*)")
    );

    if(filePath.isEmpty()) return;

    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open tasks.txt for reading";
        return;
    }
    ui->taskList->clear();

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if(!line.isEmpty()) {
            QStringList parts = line.split("\t");
            if(parts.size() == 2) {
                bool done = (parts[0] == "1");
                QString text = parts[1];

                QListWidgetItem *item = new QListWidgetItem(text);
                QFont font = item->font();
                font.setStrikeOut(done);
                item->setFont(font);

                ui->taskList->addItem(item);
            }
        }
    }
    file.close();
    qDebug() << "Tasks loaded from:" << filePath;
}

//Switch Between Light Mode and Dark Mode
void MainWindow::on_lightMode_clicked() {

    //Light Mode Styling
    if(isDarkMode) {
        QIcon darkModeIcon(":/resources/icons/darkMode.png");
        ui->lightMode->setIcon(darkModeIcon);
        ui->lightMode->setIconSize(QSize(20,20));

        //Main Window
        this->setStyleSheet(
            "QMainWindow {"
            " background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            " stop:0 #d3d3d3, stop:1 #FFFFFF);"
            "}"
            );

        //Task List
        ui->taskList->setStyleSheet(
            "QListWidget {"
            " background-color: #f5f5f5;"
            " color: #222222;"
            " border: 1px solid #cccccc;"
            " font-size: 16px;"
            "}"
            "QListWidget::item:selected {"
            " background-color: #d0ebff;"
            " color: #000000;"
            "}"
            );

        //Task Input
        ui->taskInput->setStyleSheet(
            "QLineEdit {"
            " background-color: #f0f0f0;"
            " color: black;"
            " border: 1px solid #c0c0c0;"
            " border-radius: 5px;"
            " padding: 4px;"
            "}"
            "QLineEdit:focus {"
            " border: 1px solid #808080;"
            "}"
            );

        //Due Date Input Style
        ui->dueDate->setStyleSheet(
            "QDateEdit {"
            " background-color: #f0f0f0;"
            " color: black;"
            " border: 1px solid #c0c0c0;"
            " border-radius: 5px;"
            " padding: 4px;"
            "}"
            "QDateEdit::drop-down {"
            " subcobtrol-origin: padding;"
            " subcontrol-position: top right;"
            " width: 20px;"
            " border-left: 1px solid #c0c0c0;"
            "}"
        );

        //Light Mode Button Style
        ui->lightMode->setStyleSheet(
            "QPushButton {"
            " background-color: #4a4a4a;"
            " border: 1px solid #666666;"
            " border-radius: 8px;"
            " padding: 6px 12px;"
            "}"
            "QPushButton:hover {"
            " background-color: #5c5c5c;"
            "}"
            "QPushButton:pressed {"
            " background-color: #3a3a3a;"
            "}"
            );
        //Volume Label
        ui->volumeLabel->setStyleSheet(
            "color: black;"
            );

        //Task Name Label
        ui->taskNameLabel->setStyleSheet(
            "color: black;"
            );

        //Due Date Label
        ui->dueDateLabel->setStyleSheet(
            "color: black;"
            );

        //Volume Slider
        ui->volumeSlider->setStyleSheet(
            "QSlider::groove:horizontal {"
            " border: 1px solid #999999;"
            " height: 6px;"
            " background: #222222;"
            " margin: 0px;"
            " border-radius: 3px;"
            "}"
            "QSlider::handle:horizontal {"
            " background: #ffffff;"
            " border: 1px solid #5c5c5c;"
            " width: 12px;"
            " margin: -5px 0;"
            " border-radius: 6px;"
            "}"
            );

        //Now Playing Label
        ui->nowPlayingLabel->setStyleSheet(
            " QLabel {"
            " color: black;"
            " font-weight: bold;"
            "}"
            );

    //Dark Mode Styling
    } else {
        QIcon lightModeIcon(":/resources/icons/lightMode.png");
        ui->lightMode->setIcon(lightModeIcon);
        ui->lightMode->setIconSize(QSize(20,20));

        //Main Window
        this->setStyleSheet(
            "QMainWindow {"
            " background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            " stop:0 #2a2a2a, stop:1 #000000);"
            "}"
        );

        //Task List
        ui->taskList->setStyleSheet(
            "QListWidget {"
            " background-color: #1e1e1e;"
            " color: #ffffff;"
            " border: 1px solid #444444;"
            " font-size: 16px;"
            "}"
            "QListWidget::item:selected {"
            " background-color: #3a3a3a;"
            " color: #ffffff;"
            "}"
            );

        //Task Input Style
        ui->taskInput->setStyleSheet(
            "QLineEdit {"
            " background-color: #3a3a3a;"
            " color: white;"
            " border: 1px solid #5a5a5a;"
            " border-radius: 5px;"
            " padding: 4px;"
            "}"
            "QLineEdit:focus {"
            " border: 1px solid #a0a0a0;"
            "}"
            );

        //Due Date Input Style
        ui->dueDate->setStyleSheet(
            "QDateEdit {"
            " background-color: #3a3a3a;"
            " color: white;"
            " border: 1px solid #5a5a5a;"
            " border-radius: 5px;"
            " padding: 4px;"
            "}"
            "QDateEdit::drop-down {"
            " subcobtrol-origin: padding;"
            " subcontrol-position: top right;"
            " width: 20px;"
            " border-left: 1px solid #5a5a5a;"
            "}"
        );

        //Light Mode Button Style
        ui->lightMode->setStyleSheet(
            "QPushButton {"
            " background-color: #2e2e2e;"
            " border: 1px solid #555555;"
            " border-radius: 8px;"
            " padding: 6px 12px;"
            "}"
            "QPushButton:hover {"
            " background-color: #3c3c3c;"
            "}"
            "QPushButton:pressed {"
            " background-color: #4a4a4a;"
            "}"
            );

        //Volume Label
        ui->volumeLabel->setStyleSheet(
            "color: white;"
            );

        //Task Name Label
        ui->taskNameLabel->setStyleSheet(
            "color: white;"
            );

        //Due Date Label
        ui->dueDateLabel->setStyleSheet(
            "color: white;"
            );

        //Volume Slider
        ui->volumeSlider->setStyleSheet(
            "QSlider::groove:horizontal {"
            " border: 1px solid #444444;"
            " height: 6px;"
            " background: #d3d3d3;"
            " margin: 0px;"
            " border-radius: 3px;"
            "}"
            "QSlider::handle:horizontal {"
            " background: #ffffff;"
            " border: 1px solid #888888;"
            " width: 12px;"
            " margin: -5px 0;"
            " border-radius: 6px;"
            "}"
            );

        //Now Playing Label Style
        ui->nowPlayingLabel->setStyleSheet(
            " QLabel {"
            " color: white;"
            " font-weight: bold;"
            "}"
            );
    }
    isDarkMode = !isDarkMode;
}

//Change Volume w/Slider
void MainWindow::on_volumeSlider_valueChanged(int value) {
    if(player) {
        audioOutput->setVolume(value / 100.0);
    }
}

//Pause or Play Music
void MainWindow::on_pausePlayButton_clicked()
{
    QIcon playIcon(":/resources/icons/Play.png");
    QIcon pauseIcon(":/resources/icons/Pause.png");
    if(player->isPlaying()) {
        player->pause();
        ui->pausePlayButton->setIcon(playIcon);
        ui->pausePlayButton->setIconSize(QSize(20,20));
    } else {
        player->play();
        ui->pausePlayButton->setIcon(pauseIcon);
        ui->pausePlayButton->setIconSize(QSize(20,20));
    }
}

//Go to Previous Song
void MainWindow::on_previousSongButton_clicked()
{
    if(playlist.isEmpty()) return;

    if(shuffleOn) {
        if(!shuffleHistory.isEmpty()) {
            currentSongIndex = shuffleHistory.pop();
        }
    } else {
        currentSongIndex = (currentSongIndex - 1 + playlist.size()) % playlist.size();
    }
    QUrl currentSongUrl = playlist[currentSongIndex];
    QString fileName = currentSongUrl.fileName();
    fileName.chop(4);
    fileName.replace('_', ' ');
    ui->nowPlayingLabel->setText("Now Playing: " + fileName);

    qDebug() << "Previous Song Index:" << currentSongIndex;
    player->setSource(playlist[currentSongIndex]);
    player->play();
}

//Go to Next Song
void MainWindow::on_nextSongButton_clicked()
{
    if(playlist.isEmpty()) return;

    if(shuffleOn) {
        shuffleHistory.push(currentSongIndex);
        int newIndex;
        do {
            newIndex = QRandomGenerator::global()->bounded(playlist.size());
        } while (newIndex == currentSongIndex && playlist.size() > 1);

        currentSongIndex = newIndex;
    } else {
        currentSongIndex = (currentSongIndex + 1) % playlist.size();
    }
    QUrl currentSongUrl = playlist[currentSongIndex];
    QString fileName = currentSongUrl.fileName();
    fileName.chop(4);
    fileName.replace('_', ' ');
    ui->nowPlayingLabel->setText("Now Playing: " + fileName);

    qDebug() << "Next Song Index:" << currentSongIndex;
    player->setSource(playlist[currentSongIndex]);
    player->play();
}

//Shuffle the Songs
void MainWindow::on_shuffleButton_clicked()
{
    QIcon shuffleOffIcon(":/resources/icons/shuffleOff.png");
    QIcon shuffleOnIcon(":/resources/icons/shuffleOn.png");

    shuffleOn = !shuffleOn;

    if(shuffleOn) {
        ui->shuffleButton->setIcon(shuffleOnIcon);
        shuffleHistory.clear();
    } else {
        ui->shuffleButton->setIcon(shuffleOffIcon);
    }

    ui->shuffleButton->setIconSize(QSize(20,20));
}

