/*==========================================================
* D2Ex2
* https://github.com/lolet/D2Ex2
* ==========================================================
* Copyright (c) 2011-2014 Bartosz Jankowski
* SlashDiablo-Tools Modifications: Copyright (C) 2017 Mir Drualga
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
* ==========================================================
*/

#include "D2HDInventory.h"
#include "../D2Ptrs.h"

void __stdcall D2HD::Inventory::getBeltPos(int nIndex, int nMode, BeltBox *out, int nBox) // Wrapper on D2Common.Ordinal10689
{
    int w, h, panelsize, xpos;

    D2HD::getModeParams(nMode, &w, &h);


    if (nMode < 2) {
        xpos = 178;
        panelsize = 310;
    } else {
        xpos = 258;
        panelsize = 470;
    }
    /*[         Width        ]
    [   310  ]
    ( ) *  =====....=  * ( )
    xpos + panelsize / 2
    */
    out->boxLeft = ((w / 2) - (panelsize / 2) + xpos) + (31 * (nBox % 4));
    out->boxRight = out->boxLeft + 29;
    out->boxBottom = (h - 9) - (33 * (nBox / 4));
    out->boxTop = out->boxBottom - 29;
}

// Why the hell Blizzard put in .txts the UI stuff?!
void __stdcall D2HD::Inventory::getBeltsTxtRecord(int nIndex, int nMode, BeltsTxt *out) // Wrapper on D2Common.Ordinal10370
{
    //TODO: Don't make this const hardcoded
    const int nBeltBoxesTbl[] = { 12, 8, 4, 16, 8, 12, 16 };

    out->dwNumBoxes = nBeltBoxesTbl[nIndex % 7];

    for (int i = 0; (unsigned int)i < out->dwNumBoxes; ++i) {
        D2HD::Inventory::getBeltPos(nIndex, nMode, &out->hBox[i], i);
    }

}

void __stdcall D2HD::Inventory::getInventorySize(int nRecord, int nScreenMode, InventorySize *pOut) // Wrapper on D2Common.Ordinal10770
{
    int xBottom, xTop;
    if (nScreenMode < 3) // Legacy support
    {
        if (nScreenMode == 2)
            nScreenMode = 1;

        InventoryTxt* pTxt = &(*D2COMMON_InventoryTxt)[nRecord + (nScreenMode * 16)];

        pOut->left = pTxt->Inventory.left;
        pOut->right = pTxt->Inventory.right;
        pOut->top = pTxt->Inventory.top;
        pOut->bottom = pTxt->Inventory.bottom;
    } else {
        InventoryTxt* pTxt = &(*D2COMMON_InventoryTxt)[nRecord];

        int xLeft = -1;
        int xRight = -1;


        if (nRecord == INV_REC_HIRELING) {
            pTxt->Grid.left = 0;
            pTxt->Grid.right = 321;
            pTxt->Grid.top = 0;
            pTxt->Grid.bottom = 441;

        }

        if (pTxt->Grid.left > 300) {
            xLeft = ((pTxt->Inventory.left - 320) + (*D2CLIENT_ScreenSizeX / 2));
            xRight = ((pTxt->Inventory.right - 320) + (*D2CLIENT_ScreenSizeX / 2));
        } else {
            xLeft = ((*D2CLIENT_ScreenSizeX / 2) - 320) + pTxt->Inventory.left;
            xRight = ((*D2CLIENT_ScreenSizeX / 2) - 320) + pTxt->Inventory.right;
        }
        xTop = ((*D2CLIENT_ScreenSizeY / 2) - 240) + pTxt->Inventory.top;
        xBottom = xTop + pTxt->Inventory.bottom - pTxt->Inventory.top; //  (*D2Vars.D2CLIENT_ScreenHeight - (480 - pTxt->Inventory.dwBottom));

        pOut->left = xLeft;
        pOut->right = xRight;
        pOut->top = xTop;
        pOut->bottom = xBottom;
    }
}

