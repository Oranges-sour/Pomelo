// PomeloLib.cpp : 定义静态库的函数。
//

#include <assert.h>
#include <stdint.h>
#include <string.h>

#include <iostream>
using namespace std;

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容

#include "easyx.h"

#define DEFINE_STRUCT(name, size_bytes)                                        \
    struct name {                                                              \
        char buf[(size_bytes)];                                                \
    }

#define CREATE_STRUCT(name, size_bytes)                                        \
    struct {                                                                   \
        char buf[(size_bytes)];                                                \
    } name

#define shft_tunc(char_ptr, off, type) ((type *)((char_ptr) + off))

typedef uint8_t u8;

typedef int32_t i32;
typedef uint32_t u32;

typedef float f32;
typedef double f64;

static_assert(sizeof(LOGFONT) == 92, "");

extern "C" {

void *p_initgraph(int w, int h, int flag) {
    cout << sizeof(IMAGE) << endl;
    return (void *)initgraph(w, h, flag);
}

void p_closegraph() { closegraph(); }

void p_cleardevice() { cleardevice(); }

void p_setcliprgn(void *hrgn) { setcliprgn((HRGN)hrgn); }

void p_clearcliprgn() { clearcliprgn(); }

void p_getlinestyle(void *buf_20b) {
    DEFINE_STRUCT(BUF, sizeof(u32) * 3 + sizeof(void *) * 1);

    LINESTYLE ls;

    getlinestyle(&ls);

    char *p = ((BUF *)buf_20b)->buf;

    *shft_tunc(p, 0 * sizeof(u32), u32) = ls.style;
    *shft_tunc(p, 1 * sizeof(u32), u32) = ls.thickness;
    *shft_tunc(p, 2 * sizeof(u32), void *) = (void *)ls.puserstyle;
    *shft_tunc(p, 2 * sizeof(u32) + sizeof(void *), u32) = ls.userstylecount;
}

void p_setlinestyle_1(void *buf_20b) {
    DEFINE_STRUCT(BUF, sizeof(u32) * 3 + sizeof(void *) * 1);

    LINESTYLE ls;

    char *p = ((BUF *)buf_20b)->buf;

    ls.style = *shft_tunc(p, 0 * sizeof(u32), u32);

    ls.thickness = *shft_tunc(p, 1 * sizeof(u32), u32);

    ls.puserstyle = (DWORD *)(*shft_tunc(p, 2 * sizeof(u32), void *));

    ls.userstylecount = *shft_tunc(p, 2 * sizeof(u32) + sizeof(void *), u32);

    setlinestyle(&ls);
}

void p_setlinestyle_2(i32 style, i32 thickness, void *puserstyle,
                      u32 userstylecount) {
    setlinestyle(style, thickness, (const DWORD *)puserstyle, userstylecount);
}

void p_getfillstyle(void *buf_16b) {
    DEFINE_STRUCT(BUF, sizeof(i32) * 2 + sizeof(void *) * 1);

    FILLSTYLE fs;

    getfillstyle(&fs);

    char *p = ((BUF *)buf_16b)->buf;

    *shft_tunc(p, 0 * sizeof(i32), i32) = fs.style;
    *shft_tunc(p, 1 * sizeof(i32), i32) = fs.hatch;
    *shft_tunc(p, 1 * sizeof(i32) + sizeof(void *), void *) =
        (void *)fs.ppattern;
}

void p_setfillstyle_1(void *buf_16b) {
    DEFINE_STRUCT(BUF, sizeof(i32) * 2 + sizeof(void *) * 1);

    FILLSTYLE fs;

    char *p = ((BUF *)buf_16b)->buf;

    fs.style = *shft_tunc(p, 0 * sizeof(i32), i32);
    fs.hatch = *shft_tunc(p, 1 * sizeof(i32), i32);
    fs.ppattern =
        (IMAGE *)*shft_tunc(p, 1 * sizeof(i32) + sizeof(void *), void *);
}

void p_setfillstyle_2(i32 style, i32 hatch, void *ppattern) {
    setfillstyle(style, hatch, (IMAGE *)ppattern);
}

void p_setfillstyle_3(void *ppattern8x8) { setfillstyle((BYTE *)ppattern8x8); }

void p_setorigin(i32 x, i32 y) { setorigin(x, y); }

void p_getaspectratio(void *pxasp, void *pyasp) {
    getaspectratio((f32 *)pxasp, (f32 *)pyasp);
}

void p_setaspectratio(f32 xasp, f32 yasp) { setaspectratio(xasp, yasp); }

i32 p_getrop2() { return getrop2(); }

void p_setrop2(i32 mode) { setrop2(mode); }

i32 p_getpolyfillmode() { return getpolyfillmode(); }

void p_setpolyfillmode(i32 mode) { setpolyfillmode(mode); }

void p_graphdefaults() { graphdefaults(); }

u32 p_getlinecolor() { return getlinecolor(); }

void p_setlinecolor(u32 color) { setlinecolor(color); }

u32 p_gettextcolor() { return gettextcolor(); }

void p_settextcolor(u32 color) { settextcolor(color); }

u32 p_getfillcolor() { return getfillcolor(); }

void p_setfillcolor(u32 color) { setfillcolor(color); }

u32 p_getbkcolor() { return getbkcolor(); }

void p_setbkcolor(u32 color) { setbkcolor(color); }

i32 p_getbkmode() { return getbkmode(); }

void p_setbkmode(i32 mode) { setbkmode(mode); }

u32 p_RGBtoGRAY(u32 rgb) { return RGBtoGRAY(rgb); }

void p_RGBtoHSL(u32 rgb, void *H, void *S, void *L) {
    RGBtoHSL(rgb, (f32 *)H, (f32 *)S, (f32 *)L);
}

void p_RGBtoHSV(u32 rgb, void *H, void *S, void *V) {
    RGBtoHSV(rgb, (f32 *)H, (f32 *)S, (f32 *)V);
}

u32 p_HSLtoRGB(f32 H, f32 S, f32 L) { return HSLtoRGB(H, S, L); }

u32 p_HSVtoRGB(f32 H, f32 S, f32 V) { return HSVtoRGB(H, S, V); }

u32 p_getpixel(i32 x, i32 y) { return getpixel(x, y); }

void p_putpixel(i32 x, i32 y, u32 color) { putpixel(x, y, color); }

void p_line(i32 x1, i32 y1, i32 x2, i32 y2) { line(x1, y1, x2, y2); }

void p_rectangle(i32 left, i32 top, i32 right, i32 bottom) {
    rectangle(left, top, right, bottom);
}

void p_fillrectangle(i32 left, i32 top, i32 right, i32 bottom) {
    fillrectangle(left, top, right, bottom);
}

void p_solidrectangle(i32 left, i32 top, i32 right, i32 bottom) {
    solidrectangle(left, top, right, bottom);
}

void p_clearrectangle(i32 left, i32 top, i32 right, i32 bottom) {
    clearrectangle(left, top, right, bottom);
}

void p_circle(i32 x, i32 y, i32 radius) { circle(x, y, radius); }

void p_fillcircle(i32 x, i32 y, i32 radius) { fillcircle(x, y, radius); }

void p_solidcircle(i32 x, i32 y, i32 radius) { solidcircle(x, y, radius); }

void p_clearcircle(i32 x, i32 y, i32 radius) { clearcircle(x, y, radius); }

void p_ellipse(i32 left, i32 top, i32 right, i32 bottom) {
    ellipse(left, top, right, bottom);
}

void p_fillellipse(i32 left, i32 top, i32 right, i32 bottom) {
    fillellipse(left, top, right, bottom);
}

void p_solidellipse(i32 left, i32 top, i32 right, i32 bottom) {
    solidellipse(left, top, right, bottom);
}

void p_clearellipse(i32 left, i32 top, i32 right, i32 bottom) {
    clearellipse(left, top, right, bottom);
}

void p_roundrect(i32 left, i32 top, i32 right, i32 bottom, i32 ellipsewidth,
                 i32 ellipseheight) {
    roundrect(left, top, right, bottom, ellipsewidth, ellipseheight);
}

void p_fillroundrect(i32 left, i32 top, i32 right, i32 bottom, i32 ellipsewidth,
                     i32 ellipseheight) {
    fillroundrect(left, top, right, bottom, ellipsewidth, ellipseheight);
}

void p_solidroundrect(i32 left, i32 top, i32 right, i32 bottom,
                      i32 ellipsewidth, i32 ellipseheight) {
    solidroundrect(left, top, right, bottom, ellipsewidth, ellipseheight);
}

void p_clearroundrect(i32 left, i32 top, i32 right, i32 bottom,
                      i32 ellipsewidth, i32 ellipseheight) {
    clearroundrect(left, top, right, bottom, ellipsewidth, ellipseheight);
}

void p_arc(i32 left, i32 top, i32 right, i32 bottom, f64 stangle,
           f64 endangle) {
    arc(left, top, right, bottom, stangle, endangle);
}

void p_pie(i32 left, i32 top, i32 right, i32 bottom, f64 stangle,
           f64 endangle) {
    pie(left, top, right, bottom, stangle, endangle);
}

void p_fillpie(i32 left, i32 top, i32 right, i32 bottom, f64 stangle,
               f64 endangle) {
    fillpie(left, top, right, bottom, stangle, endangle);
}

void p_solidpie(i32 left, i32 top, i32 right, i32 bottom, f64 stangle,
                f64 endangle) {
    solidpie(left, top, right, bottom, stangle, endangle);
}

void p_clearpie(i32 left, i32 top, i32 right, i32 bottom, f64 stangle,
                f64 endangle) {
    clearpie(left, top, right, bottom, stangle, endangle);
}

void p_polyline(void *buf_8b_arr, i32 num) {
    polyline((const POINT *)buf_8b_arr, num);
}

void p_polygon(void *buf_8b_arr, i32 num) {
    polygon((const POINT *)buf_8b_arr, num);
}

void p_fillpolygon(void *buf_8b_arr, i32 num) {
    fillpolygon((const POINT *)buf_8b_arr, num);
}

void p_solidpolygon(void *buf_8b_arr, i32 num) {
    solidpolygon((const POINT *)buf_8b_arr, num);
}

void p_clearpolygon(void *buf_8b_arr, i32 num) {
    clearpolygon((const POINT *)buf_8b_arr, num);
}

void p_polybezier(void *buf_8b_arr, i32 num) {
    polybezier((const POINT *)buf_8b_arr, num);
}

void p_floodfill(i32 x, i32 y, u32 color, i32 filltype) {
    floodfill(x, y, color, filltype);
}

void p_outtextxy_1(i32 x, i32 y, void *str) { outtextxy(x, y, (LPCTSTR)str); }

void p_outtextxy_2(i32 x, i32 y, wchar_t c) { outtextxy(x, y, c); }

i32 p_textwidth_1(void *str) { return textwidth((LPCTSTR)str); }

i32 p_textwidth_2(wchar_t c) { return textwidth(c); }

i32 p_textheight_1(void *str) { return textheight((LPCTSTR)str); }

i32 p_textheight_2(wchar_t c) { return textheight(c); }

i32 p_drawtext_1(void *str, void *pRect, u32 uFormat) {
    return drawtext(((LPCTSTR)str), (RECT *)pRect, uFormat);
}

i32 p_drawtext_2(wchar_t c, RECT *pRect, UINT uFormat) {
    return drawtext(c, (RECT *)pRect, uFormat);
}

void p_settextstyle_1(i32 nHeight, i32 nWidth, void *lpszFace, i32 nEscapement,
                      i32 nOrientation, i32 nWeight, bool bItalic,
                      bool bUnderline, bool bStrikeOut, u8 fbCharSet,
                      u8 fbOutPrecision, u8 fbClipPrecision, u8 fbQuality,
                      u8 fbPitchAndFamily) {
    settextstyle(nHeight, nWidth, (LPCTSTR)lpszFace, nEscapement, nOrientation,
                 nWeight, bItalic, bUnderline, bStrikeOut, fbCharSet,
                 fbOutPrecision, fbClipPrecision, fbQuality, fbPitchAndFamily);
}

void p_settextstyle_2(void *buf_92b) { settextstyle((const LOGFONT *)buf_92b); }

void p_gettextstyle(void *buf_92b) {
    DEFINE_STRUCT(BUF, sizeof(i32) * 5 + sizeof(u8) * 8 + sizeof(WCHAR) * 32);

    LOGFONT lf;
    gettextstyle(&lf);

    char *p = ((BUF *)buf_92b)->buf;

    *shft_tunc(p, sizeof(i32) * 0 + sizeof(u8) * 0 + sizeof(WCHAR) * 0, i32) =
        lf.lfHeight;
    *shft_tunc(p, sizeof(i32) * 1 + sizeof(u8) * 0 + sizeof(WCHAR) * 0, i32) =
        lf.lfWidth;
    *shft_tunc(p, sizeof(i32) * 2 + sizeof(u8) * 0 + sizeof(WCHAR) * 0, i32) =
        lf.lfEscapement;
    *shft_tunc(p, sizeof(i32) * 3 + sizeof(u8) * 0 + sizeof(WCHAR) * 0, i32) =
        lf.lfOrientation;
    *shft_tunc(p, sizeof(i32) * 4 + sizeof(u8) * 0 + sizeof(WCHAR) * 0, i32) =
        lf.lfWeight;

    *shft_tunc(p, sizeof(i32) * 5 + sizeof(u8) * 0 + sizeof(WCHAR) * 0, u8) =
        lf.lfItalic;
    *shft_tunc(p, sizeof(i32) * 5 + sizeof(u8) * 1 + sizeof(WCHAR) * 0, u8) =
        lf.lfUnderline;
    *shft_tunc(p, sizeof(i32) * 5 + sizeof(u8) * 2 + sizeof(WCHAR) * 0, u8) =
        lf.lfStrikeOut;
    *shft_tunc(p, sizeof(i32) * 5 + sizeof(u8) * 3 + sizeof(WCHAR) * 0, u8) =
        lf.lfCharSet;
    *shft_tunc(p, sizeof(i32) * 5 + sizeof(u8) * 4 + sizeof(WCHAR) * 0, u8) =
        lf.lfOutPrecision;
    *shft_tunc(p, sizeof(i32) * 5 + sizeof(u8) * 5 + sizeof(WCHAR) * 0, u8) =
        lf.lfClipPrecision;
    *shft_tunc(p, sizeof(i32) * 5 + sizeof(u8) * 6 + sizeof(WCHAR) * 0, u8) =
        lf.lfQuality;
    *shft_tunc(p, sizeof(i32) * 5 + sizeof(u8) * 7 + sizeof(WCHAR) * 0, u8) =
        lf.lfPitchAndFamily;

    char *p_off = shft_tunc(
        p, sizeof(i32) * 5 + sizeof(u8) * 8 + sizeof(WCHAR) * 0, char);

    memcpy(p_off, lf.lfFaceName, 32);
}

void p_loadimage_1(void *buf_136b, void *pImgFile, i32 nWidth, i32 nHeight,
                   bool bResize) {

    loadimage((IMAGE *)buf_136b, (LPCTSTR)pImgFile, nWidth, nHeight);
}

void p_loadimage_2(void *buf_136b, void *pResType, void *pResName, i32 nWidth,
                   i32 nHeight, bool bResize) {
    loadimage((IMAGE *)buf_136b, (LPCTSTR)pResType, (LPCTSTR)pResName, nWidth,
              nHeight);
}

void p_saveimage(void *pImgFile, void *buf_136b) {
    saveimage((LPCTSTR)pImgFile, (IMAGE *)buf_136b);
}

void p_getimage(void *buf_136b, i32 srcX, i32 srcY, i32 srcWidth,
                i32 srcHeight) {
    getimage((IMAGE *)buf_136b, srcX, srcY, srcWidth, srcHeight);
}

void p_putimage_1(i32 dstX, i32 dstY, void *buf_136b, u32 dwRop) {
    putimage(dstX, dstY, (const IMAGE *)buf_136b, dwRop);
}

void p_putimage_2(i32 dstX, i32 dstY, i32 dstWidth, i32 dstHeight,
                  void *buf_136b, i32 srcX, i32 srcY, u32 dwRop) {
    putimage(dstX, dstY, dstWidth, dstHeight, (const IMAGE *)buf_136b, srcX,
             srcY, dwRop);
}

void p_rotateimage(void *buf_136b_dst, void *buf_136b_src, f64 radian,
                   u32 bkcolor, bool autosize, bool highquality) {
    rotateimage((IMAGE *)buf_136b_dst, (IMAGE *)buf_136b_src, radian, bkcolor,
                autosize, highquality);
}

void p_Resize(void *buf_136b, i32 width, i32 height) {
    Resize((IMAGE *)buf_136b, width, height);
}

i32 p_getwidth() { return getwidth(); }

i32 p_getheight() { return getheight(); }

void p_BeginBatchDraw() { BeginBatchDraw(); }

void p_FlushBatchDraw_1() { FlushBatchDraw(); }

void p_FlushBatchDraw_2(i32 left, i32 top, i32 right, i32 bottom) {
    FlushBatchDraw(left, top, right, bottom);
}

void p_EndBatchDraw_1() { EndBatchDraw(); }

void p_EndBatchDraw_2(i32 left, i32 top, i32 right, i32 bottom) {
    EndBatchDraw(left, top, right, bottom);
}
}
