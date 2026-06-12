#include "UIVisual.h"
#include <regex>

#include "Assets.h"
#include "Config.h"
#include "GameState.h"



UIVisual::UIVisual(Assets& assets, Config& config, GameState& state) : Visual(assets, config, "ui_")
, kontoText(assets.mainFont)
, sklepText(assets.mainFont)
, pracownicyText(assets.mainFont)
{
	kontoText.setCharacterSize(30);
	kontoText.setFillColor(sf::Color::Yellow);
	kontoText.setPosition({ config.logicalData.at("ui_bank_posX"), config.logicalData.at("ui_bank_posY") });

	sklepText.setCharacterSize(20);
	sklepText.setFillColor(sf::Color::White);
	sklepText.setPosition({ config.spritesData.at("ui_shop_button").position.x + 30.0f
		,config.spritesData.at("ui_shop_button").position.y + 20.0f });
	sklepText.setString("Rynek \n pracy");

	pracownicyText.setCharacterSize(20);
	pracownicyText.setFillColor(sf::Color::White);
	pracownicyText.setPosition({ config.spritesData.at("ui_shop_button").position.x + 120.0f
		,config.spritesData.at("ui_shop_button").position.y + 20.0f });
	pracownicyText.setString("Pracownicy");

}

void UIVisual::update(GameState& state)
{
	std::string Napis = "Konto: $" + std::to_string(state.getBank());
	kontoText.setString(Napis);
}

void UIVisual::draw(sf::RenderWindow & window)
{
	Visual::draw(window);
	window.draw(kontoText);
}

void UIVisual::drawShopButton(sf::RenderWindow& window, bool czyPracownicy)
{
	if (czyPracownicy) {
		sklepText.setString("Pracownicy");
		pracownicyText.setString("Rynek\npracy");
	}
	else {
		sklepText.setString("Rynek\npracy");
		pracownicyText.setString("Pracownicy");
	}
	window.draw(sklepText);
	window.draw(pracownicyText);
}

void UIVisual::drawDynamic(sf::RenderWindow& window, bool shopOpen, bool czyPracownicy, const std::vector<std::string>& identyfikatory, Assets& assets, Config& config)
{
	if (!shopOpen) return;

	sf::Sprite shop_bg(assets.textures.at("ui_shop_bg"));
	shop_bg.setPosition(config.spritesData.at("ui_shop_bg").position);
	sf::Sprite shop_bounds(assets.textures.at("ui_shop_bounds"));
	sf::Sprite shop_decision_yes(assets.textures.at("ui_shopdecision_yes"));
	shop_decision_yes.setColor({ 0,255,0 });
	sf::Sprite shop_decision_no(assets.textures.at("ui_shopdecision_no"));
	shop_decision_no.setColor({ 255,0,0 });
	sf::Sprite agentIcon(assets.textures.at("ui_agent"));
	sf::Sprite groupIcon(assets.textures.at("ui_group"));

	window.draw(shop_bg);

	float borderX = shop_bg.getGlobalBounds().size.x;
	float startY = 13.5f;
	float odstep = 131.0f;

	sf::Text decisionText(assets.mainFont);
	decisionText.setFillColor(sf::Color::White);

	for (size_t i = 0; i < opisOfert.size(); i++)
	{
		float currentY = startY + (i * odstep);

		shop_bounds.setPosition({ 1920.0f - borderX + 2.5f, currentY });
		window.draw(shop_bounds);

		opisOfert[i].setPosition({ 1920.0f - borderX + 135.0f, currentY + 10.0f });
		window.draw(opisOfert[i]);

		if (!czyPracownicy)
		{
			decisionText.setCharacterSize(26);

			shop_decision_yes.setPosition({ 1920.0f - 107.0f, currentY + 12.0f });
			shop_decision_no.setPosition({ 1920.0f - 107.0f, currentY + 67.0f });
			window.draw(shop_decision_yes);
			window.draw(shop_decision_no);

			decisionText.setString("Kup");
			decisionText.setPosition({ 1920.0f - 101.0f, currentY + 17.0f });
			window.draw(decisionText);

			decisionText.setString("Usun");
			decisionText.setPosition({ 1920.0f - 101.0f, currentY + 72.0f });
			window.draw(decisionText);
		}
		else
		{
			decisionText.setCharacterSize(17);

			shop_decision_yes.setPosition({ 1920.0f - 105.0f, currentY + 12.0f });
			shop_decision_no.setPosition({ 1920.0f - 105.0f, currentY + 67.0f });
			window.draw(shop_decision_yes);
			window.draw(shop_decision_no);

			decisionText.setString("Zadanie");
			decisionText.setPosition({ 1920.0f - 103.0f, currentY + 20.0f });
			window.draw(decisionText);

			decisionText.setString("Sprzedaj");
			decisionText.setPosition({ 1920.0f - 106.0f, currentY + 75.0f });
			window.draw(decisionText);
		}

		if (i < identyfikatory.size())
		{
			if (identyfikatory[i] == "A") {
				agentIcon.setPosition({ 1920.0f - borderX + 30.0f, currentY + 17.5f });
				window.draw(agentIcon);
			}
			else if (identyfikatory[i] == "G") {
				groupIcon.setPosition({ 1920.0f - borderX + 25.0f, currentY + 32.5f });
				window.draw(groupIcon);
			}
		}
	}
}

