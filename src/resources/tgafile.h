/*
 * Copyright � 2020 Vsevolod Kremianskii
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "binfile.h"

#include "../render/texture.h"

namespace reone {

namespace resources {

class TgaFile : public BinaryFile {
public:
    TgaFile(const std::string &resRef, render::TextureType type);
    std::shared_ptr<render::Texture> texture() const;

private:
    enum class ImageType {
        RGBA = 2,
        Grayscale = 3
    };

    std::string _resRef;
    render::TextureType _texType { render::TextureType::Diffuse };
    ImageType _imageType { ImageType::RGBA };
    int _width { 0 };
    int _height { 0 };
    std::shared_ptr<render::Texture> _texture;

    void doLoad() override;
    void loadTexture();
};

} // namespace resources

} // namespace reone
