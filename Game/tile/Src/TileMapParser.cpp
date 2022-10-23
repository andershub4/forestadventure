/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileMapParser.h"

#include <tinyxml2/tinyxml2.h>

#include "ByteStreamFactory.h"
#include "Folder.h"
#include "ParseHelper.h"
#include "TileMapData.h"
#include "TileService.h"
#include "TileSetFactory.h"
#include "TmxLogging.h"
#include "TmxParser.h"
#include "TsxParser.h"

namespace FA {

namespace Tile {

TileMapParser::TileMapParser()
    : helper_(std::make_shared<ParseHelper<tinyxml2::XMLElement, tinyxml2::XMLError>>())
    , tileService_(std::make_unique<TileService<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError>>(
          std::make_unique<TmxParser<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError>>(helper_),
          std::make_unique<TsxParser<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError>>(helper_),
          std::make_unique<TileSetFactory>(), std::make_unique<ByteStreamFactory>()))
{}

TileMapParser::~TileMapParser() = default;

TileMapData TileMapParser::Run(const std::string& fileName)
{
    LOG_TMXINFO("Parse ", fileName);
    LOG_TMXINFO("Start parse fileName ", fileName);
    TileMapData tileMapData;

    if (tileService_->Parse(fileName)) {
        tileMapData.mapProperties_ = tileService_->ReadMapProperties();
        auto tmxDir = GetHead(fileName);
        tileMapData.tileSets_ = tileService_->ReadTileSets(tmxDir);
        tileMapData.layers_ = tileService_->ReadLayers();
        tileMapData.objectGroups_ = tileService_->ReadObjectGroups();
    }
    else {
        LOG_TMXERROR("Could not load ", fileName);
    }

    LOG_TMXINFO("End parse fileName ", fileName);

    return tileMapData;
}

}  // namespace Tile

}  // namespace FA
