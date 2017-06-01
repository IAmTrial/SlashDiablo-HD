/*
    Many thanks to the creator of D2MultiRes and the person who revealed its source on BlizzHackers.
    In addition, thanks to the creators of D2Ex2 for publicly hosting their own code, which helped
    me double-check whether I was going toward the right direction.
*/

#pragma once

namespace HD {
    void RedrawUILeftPanelBorders_Interception();
    void RedrawUIRightPanelBorders_Interception();
    void DrawUIPanelBackground();
    void DrawUIControlPanel();
    void UnloadCellFiles();
}
