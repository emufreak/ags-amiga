//=============================================================================
//
// Adventure Game Studio (AGS)
//
// Copyright (C) 1999-2011 Chris Jones and 2011-20xx others
// The full list of copyright holders can be found in the Copyright.txt
// file, which is part of this source code distribution.
//
// The AGS source code is provided under the Artistic License 2.0.
// A copy of this license can be found in the file License.txt and at
// http://www.opensource.org/licenses/artistic-license-2.0.php
//
//=============================================================================
#include "data/scriptgen.h"
#include "data/room_utils.h"

namespace AGS
{
namespace DataUtil
{

//-----------------------------------------------------------------------------
// Room.ash
//-----------------------------------------------------------------------------

String MakeRoomScriptHeader(const RoomScNames &data)
{
    String header;
    // Room Object names
    for (const auto &obj : data.ObjectNames)
    {
        if (!obj.IsEmpty())
        {
            header.Append("import Object ");
            header.Append(obj);
            header.Append(";\n");
        }
    }
    // Hotspot names
    for (const auto &hot : data.HotspotNames)
    {
        if (!hot.IsEmpty())
        {
            header.Append("import Hotspot ");
            header.Append(hot);
            header.Append(";\n");
        }
    }
    return header;
}

} // namespace DataUtil
} // namespace AGS
