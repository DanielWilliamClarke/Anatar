#include "texture_atlas.h"

std::shared_ptr<ITextureAtlas> TextureAtlas::AddTexture(std::string tag, std::string texturePath)
{
	sf::Image image;
	image.loadFromFile(texturePath);
	auto backgroundColor = image.getPixel(0, 0);
	image.createMaskFromColor(backgroundColor);
	auto texture = std::make_shared<sf::Texture>();	
	texture->loadFromImage(image);
	this->textures[tag] = texture;
	return shared_from_this();
}

std::shared_ptr<sf::Texture> TextureAtlas::GetTexture(std::string tag) const
{
	return this->textures.at(tag);
}