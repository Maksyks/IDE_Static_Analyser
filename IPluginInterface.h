#pragma once

#include <QtPlugin>
#include <QString>

// Базовый интерфейс плагина.
class IPluginInterface
{
public:
    virtual ~IPluginInterface() {}

    virtual QString pluginName() const = 0;

    virtual QString pluginDescription() const = 0;

    virtual QString process(const QString &input, QWidget *parent) = 0;
};

// IID для регистрации в Qt
#define IPluginInterface_iid "com.myide.plugins.IPluginInterface"
Q_DECLARE_INTERFACE(IPluginInterface, IPluginInterface_iid)
