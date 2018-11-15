#include "scenemanager.h"


SceneManager::SceneManager()
{

}


SceneManager::SceneManager(const std::string& scenePath)
{
    loadScene(scenePath);
}


int SceneManager::loadScene(const std::string& scenePath)
{
    if (std::size_t(scenePath.rfind(std::string(".usd")) != std::string::npos)
                || std::size_t(scenePath.rfind(std::string(".usda")) != std::string::npos)
                || std::size_t(scenePath.rfind(std::string(".usdc")) != std::string::npos))
    {
        if (!usdScene.loadSceneFile(scenePath))
            return false;
    }
    else
    {
        std::cout << "ERROR - The following file is not an USD scene: " << scenePath << std::endl;
        return false;
    }
}


USDScene& SceneManager::getUSDScene()
{
    return usdScene;
}
