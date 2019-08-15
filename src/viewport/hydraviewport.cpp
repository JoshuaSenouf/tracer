#include "hydraviewport.h"
#include "hydrarenderer.h"


HydraViewport::HydraViewport(QQuickItem* parent) :
    QQuickFramebufferObject(parent)
{
    // Need to see the render produced by Hydra correctly.
    setMirrorVertically(true);
}

HydraViewport::~HydraViewport()
{

}

QQuickFramebufferObject::Renderer* HydraViewport::createRenderer() const
{
    return new HydraRenderer();
}
