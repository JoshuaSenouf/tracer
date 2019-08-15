#include "hydrarenderer.h"


HydraRenderer::HydraRenderer()
{
    _openGL = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
}

HydraRenderer::~HydraRenderer()
{

}

QOpenGLFramebufferObject* HydraRenderer::createFramebufferObject(
    const QSize& size)
{
    if (_size != size)
    {
        _size = size;
    }

    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    // MSAA
    format.setSamples(0);

    return new QOpenGLFramebufferObject(_size, format);
}

void HydraRenderer::render()
{
    _openGL->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    _openGL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void HydraRenderer::synchronize(QQuickFramebufferObject* item)
{

}
