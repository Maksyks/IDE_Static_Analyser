#pragma once

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QToolBar>
#include <QMenu>
#include <QList>
#include <QPluginLoader>
#include "IPluginInterface.h"
#include "CodeEditor.h"

class IDE : public QMainWindow
{
    Q_OBJECT

public:
    explicit IDE(QWidget *parent = nullptr);
    ~IDE() override = default;

private slots:
    void openSourceFile();
    //void applyPlugin();

private:
    void setupUi();
    void loadPlugins();

    CodeEditor *leftEditor;
    CodeEditor *rightEditor;
    QToolBar         *mainToolBar;
    QMenu            *fileMenu;
    QMenu            *pluginsMenu;
    QMenu            *projectMenu;
    QMenu            *settingsMenu;
    QList<IPluginInterface*> plugins;
    IPluginInterface         *currentPlugin = nullptr;
};