std::vector<std::string> UIVisual::zaladujDaneSklepu(bool czyPracownicy, GameState& state, Assets& assets)
{
	opisOfert.clear();
	hitboxyKupZadanie.clear();
	hitboxyUsunSprzedaj.clear();

	std::vector<std::string> fragmenty;
	std::vector<std::string> identyfikacja;

	if (assets.textures.count("ui_shop_bg") == 0) return fragmenty;

	const auto& rynek = czyPracownicy ?
		state.getPracownicy() :
		state.getRynekPracy();

	float szerokosc = static_cast<float>(assets.textures.at("ui_shopdecision_yes").getSize().x);
	float wysokosc = static_cast<float>(assets.textures.at("ui_shopdecision_yes").getSize().y);
	float borderX = static_cast<float>(assets.textures.at("ui_shop_bg").getSize().x);

	float startY = 13.5f;
	float odstep = 131.0f;

	for (size_t i = 0; i < rynek.size(); ++i)
	{
		float currentY = startY + (i * odstep);

		hitboxyKupZadanie.push_back(sf::FloatRect({ 1920.0f - 107.0f, currentY + 12.0f }, { szerokosc, wysokosc }));
		hitboxyUsunSprzedaj.push_back(sf::FloatRect({ 1920.0f - 107.0f, currentY + 67.0f }, { szerokosc, wysokosc }));

		sf::Text nowyTekst(assets.mainFont);
		nowyTekst.setCharacterSize(16);
		nowyTekst.setFillColor(sf::Color::White);

		std::string dane = rynek[i]->zwrocDane();

		std::regex pattern(R"([^|]+)");
		auto begin = std::sregex_iterator(dane.begin(), dane.end(), pattern);
		auto end = std::sregex_iterator();

		for (auto it = begin; it != end; ++it) {
			fragmenty.push_back(it->str());
		}

		std::string finalDane = "";
		if (fragmenty.size() > 0) {
			std::string id = fragmenty[0];
			if (id.find("A") != std::string::npos && fragmenty.size() >= 6) {
				finalDane += fragmenty[1] + "\n";
				finalDane += " | Cena: " + fragmenty[2] + "$\n";
				finalDane += " | XP: " + fragmenty[3] + "\n";
				finalDane += " | Suma skills: " + fragmenty[4] + "\n";
				finalDane += " | Preferowana misja: " + fragmenty[5] + "\n";
				identyfikacja.push_back("A");
			}
			else if (id.find("G") != std::string::npos && fragmenty.size() >= 4) {
				finalDane += fragmenty[1] + "\n";
				finalDane += " | Cena: " + fragmenty[2] + "$\n";
				finalDane += " | XP: " + fragmenty[3] + "\n";
				finalDane += " | Suma skills: " + fragmenty[4] + "\n";
				finalDane += " | " + fragmenty[5] + "\n";
				identyfikacja.push_back("G");
			}
		}

		nowyTekst.setString(finalDane);
		opisOfert.push_back(nowyTekst);
		fragmenty.clear();
	}

	return identyfikacja;
}

int UIVisual::sprawdzKlikniecieGora(const sf::Vector2f& mousePos) {
	for (size_t i = 0; i < hitboxyKupZadanie.size(); ++i) {
		if (hitboxyKupZadanie[i].contains(mousePos)) return i;
	}
	return -1;
}

int UIVisual::sprawdzKlikniecieDol(const sf::Vector2f& mousePos) {
	for (size_t i = 0; i < hitboxyUsunSprzedaj.size(); ++i) {
		if (hitboxyUsunSprzedaj[i].contains(mousePos)) return i;
	}
	return -1;
}