void __stdcall D2HD::Inventory::getInventoryGrid(int nRecord, int nScreenMode, InventoryGrid *pOut) // Wrapper on D2Common.Ordinal10964
{
    if (nScreenMode < 3) // Legacy support
    {
        if (nScreenMode == 2)
            nScreenMode = 1;

        InventoryTxt* pTxt = &(*D2COMMON_InventoryTxt)[nRecord + (nScreenMode * 16)];

        pOut->nGridX = pTxt->Inventory.nGridX;
        pOut->nGridY = pTxt->Inventory.nGridY;
        pOut->left = pTxt->Grid.left;
        pOut->right = pTxt->Grid.right;
        pOut->top = pTxt->Grid.top;
        pOut->bottom = pTxt->Grid.bottom;
        pOut->nGridWidth = pTxt->Grid.nWidth;
        pOut->nGridHeight = pTxt->Grid.nHeight;
    } else {
        InventoryTxt* pTxt = &(*D2COMMON_InventoryTxt)[nRecord];
        int xLeft = -1;
        int xRight = -1;
        if (pTxt->Grid.left > 300) {
            xLeft = pTxt->Grid.left == -1 ? -1 : ((pTxt->Grid.left - 320) + (*D2CLIENT_ScreenSizeX / 2));
            xRight = pTxt->Grid.right == -1 ? -1 : ((pTxt->Grid.right - 320) + (*D2CLIENT_ScreenSizeX / 2));
        } else {
            xLeft = ((*D2CLIENT_ScreenSizeX / 2) - 320) + pTxt->Grid.left;
            xRight = ((*D2CLIENT_ScreenSizeX / 2) - 320) + pTxt->Grid.right;
        }

        int xTop = pTxt->Grid.top == -1 ? -1 : ((*D2CLIENT_ScreenSizeY / 2) - 240) + pTxt->Grid.top;
        int xBottom = pTxt->Grid.bottom == -1 ? -1 : xTop + (pTxt->Grid.bottom - pTxt->Grid.top);  // (*D2Vars.D2CLIENT_ScreenHeight - (480 - pTxt->Grid.dwBottom));

        pOut->nGridX = pTxt->Inventory.nGridX;
        pOut->nGridY = pTxt->Inventory.nGridY;
        pOut->left = xLeft;
        pOut->right = xRight;
        pOut->top = xTop;
        pOut->bottom = xBottom;
        pOut->nGridWidth = pTxt->Grid.nWidth;
        pOut->nGridHeight = pTxt->Grid.nHeight;
    }

}

void __stdcall D2HD::Inventory::getInventoryField(int nRecord, int nScreenMode, InventoryLayout *pOut, int nField) // Wrapper on D2Common.Ordinal10441
{
    if (nScreenMode < 3) // Legacy support
    {
        if (nScreenMode == 2)
            nScreenMode = 1;
        InventoryTxt* pTxt = &(*D2COMMON_InventoryTxt)[nRecord + (nScreenMode * 16)];
        InventoryLayout * pLayout = &pTxt->hItem[nField];

        pOut->left = pLayout->left;
        pOut->right = pLayout->right;
        pOut->top = pLayout->top;
        pOut->bottom = pLayout->bottom;
        pOut->nWidth = pLayout->nWidth;
        pOut->nHeight = pLayout->nHeight;
    } else {
        InventoryTxt* pTxt = &(*D2COMMON_InventoryTxt)[nRecord];
        InventoryLayout * pLayout = &pTxt->hItem[nField];

        int xLeft = -1;
        int xRight = -1;

        if (pTxt->Grid.left > 300) {
            xLeft = pLayout->left == -1 ? -1 : ((pLayout->left - 320) + (*D2CLIENT_ScreenSizeX / 2));
            xRight = pLayout->right == -1 ? -1 : ((pLayout->right - 320) + (*D2CLIENT_ScreenSizeX / 2));
        } else {
            xLeft = ((*D2CLIENT_ScreenSizeX / 2) - 320) + pLayout->left;
            xRight = ((*D2CLIENT_ScreenSizeX / 2) - 320) + pLayout->right;
        }

        int xTop = pLayout->top == -1 ? -1 : ((*D2CLIENT_ScreenSizeY / 2) - 240) + pLayout->top;
        int xBottom = pLayout->bottom == -1 ? -1 : xTop + (pLayout->bottom - pLayout->top);    //(*D2Vars.D2CLIENT_ScreenHeight - (480 - pLayout->dwBottom));

        pOut->left = xLeft;
        pOut->right = xRight;
        pOut->top = xTop;
        pOut->bottom = xBottom;
        pOut->nWidth = pLayout->nWidth;
        pOut->nHeight = pLayout->nHeight;
    }

}
