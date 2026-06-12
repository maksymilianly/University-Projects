#include "UILogic.h"

#include "Config.h"
#include "GameState.h"




UILogic::UILogic(Config& config, GameState& state)
{
    shopOpen = false;
    czyPracownicy = false;
}

bool UILogic::checkShopButton(const sf::Vector2f& mousePos, const sf::FloatRect& przycisk)
{


    if (przycisk.contains(mousePos))
    {
        float lewaKrawedz = przycisk.position.x;
        float polowaszerokosc = (przycisk.size.x) / 2.0f;

        if (mousePos.x < (lewaKrawedz + polowaszerokosc))
        {
            shopOpen = !shopOpen;
        }
        else {
            czyPracownicy = !czyPracownicy;
        }
        return true;
    }
    return false;
}
