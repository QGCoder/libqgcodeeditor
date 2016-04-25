#include "QGCodeEditorPlugin.h"

#include <QtPlugin>

QGCodeEditorPlugin::QGCodeEditorPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QGCodeEditorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QGCodeEditorPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QGCodeEditorPlugin::createWidget(QWidget *parent)
{
    return new QGCodeEditor(parent);
}

QString QGCodeEditorPlugin::name() const
{
    return QLatin1String("QGCodeEditor");
}

QString QGCodeEditorPlugin::group() const
{
    return QLatin1String("Custom_Widgets");
}

QIcon QGCodeEditorPlugin::icon() const
{
    return QIcon();
}

QString QGCodeEditorPlugin::toolTip() const
{
    return QLatin1String("");
}

QString QGCodeEditorPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool QGCodeEditorPlugin::isContainer() const
{
    return false;
}

QString QGCodeEditorPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QGCodeEditor\" name=\"QGCodeEditor\">\n</widget>\n");
}

QString QGCodeEditorPlugin::includeFile() const
{
    return QLatin1String("QGCodeEditorPlugin.h");
}

