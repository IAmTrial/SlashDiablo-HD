#include "D2HDInventory.h"
#include "../D2Ptrs.h"

void __stdcall Inventory::GetBeltPos(int nIndex, int nMode, BeltBox *out, int nBox) // Wrapper on D2Common.Ordinal10689
{
    DWORD w, h, panelsize, xpos;

    HD::D2GFX_GetModeParams(nMode, &w, &h);


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
    out->dwBoxLeft = ((w / 2) - (panelsize / 2) + xpos) + (31 * (nBox % 4));
    out->dwBoxRight = out->dwBoxLeft + 29;
    out->dwBoxBottom = (h - 9) - (33 * (nBox / 4));
    out->dwBoxTop = out->dwBoxBottom - 29;
}

// Why the hell Blizzard put in .txts the UI stuff?!
void __stdcall Inventory::GetBeltsTxtRecord(int nIndex, int nMode, BeltsTxt *out) // Wrapper on D2Common.Ordinal10370
{
    //TODO: Don't make this const hardcoded
    const int nBeltBoxesTbl[] = { 12, 8, 4, 16, 8, 12, 16 };

    out->dwNumBoxes = nBeltBoxesTbl[nIndex % 7];

    for (int i = 0; (unsigned int)i < out->dwNumBoxes; ++i) {
        GetBeltPos(nIndex, nMode, &out->hBox[i], i);
    }

}

void __stdcall Inventory::GetInventorySize(int nRecord, int nScreenMode, InventorySize *pOut) // Wrapper on D2Common.Ordinal10770
{
    int xBottom, xTop;
    if (nScreenMode < 3) // Legacy support
    {
        if (nScreenMode == 2)
            nScreenMode = 1;

        InventoryTxt* pTxt = &(*D2COMMON_InventoryTxt)[nRecord + (nScreenMode * 16)];

        pOut->dwLeft = pTxt->Inventory.dwLeft;
        pOut->dwRight = pTxt->Inventory.dwRight;
        pOut->dwTop = pTxt->Inventory.dwTop;
        pOut->dwBottom = pTxt->Inventory.dwBottom;
    } else {
        InventoryTxt* pTxt = &(*D2COMMON_InventoryTxt)[nRecord];

        int xLeft = -1;
        int xRight = -1;


        if (nRecord == INV_REC_HIRELING) {
            pTxt->Grid.dwLeft = 0;
            pTxt->Grid.dwRight = 321;
            pTxt->Grid.dwTop = 0;
            pTxt->Grid.dwBottom = 441;

        }

        if ((int)pTxt->Grid.dwLeft > 300) {
            xLeft = ((pTxt->Inventory.dwLeft - 320) + (*D2CLIENT_ScreenSizeX / 2));
            xRight = ((pTxt->Inventory.dwRight - 320) + (*D2CLIENT_ScreenSizeX / 2));
        } else {
            xLeft = ((*D2CLIENT_ScreenSizeX / 2) - 320) + pTxt->Inventory.dwLeft;
            xRight = ((*D2CLIENT_ScreenSizeX / 2) - 320) + pTxt->Inventory.dwRight;
        }
        xTop = ((*D2CLIENT_ScreenSizeY / 2) - 240) + pTxt->Inventory.dwTop;
        xBottom = xTop + pTxt->Inventory.dwBottom - pTxt->Inventory.dwTop; //  (*D2Vars.D2CLIENT_ScreenHeight - (480 - pTxt->Inventory.dwBottom));

        pOut->dwLeft = xLeft;
        pOut->dwRight = xRight;
        pOut->dwTop = xTop;
        pOut->dwBottom = xBottom;
    }
}

