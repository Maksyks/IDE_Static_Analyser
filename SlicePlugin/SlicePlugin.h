#pragma once
#include <QObject>
#include <QWidget>
#include "IPluginInterface.h"

class SlicePlugin : public QObject, public IPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IPluginInterface_iid FILE "SlicePlugin.json")
    Q_INTERFACES(IPluginInterface)

public:
    QString pluginName() const override { return "Сделать срез"; }
    QString pluginDescription() const override { return "Вырезает первые N строк"; }

    QString process(const QString &input, QWidget *parent) override;
private:
    // Функция для выбора критерия: ввод вручную или из файла
    QString askCriterion(QWidget *parent);

};
