#pragma once

#include <QtPlugin>
#include <QString>

class IPluginInterface
{
public:
    virtual ~IPluginInterface() {}

    // Название и описание плагина
    virtual QString pluginName() const = 0;
    virtual QString pluginDescription() const = 0;

    // Существующий метод: ввод критерия вручную
    virtual QString process(const QString &input, QWidget *parent) = 0;

    // Новый метод: срез по указанному критерию (line:variable)
    virtual QString process(const QString &input,
                            int lineNumber,
                            const QString &variable,
                            QWidget *parent) {
        Q_UNUSED(lineNumber);
        Q_UNUSED(variable);
        // По умолчанию — вызов старого метода, чтобы сохранить совместимость
        return process(input, parent);
    }
};

#define IPluginInterface_iid "com.myide.plugins.IPluginInterface"
Q_DECLARE_INTERFACE(IPluginInterface, IPluginInterface_iid)
