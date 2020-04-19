﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AuxiliaryFunctionality/qtDebugSwitch.h"

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QAction>
#include <QCloseEvent>
#include <QComboBox>
#include <QCheckBox>

#include "GUI/gamewindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;
    virtual void closeEvent(QCloseEvent* event);
    GameWindow* getGameWindow() const;

private:
    void setUpUI();

    /*  NEW GAME SETUP  */

    QPushButton *startNewGameButton;
    // game setup
    QLabel *playersCountLabel;
    QSpinBox *playersCountSpinBox;
    QLabel *fieldSizeLabel;
    QSpinBox *fieldSizeSpinBox;
    // log
    QLabel *logModeLabel;
    QComboBox *logModeComboBox;
    QCheckBox *logAdvancedModeCheckBox;

    // GAME WINDOW
    GameWindow *gameWindow;

    // PAR
    size_t gameFieldSize{};
    size_t playersCount{};

private slots:
    void on_startNewGameButton_clicked();
    void on_gameWindow_closeEvent();

signals:
    void startNewGameWindow(size_t gameFieldSize, size_t playersCount);
};

#endif // MAINWINDOW_H
