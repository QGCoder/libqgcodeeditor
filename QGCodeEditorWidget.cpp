#include "QGCodeEditorWidget.h"
#include "QGCodeEditorPlugin.h"

QGCodeEditorWidget::QGCodeEditorWidget(QObject *parent)
    : QObject(parent)
{
    m_widget.append(new QGCodeEditorPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> QGCodeEditorWidget::customWidgets() const
{
    return m_widget;
}

