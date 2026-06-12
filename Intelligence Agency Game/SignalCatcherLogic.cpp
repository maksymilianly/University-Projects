#include "SignalCatcherLogic.h"

#include "Assets.h"
#include "Config.h"


SignalCatcherLogic::SignalCatcherLogic(Assets& assets, Config& config)
{
    auto& texCatcher = assets.textures.at("target_catcher");
    auto catcherData = config.spritesData.at("target_catcher");

    catcherRadius = 1000.0f;//texCatcher.getSize().x / 2.0f * catcherData.scale.x;
    config.loadIn("target_catcher_speed", catcherMoveSpeed, 1.0f);
    

    auto radarData = config.spritesData.at("target_radar_bounds");
    auto texSize = assets.textures.at("target_radar_bounds").getSize();

    radarBounds = sf::FloatRect(radarData.position,
        { static_cast<float>(texSize.x * radarData.scale.x),
          static_cast<float>(texSize.y * radarData.scale.y) });

    catcherPos.x = radarBounds.position.x + (radarBounds.size.x / 2.0f);
    catcherPos.y = radarBounds.position.y + (radarBounds.size.y / 2.0f);
}

void SignalCatcherLogic::move(float dt, sf::Vector2f vector)
{
    catcherPos.x = catcherPos.x + (vector.x * catcherMoveSpeed * dt);
    catcherPos.y = catcherPos.y + (vector.y * catcherMoveSpeed * dt);
}

void SignalCatcherLogic::compareWithRadarBounds()
{
    if (catcherPos.x - catcherRadius < radarBounds.position.x) {
        catcherPos.x = radarBounds.position.x + catcherRadius; 
    }
    else if (catcherPos.x + catcherRadius > radarBounds.position.x + radarBounds.size.x) {
        catcherPos.x = radarBounds.position.x + radarBounds.size.x - catcherRadius; 
    }
    if (catcherPos.y - catcherRadius < radarBounds.position.y) {
        catcherPos.y = radarBounds.position.y + catcherRadius;
    }
    else if (catcherPos.y + catcherRadius > radarBounds.position.y + radarBounds.size.y) {
        catcherPos.y = radarBounds.position.y + radarBounds.size.y - catcherRadius;
    }
}
