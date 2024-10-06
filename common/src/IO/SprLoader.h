/*
 Copyright (C) 2021 Kristian Duske

 This file is part of TrenchBroom.

 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "IO/EntityModelLoader.h"

#include <filesystem>
#include <string>

namespace tb::asset
{
class Palette;
}

namespace tb::IO
{
class File;
class FileSystem;
class Reader;

class SprLoader : public EntityModelLoader
{
private:
  std::string m_name;
  const Reader& m_reader;
  const asset::Palette& m_palette;

public:
  SprLoader(std::string name, const Reader& reader, const asset::Palette& palette);

  static bool canParse(const std::filesystem::path& path, Reader reader);

  Result<asset::EntityModelData> load(Logger& logger) override;
};

} // namespace tb::IO
