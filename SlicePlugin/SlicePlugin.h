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
    // Перегрузка для вызова из контекстного меню
    QString process(const QString &input,
                    int lineNumber,
                    const QString &variable,
                    QWidget *parent) override;

    // Вспомогательный метод с общей логикой по заданному критерию
    QString processWithCriterion(const QString &input,
                                 const QString &criterion,
                                 QWidget *parent);

private:
    // Функция для выбора критерия: ввод вручную или из файла
    QString askCriterion(QWidget *parent);

};
