2 stdcall MenuHelp(long long long long long long ptr)
3 stdcall ShowHideMenuCtl(long long ptr)
4 stdcall GetEffectiveClientRect(long ptr ptr)
5 stdcall DrawStatusTextA(long ptr str long)
6 stdcall CreateStatusWindowA(long str long long)
7 stdcall CreateToolbar(long long long long long long ptr long)
8 stdcall CreateMappedBitmap(long long long ptr long)
9 stdcall -noname DPA_LoadStream(ptr ptr ptr ptr)
10 stdcall -noname DPA_SaveStream(ptr ptr ptr ptr)
11 stdcall -noname DPA_Merge(ptr ptr long ptr ptr long)
12 stdcall CreatePropertySheetPage(ptr) CreatePropertySheetPageA
13 stdcall MakeDragList(long)
14 stdcall LBItemFromPt(long double long) #(long int64 long)
15 stdcall DrawInsert(long long long)
16 stdcall CreateUpDownControl(long long long long long long long long long long long long)
17 stdcall InitCommonControls()
18 stdcall CreatePropertySheetPageA(ptr)
19 stdcall CreatePropertySheetPageW(ptr)
20 stdcall CreateStatusWindow(long str long long) CreateStatusWindowA
21 stdcall CreateStatusWindowW(long wstr long long)
22 stdcall CreateToolbarEx(long long long long long long ptr long long long long long long)
23 stdcall DestroyPropertySheetPage(long)
@ stdcall -private DllGetVersion(ptr)
@ stdcall -private DllInstall(long wstr)
26 stdcall DrawStatusText(long ptr ptr long) DrawStatusTextA
27 stdcall DrawStatusTextW(long ptr wstr long)
28 stdcall FlatSB_EnableScrollBar(long long long)
29 stdcall FlatSB_GetScrollInfo(long long ptr)
30 stdcall FlatSB_GetScrollPos(long long)
31 stdcall FlatSB_GetScrollProp(long long ptr)
32 stdcall FlatSB_GetScrollRange(long long ptr ptr)
33 stdcall FlatSB_SetScrollInfo(long long ptr long)
34 stdcall FlatSB_SetScrollPos(long long long long)
35 stdcall FlatSB_SetScrollProp(long long long long)
36 stdcall FlatSB_SetScrollRange(long long long long long)
37 stdcall FlatSB_ShowScrollBar(long long long)
38 stdcall GetMUILanguage()
39 stdcall ImageList_Add(ptr long long)
40 stdcall ImageList_AddIcon(ptr long)
41 stdcall ImageList_AddMasked(ptr long long)
42 stdcall ImageList_BeginDrag(ptr long long long)
43 stdcall ImageList_Copy(ptr long ptr long long)
44 stdcall ImageList_Create(long long long long long)
45 stdcall ImageList_Destroy(ptr)
46 stdcall ImageList_DragEnter(long long long)
47 stdcall ImageList_DragLeave(long)
48 stdcall ImageList_DragMove(long long)
49 stdcall ImageList_DragShowNolock(long)
50 stdcall ImageList_Draw(ptr long long long long long)
51 stdcall ImageList_DrawEx(ptr long long long long long long long long long)
52 stdcall ImageList_DrawIndirect(ptr)
53 stdcall ImageList_Duplicate(ptr)
54 stdcall ImageList_EndDrag()
55 stdcall ImageList_GetBkColor(ptr)
56 stdcall ImageList_GetDragImage(ptr ptr)
57 stdcall ImageList_GetFlags(ptr)
58 stdcall ImageList_GetIcon(ptr long long)
59 stdcall ImageList_GetIconSize(ptr ptr ptr)
60 stdcall ImageList_GetImageCount(ptr)
61 stdcall ImageList_GetImageInfo(ptr long ptr)
62 stdcall ImageList_GetImageRect(ptr long ptr)
63 stdcall ImageList_LoadImage(long str long long long long long) ImageList_LoadImageA
64 stdcall ImageList_LoadImageA(long str long long long long long)
65 stdcall ImageList_LoadImageW(long wstr long long long long long)
66 stdcall ImageList_Merge(ptr long ptr long long long)
67 stdcall ImageList_Read(ptr)
68 stdcall ImageList_Remove(ptr long)
69 stdcall ImageList_Replace(ptr long long long)
70 stdcall ImageList_ReplaceIcon(ptr long long)
71 stdcall -noname Alloc(long)
72 stdcall -noname ReAlloc(ptr long)
73 stdcall -noname Free(ptr)
74 stdcall -noname GetSize(ptr)
75 stdcall ImageList_SetBkColor(ptr long)
76 stdcall ImageList_SetDragCursorImage(ptr long long long)
77 stdcall ImageList_SetFilter(ptr long long)
78 stdcall ImageList_SetFlags(ptr long)
79 stdcall ImageList_SetIconSize(ptr long long)
80 stdcall ImageList_SetImageCount(ptr long)
81 stdcall ImageList_SetOverlayImage(ptr long long)
82 stdcall ImageList_Write(ptr ptr)
83 stdcall InitCommonControlsEx(ptr)
84 stdcall InitMUILanguage(long)
85 stdcall InitializeFlatSB(long)
86 stdcall PropertySheet(ptr) PropertySheetA
87 stdcall PropertySheetA(ptr)
88 stdcall PropertySheetW(ptr)
89 stdcall RegisterClassNameW(wstr)
90 stdcall UninitializeFlatSB(long)
91 stdcall _TrackMouseEvent(ptr)
151 stdcall -noname CreateMRUListA(ptr)
152 stdcall -ordinal FreeMRUList(long)
153 stdcall -noname AddMRUStringA(long str)
154 stdcall -noname EnumMRUListA(long long ptr long)
155 stdcall -noname FindMRUStringA(long str ptr)
156 stdcall -noname DelMRUString(long long)
157 stdcall -noname CreateMRUListLazyA(ptr long long long)
163 stdcall -noname CreatePage(long ptr)
164 stdcall -noname CreateProxyPage(long long)
167 stdcall -noname AddMRUData(long ptr long)
169 stdcall -noname FindMRUData(long ptr long ptr)
233 stdcall -noname Str_GetPtrA(str str long)
234 stdcall -noname Str_SetPtrA(str str)
235 stdcall -noname Str_GetPtrW(wstr wstr long)
236 stdcall -ordinal Str_SetPtrW(wstr wstr)
320 stdcall -ordinal DSA_Create(long long)
321 stdcall -ordinal DSA_Destroy(ptr)
322 stdcall -noname DSA_GetItem(ptr long ptr)
323 stdcall -ordinal DSA_GetItemPtr(ptr long)
324 stdcall -ordinal DSA_InsertItem(ptr long ptr)
325 stdcall -noname DSA_SetItem (ptr long ptr)
326 stdcall -noname DSA_DeleteItem(ptr long)
327 stdcall -ordinal DSA_DeleteAllItems(ptr)
328 stdcall -ordinal DPA_Create(long)
329 stdcall -ordinal DPA_Destroy(ptr)
330 stdcall -noname DPA_Grow(ptr long)
331 stdcall -noname DPA_Clone(ptr ptr)
332 stdcall -ordinal DPA_GetPtr(ptr long)
333 stdcall -noname DPA_GetPtrIndex(ptr ptr)
334 stdcall -ordinal DPA_InsertPtr(ptr long ptr)
335 stdcall -ordinal DPA_SetPtr(ptr long ptr)
336 stdcall -ordinal DPA_DeletePtr(ptr long)
337 stdcall -ordinal DPA_DeleteAllPtrs(ptr)
338 stdcall -ordinal DPA_Sort(ptr ptr long)
339 stdcall -ordinal DPA_Search(ptr ptr long ptr long long)
340 stdcall -noname DPA_CreateEx(long long)
341 stdcall -noname SendNotify(long long long ptr)
342 stdcall -noname SendNotifyEx(long long long ptr long)
350 stdcall -noname -private StrChrA(str long)
351 stdcall -noname -private StrRChrA(str str long)
352 stdcall -noname -private StrCmpNA(str str long)
353 stdcall -noname -private StrCmpNIA(str str long)
354 stdcall -noname -private StrStrA(str str)
355 stdcall -noname -private StrStrIA(str str)
356 stdcall -noname -private StrCSpnA(str str)
357 stdcall -noname -private StrToIntA(str)
358 stdcall -noname -private StrChrW(wstr long)
359 stdcall -noname -private StrRChrW(wstr wstr long)
360 stdcall -noname -private StrCmpNW(wstr wstr long)
361 stdcall -noname -private StrCmpNIW(wstr wstr long)
362 stdcall -noname -private StrStrW(wstr wstr)
363 stdcall -noname -private StrStrIW(wstr wstr)
364 stdcall -noname -private StrCSpnW(wstr wstr)
365 stdcall -noname -private StrToIntW(wstr)
366 stdcall -noname -private StrChrIA(str long)
367 stdcall -noname -private StrChrIW(wstr long)
368 stdcall -noname -private StrRChrIA(str str long)
369 stdcall -noname -private StrRChrIW(wstr wstr long)
372 stdcall -noname -private StrRStrIA(str str str)
373 stdcall -noname -private StrRStrIW(wstr wstr wstr)
374 stdcall -noname -private StrCSpnIA(str str)
375 stdcall -noname -private StrCSpnIW(wstr wstr)
376 stdcall -noname -private IntlStrEqWorkerA(long str str long)
377 stdcall -noname -private IntlStrEqWorkerW(long wstr wstr long)
381 stdcall -noname -private Unnamedvistabullshit(ptr)
382 stdcall -noname SmoothScrollWindow(ptr)
383 stdcall -noname DoReaderMode(ptr)
384 stdcall -noname SetPathWordBreakProc(ptr long)
385 stdcall -ordinal DPA_EnumCallback(ptr ptr ptr)
386 stdcall -ordinal DPA_DestroyCallback(ptr ptr ptr)
387 stdcall -noname DSA_EnumCallback(ptr ptr ptr)
388 stdcall -ordinal DSA_DestroyCallback(ptr ptr ptr)
#389 CControl::v_OnNotify
390 stdcall -noname ImageList_SetColorTable(ptr long long ptr)
400 stdcall -ordinal CreateMRUListW(ptr)
401 stdcall -ordinal AddMRUStringW(long wstr)
402 stdcall -noname FindMRUStringW(long wstr ptr)
403 stdcall -ordinal EnumMRUListW(long long ptr long)
404 stdcall -noname CreateMRUListLazyW(ptr long long long)
410 stdcall -ordinal SetWindowSubclass(long ptr long long)
411 stdcall -ordinal GetWindowSubclass(long ptr long ptr)
412 stdcall -ordinal RemoveWindowSubclass(long ptr long)
413 stdcall -ordinal DefSubclassProc(long long long long)
414 stdcall -noname MirrorIcon(ptr ptr)
415 stdcall -noname DrawTextWrap(long wstr long ptr long) user32.DrawTextW
416 stdcall -noname DrawTextExPrivWrap(long wstr long ptr long ptr) user32.DrawTextExW
417 stdcall -noname ExtTextOutWrap(long long long long ptr wstr long ptr) gdi32.ExtTextOutW
418 stdcall -noname GetCharWidthWrap(long long long long) gdi32.GetCharWidthW
419 stdcall -noname GetTextExtentPointWrap(long wstr long ptr) gdi32.GetTextExtentPointW
420 stdcall -noname GetTextExtentPoint32Wrap(long wstr long ptr) gdi32.GetTextExtentPoint32W
421 stdcall -noname TextOutWrap(long long long wstr long) gdi32.TextOutW

; Exported in v6 but not v5
@ stdcall DrawShadowText(long wstr long ptr long long long long long)
@ stdcall -version=0x600+ LoadIconWithScaleDown(long wstr long long long)
@ stdcall -version=0x600+ LoadIconMetric(long wstr long long)
