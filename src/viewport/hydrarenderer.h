#ifndef HYDRARENDERER_H
#define HYDRARENDERER_H

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLFramebufferObject>
#include <QQuickFramebufferObject>

#include "usd_helper.h"


class HydraRenderer : public QQuickFramebufferObject::Renderer
{
    public:
        HydraRenderer();
        ~HydraRenderer();

        QOpenGLFramebufferObject* createFramebufferObject(
            const QSize& size) override;
        void render() override;
        void synchronize(QQuickFramebufferObject* item) override;
    private:
        friend class HydraViewport;
        // Exposes all the necessary functions to deal with OpenGL from the 4.5 standard.
        QOpenGLFunctions_4_5_Core* _openGL = 0;
        // The size of the QOpenGLFramebufferObject.
        QSize _size;
        // The aspect ratio of the QOpenGLFramebufferObject.
        float _aspectRatio;
};

#endif // HYDRARENDERER_H
