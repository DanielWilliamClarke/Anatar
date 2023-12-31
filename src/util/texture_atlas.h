#ifndef TEXTURE_ATLAS
#define TEXTURE_ATLAS

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

#include "i_texture_atlas.h"

class TextureAtlas: public ITextureAtlas
{
public:
	TextureAtlas() = default;
	~TextureAtlas() override = default;

	virtual std::shared_ptr<ITextureAtlas> AddTexture(const std::string& tag, const std::string& texturePath) override;
	virtual std::shared_ptr<sf::Texture> GetTexture(const std::string& tag) const override;

private:
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
};

#endif