void __stdcall Inventory::GetInventoryGrid(int nRecord, int nScreenMode, InventoryGrid *pOut) // Wrapper on D2Common.Ordinal10964
{
    if (nScreenMode < 3) // Legacy support
    {
        if (nScreenMode == 2)
            nScreenMode = 1;

        InventoryTxt* pTxt = &(*D2COMMON_InventoryTxt)[nRecord + (nScreenMode * 16)];

        pOut->nGridX = pTxt->Inventory.nGridX;
        pOut->nGridY = pTxt->Inventory.nGridY;
        pOut->dwLeft = pTxt->Grid.dwLeft;
        pOut->dwRight = pTxt->Grid.dwRight;
        pOut->dwTop = pTxt->Grid.dwTop;
        pOut->dwBottom = pTxt->Grid.dwBottom;
        pOut->nGridWidth = pTxt->Grid.nWidth;
        pOut->nGridHeight = pTxt->Grid.nHeight;
    } else {
        InventoryTxt* pTxt = &(*D2COMMON_InventoryTxt)[nRecord];
        int xLeft = -1;
        int xRight = -1;
        if (pTxt->Grid.dwLeft > 300) {
            xLeft = pTxt->Grid.dwLeft == -1 ? -1 : ((pTxt->Grid.dwLeft - 320) + (*D2CLIENT_ScreenSizeX / 2));
            xRight = pTxt->Grid.dwRight == -1 ? -1 : ((pTxt->Grid.dwRight - 320) + (*D2CLIENT_ScreenSizeX / 2));
        } else {
            xLeft = ((*D2CLIENT_ScreenSizeX / 2) - 320) + pTxt->Grid.dwLeft;
            xRight = ((*D2CLIENT_ScreenSizeX / 2) - 320) + pTxt->Grid.dwRight;
        }

        int xTop = pTxt->Grid.dwTop == -1 ? -1 : ((*D2CLIENT_ScreenSizeY / 2) - 240) + pTxt->Grid.dwTop;
        int xBottom = pTxt->Grid.dwBottom == -1 ? -1 : xTop + (pTxt->Grid.dwBottom - pTxt->Grid.dwTop);  // (*D2Vars.D2CLIENT_ScreenHeight - (480 - pTxt->Grid.dwBottom));

        pOut->nGridX = pTxt->Inventory.nGridX;
        pOut->nGridY = pTxt->Inventory.nGridY;
        pOut->dwLeft = xLeft;
        pOut->dwRight = xRight;
        pOut->dwTop = xTop;
        pOut->dwBottom = xBottom;
        pOut->nGridWidth = pTxt->Grid.nWidth;
        pOut->nGridHeight = pTxt->Grid.nHeight;
    }

}

void __stdcall Inventory::GetInventoryField(int nRecord, int nScreenMode, InventoryLayout *pOut, int nField) // Wrapper on D2Common.Ordinal10441
{
    if (nScreenMode < 3) // Legacy support
    {
        if (nScreenMode == 2)
            nScreenMode = 1;
        InventoryTxt* pTxt = &(*D2COMMON_InventoryTxt)[nRecord + (nScreenMode * 16)];
        InventoryLayout * pLayout = &pTxt->hItem[nField];

        pOut->dwLeft = pLayout->dwLeft;
        pOut->dwRight = pLayout->dwRight;
        pOut->dwTop = pLayout->dwTop;
        pOut->dwBottom = pLayout->dwBottom;
        pOut->nWidth = pLayout->nWidth;
        pOut->nHeight = pLayout->nHeight;
    } else {
        InventoryTxt* pTxt = &(*D2COMMON_InventoryTxt)[nRecord];
        InventoryLayout * pLayout = &pTxt->hItem[nField];

        int xLeft = -1;
        int xRight = -1;

        if (pTxt->Grid.dwLeft > 300) {
            xLeft = pLayout->dwLeft == -1 ? -1 : ((pLayout->dwLeft - 320) + (*D2CLIENT_ScreenSizeX / 2));
            xRight = pLayout->dwRight == -1 ? -1 : ((pLayout->dwRight - 320) + (*D2CLIENT_ScreenSizeX / 2));
        } else {
            xLeft = ((*D2CLIENT_ScreenSizeX / 2) - 320) + pLayout->dwLeft;
            xRight = ((*D2CLIENT_ScreenSizeX / 2) - 320) + pLayout->dwRight;
        }

        int xTop = pLayout->dwTop == -1 ? -1 : ((*D2CLIENT_ScreenSizeY / 2) - 240) + pLayout->dwTop;
        int xBottom = pLayout->dwBottom == -1 ? -1 : xTop + (pLayout->dwBottom - pLayout->dwTop);    //(*D2Vars.D2CLIENT_ScreenHeight - (480 - pLayout->dwBottom));

        pOut->dwLeft = xLeft;
        pOut->dwRight = xRight;
        pOut->dwTop = xTop;
        pOut->dwBottom = xBottom;
        pOut->nWidth = pLayout->nWidth;
        pOut->nHeight = pLayout->nHeight;
    }

}