/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileMapParser.h"

#include <tinyxml2/tinyxml2.h>
#include <vector>

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
    : helper_(std::make_shared<ParseHelperImpl>())
    , tileService_(std::make_unique<TileServiceImpl>(
          std::make_unique<TmxParserImpl>(helper_), std::make_unique<TsxParserImpl>(helper_),
          std::make_unique<TileSetFactory>(), std::make_unique<Util::ByteStreamFactory>()))
{}

TileMapParser::~TileMapParser() = default;

TileMapData TileMapParser::Run(const std::string& fileName)
{
    LOG_TMXINFO("Parse %s", fileName.c_str());
    LOG_TMXINFO("Start parse fileName %s", fileName.c_str());
    TileMapData tileMapData;

    if (tileService_->Parse(fileName)) {
        tileMapData.mapProperties_ = tileService_->ReadMapProperties();
        auto tmxDir = Util::GetHead(fileName);
        tileMapData.tileSets_ = tileService_->ReadTileSets(tmxDir);
        tileMapData.layers_ = tileService_->ReadLayers();
        tileMapData.objectGroups_ = tileService_->ReadObjectGroups();
    }
    else {
        LOG_TMXERROR("Could not load %s", fileName.c_str());
    }

    LOG_TMXINFO("End parse fileName %s", fileName.c_str());

    return tileMapData;
}

}  // namespace Tile

}  // namespace FA
