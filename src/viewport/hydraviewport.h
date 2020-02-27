#ifndef HYDRAVIEWPORT_H
#define HYDRAVIEWPORT_H

#include <iostream>
#include <fstream>
#include <string>

#include <QtQuick/QQuickFramebufferObject>


class HydraViewport : public QQuickFramebufferObject
{
    Q_OBJECT

    public:
        HydraViewport(QQuickItem* parent = nullptr);
        ~HydraViewport();

        QQuickFramebufferObject::Renderer* createRenderer() const override;
    private:
};

#endif // HYDRAVIEWPORT_H
