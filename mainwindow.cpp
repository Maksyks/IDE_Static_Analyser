#include "mainwindow.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QDir>
#include <QAction>
#include <QHBoxLayout>
#include <QApplication>

IDE::IDE(QWidget *parent)
    : QMainWindow(parent)
{
    // Через qmake не создается почему то /plugins
    QString plugDir = QCoreApplication::applicationDirPath() + "/plugins";
    QDir().mkpath(plugDir);

    setupUi();
    loadPlugins();

    this->setMinimumSize(1280, 720);
}

void IDE::setupUi()
{
    // Меню Файл
    fileMenu = menuBar()->addMenu(tr("Файл"));
    fileMenu->addAction(tr("Открыть..."), this, SLOT(openSourceFile()));

    // Меню Плагины
    pluginsMenu = menuBar()->addMenu(tr("Инструменты"));

    //Меню Проект
    projectMenu = menuBar()->addMenu(tr("Проект"));

    //Меню Настройки
    settingsMenu = menuBar()->addMenu(tr("Настройки"));

    // Центральный виджет: два редактора рядом
    QWidget *central = new QWidget(this);
    QHBoxLayout *lay = new QHBoxLayout(central);

    leftEditor  = new CodeEditor;
    rightEditor = new CodeEditor;

    lay->addWidget(leftEditor);
    lay->addWidget(rightEditor);
    setCentralWidget(central);
}

void IDE::openSourceFile()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Открыть исходник"), "", "*.c *.cpp *.h");
    if (fn.isEmpty()) return;

    QFile f(fn);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    leftEditor->setPlainText(f.readAll());
    rightEditor->clear();
}

void IDE::loadPlugins()
{
    QDir pluginsDir(QApplication::applicationDirPath() + "/plugins");
    for (QString fn : pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fn));
        if (auto *plug = qobject_cast<IPluginInterface*>(loader.instance())) {
                plugins.append(plug);
            QAction *act = new QAction(plug->pluginName(), this);
            connect(act, &QAction::triggered, [this, plug](){
                QString in = leftEditor->toPlainText();
                QString out = plug->process(in, this);
                if (!out.isNull())
                    rightEditor->setPlainText(out);
            });
            pluginsMenu->addAction(act);
        }
    }
}

