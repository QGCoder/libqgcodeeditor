#ifndef _QGCODE_EDITOR_WIDGET_H
#define _QGCODE_EDITOR_WIDGET_H

#include <QtDesigner>
#include <qplugin.h>

class QGCodeEditorWidget : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")

public:
    explicit QGCodeEditorWidget(QObject *parent = 0);

    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface*> m_widget;
};

#endif
