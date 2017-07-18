#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "material.h"


struct RayObject
{
        glm::vec3 origin;
        glm::vec3 direction;

        RayObject(glm::vec3 tempOrigin, glm::vec3 tempDirection) : origin(tempOrigin), direction(tempDirection)
        {

        }
};


struct SphereObject
{
        float radius;

        glm::vec3 position;
        glm::vec3 color;
        glm::vec3 emissiveColor;

        materialType material;
};


#endif // OBJECT_H
