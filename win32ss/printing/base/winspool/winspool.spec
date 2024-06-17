100 stub -noname EnumPrinterPropertySheets
101 stub -noname ClusterSplOpen
102 stub -noname ClusterSplClose
103 stub -noname ClusterSplIsAlive
104 stub PerfClose
105 stub PerfCollect
106 stub PerfOpen
107 stdcall -stub ADVANCEDSETUPDIALOG(ptr long ptr ptr) AdvancedSetupDialog
108 stdcall -stub AbortPrinter(ptr)
109 stdcall -stub AddFormA(ptr long ptr)
110 stdcall -stub AddFormW(ptr long ptr)
111 stdcall -stub AddJobA(ptr long ptr long ptr)
112 stdcall -stub AddJobW(ptr long ptr long ptr)
113 stdcall -stub AddMonitorA(str long ptr)
114 stdcall -stub AddMonitorW(wstr long ptr)
115 stdcall -stub AddPortA(str ptr str)
116 stdcall -stub AddPortExA(str long ptr str)
117 stdcall -stub AddPortExW(wstr long ptr wstr)
118 stdcall -stub AddPortW(wstr ptr wstr)
119 stdcall -stub AddPrintProcessorA(str str str str)
120 stdcall -stub AddPrintProcessorW(wstr wstr wstr wstr)
121 stdcall -stub AddPrintProvidorA(str long ptr)
122 stdcall -stub AddPrintProvidorW(wstr long ptr)
123 stdcall -stub AddPrinterA(str long ptr)
124 stub AddPrinterConnectionA
125 stub AddPrinterConnectionW
126 stdcall -stub AddPrinterDriverA(str long ptr)
127 stdcall -stub AddPrinterDriverExA(str long ptr long)
128 stdcall -stub AddPrinterDriverExW(wstr long ptr long)
129 stdcall -stub AddPrinterDriverW(wstr long ptr)
130 stdcall -stub AddPrinterW(wstr long ptr)
131 stdcall -stub AdvancedDocumentPropertiesA(ptr ptr str ptr ptr)
132 stdcall -stub AdvancedDocumentPropertiesW(ptr ptr wstr ptr ptr)
133 stdcall -stub AdvancedSetupDialog(ptr long ptr ptr)
134 stdcall -stub ClosePrinter(ptr)
135 stdcall -stub CloseSpoolFileHandle(ptr ptr)
136 stdcall -stub CommitSpoolData(ptr ptr long)
137 stdcall -stub ConfigurePortA(str ptr str)
138 stdcall -stub ConfigurePortW(wstr ptr wstr)
139 stub ConnectToPrinterDlg
140 stub ConvertAnsiDevModeToUnicodeDevmode
141 stub ConvertUnicodeDevModeToAnsiDevmode
142 stdcall -stub CreatePrinterIC(ptr ptr)
143 stdcall -stub DEVICECAPABILITIES(str str long ptr ptr) DeviceCapabilitiesA
144 stdcall -stub DEVICEMODE(ptr ptr str ptr) DeviceMode
145 stdcall -stub DeleteFormA(ptr str)
146 stdcall -stub DeleteFormW(ptr wstr)
147 stdcall -stub DeleteMonitorA(str str str)
148 stdcall -stub DeleteMonitorW(wstr wstr wstr)
149 stdcall -stub DeletePortA(str ptr str)
150 stdcall -stub DeletePortW(wstr ptr wstr)
151 stdcall -stub DeletePrintProcessorA(str str str)
152 stdcall -stub DeletePrintProcessorW(wstr wstr wstr)
153 stdcall -stub DeletePrintProvidorA(str str str)
154 stdcall -stub DeletePrintProvidorW(wstr wstr wstr)
155 stdcall -stub DeletePrinter(ptr)
156 stub DeletePrinterConnectionA
157 stub DeletePrinterConnectionW
158 stdcall -stub DeletePrinterDataA(ptr str)
159 stdcall -stub DeletePrinterDataExA(ptr str str)
160 stdcall -stub DeletePrinterDataExW(ptr wstr wstr)
161 stdcall -stub DeletePrinterDataW(ptr wstr)
162 stdcall -stub DeletePrinterDriverA(str str str)
163 stdcall -stub DeletePrinterDriverExA(str str str long long)
164 stdcall -stub DeletePrinterDriverExW(wstr wstr wstr long long)
165 stdcall -stub DeletePrinterDriverW(wstr wstr wstr)
166 stdcall -stub -stub DeletePrinterIC(ptr)
167 stdcall -stub DeletePrinterKeyA(ptr str)
168 stdcall -stub DeletePrinterKeyW(ptr wstr)
169 stdcall -stub DevQueryPrint(ptr ptr ptr)
170 stdcall -stub DevQueryPrintEx(ptr)
171 stdcall -stub DeviceCapabilities(str str long ptr ptr) DeviceCapabilitiesA
172 stdcall -stub DeviceCapabilitiesA(str str long ptr ptr)
173 stdcall -stub DeviceCapabilitiesW(wstr wstr long ptr ptr)
174 stdcall -stub DeviceMode(ptr ptr str ptr)
175 stdcall -stub DevicePropertySheets(ptr long)
176 stdcall -stub DocumentEvent(ptr ptr long long ptr long ptr)
177 stdcall -stub DocumentPropertiesA(ptr ptr str ptr ptr long)
178 stdcall -stub DocumentPropertiesW(ptr ptr wstr ptr ptr long)
179 stdcall -stub DocumentPropertySheets(ptr long)
180 stdcall -stub EXTDEVICEMODE(ptr ptr ptr str str ptr str long) ExtDeviceMode
181 stdcall -stub EndDocPrinter(ptr)
182 stdcall -stub EndPagePrinter(ptr)
183 stdcall -stub EnumFormsA(ptr long ptr long ptr ptr)
184 stdcall -stub EnumFormsW(ptr long ptr long ptr ptr)
185 stdcall -stub EnumJobsA(ptr long long long ptr long ptr ptr)
186 stdcall -stub EnumJobsW(ptr long long long ptr long ptr ptr)
187 stdcall -stub EnumMonitorsA(str long ptr long ptr ptr)
188 stdcall -stub EnumMonitorsW(wstr long ptr long ptr ptr)
189 stdcall -stub EnumPortsA(str long ptr long ptr ptr)
190 stdcall -stub EnumPortsW(wstr long ptr long ptr ptr)
191 stdcall -stub EnumPrintProcessorDatatypesA(ptr ptr long ptr long ptr ptr)
192 stdcall -stub EnumPrintProcessorDatatypesW(ptr ptr long ptr long ptr ptr)
193 stdcall -stub EnumPrintProcessorsA(str str long ptr long ptr ptr)
194 stdcall -stub EnumPrintProcessorsW(wstr wstr long ptr long ptr ptr)
195 stdcall -stub EnumPrinterDataA(ptr long str long ptr ptr ptr long ptr)
196 stdcall -stub EnumPrinterDataExA(ptr str ptr long ptr ptr)
197 stdcall -stub EnumPrinterDataExW(ptr wstr ptr long ptr ptr)
198 stdcall -stub EnumPrinterDataW(ptr long wstr long ptr ptr ptr long ptr)
199 stdcall -stub EnumPrinterDriversA(str str long ptr long ptr ptr)
200 stdcall -stub EnumPrinterDriversW(wstr wstr long ptr long ptr ptr)
201 stdcall -stub GetDefaultPrinterA(ptr ptr)
202 stdcall -stub SetDefaultPrinterA(str)
203 stdcall -stub GetDefaultPrinterW(ptr ptr)
204 stdcall -stub SetDefaultPrinterW(wstr)
205 stub -noname SplReadPrinter
206 stub -noname AddPerMachineConnectionA
207 stub -noname AddPerMachineConnectionW
208 stub -noname DeletePerMachineConnectionA
209 stub -noname DeletePerMachineConnectionW
210 stub -noname EnumPerMachineConnectionsA
211 stub -noname EnumPerMachineConnectionsW
212 stdcall -stub -noname LoadPrinterDriver(ptr)
213 stub -noname RefCntLoadDriver
214 stub -noname RefCntUnloadDriver
215 stub -noname ForceUnloadDriver
216 stub -noname PublishPrinterA
217 stub -noname PublishPrinterW
218 stdcall -stub -noname CallCommonPropertySheetUI(ptr ptr long ptr)
219 stub -noname PrintUIQueueCreate
220 stub -noname PrintUIPrinterPropPages
221 stub -noname PrintUIDocumentDefaults
222 stub -noname SendRecvBidiData
223 stub -noname RouterFreeBidiResponseContainer
224 stub -noname ExternalConnectToLd64In32Server
225 stdcall -stub EnumPrinterKeyA(ptr str str long ptr)
226 stub -noname PrintUIWebPnpEntry
227 stub -noname PrintUIWebPnpPostEntry
228 stub -noname PrintUICreateInstance
229 stub -noname PrintUIDocumentPropertiesWrap
230 stub -noname PrintUIPrinterSetup
231 stub -noname PrintUIServerPropPages
232 stub -noname AddDriverCatalog
233 stdcall -stub EnumPrinterKeyW(ptr wstr wstr long ptr)
234 stdcall -stub EnumPrintersA(long ptr long ptr long ptr ptr)
235 stdcall -stub EnumPrintersW(long ptr long ptr long ptr ptr)
236 stdcall -stub ExtDeviceMode(ptr ptr ptr str str ptr str long)
237 stub FindClosePrinterChangeNotification
238 stub FindFirstPrinterChangeNotification
239 stub FindNextPrinterChangeNotification
240 stdcall -stub FlushPrinter(ptr ptr long ptr long)
241 stub FreePrinterNotifyInfo
242 stdcall -stub GetFormA(ptr str long ptr long ptr)
243 stdcall -stub GetFormW(ptr str long ptr long ptr)
244 stdcall -stub GetJobA(ptr long long ptr long ptr)
245 stdcall -stub GetJobW(ptr long long ptr long ptr)
246 stdcall -stub GetPrintProcessorDirectoryA(str str long ptr long ptr)
247 stdcall -stub GetPrintProcessorDirectoryW(wstr wstr long ptr long ptr)
248 stdcall -stub GetPrinterA(ptr long ptr long ptr)
249 stdcall -stub GetPrinterDataA(ptr str ptr ptr long ptr)
250 stdcall -stub GetPrinterDataExA(ptr str str ptr ptr long ptr)
251 stdcall -stub GetPrinterDataExW(ptr wstr wstr ptr ptr long ptr)
252 stdcall -stub GetPrinterDataW(ptr wstr ptr ptr long ptr)
253 stdcall -stub GetPrinterDriverA(ptr str long ptr long ptr)
254 stdcall -stub GetPrinterDriverDirectoryA(str str long ptr long ptr)
255 stdcall -stub GetPrinterDriverDirectoryW(wstr wstr long ptr long ptr)
256 stdcall -stub GetPrinterDriverW(ptr wstr long ptr long ptr)
257 stdcall -stub GetPrinterW(ptr long ptr long ptr)
258 stdcall -stub GetSpoolFileHandle(ptr)
259 stdcall -stub IsValidDevmodeA(ptr long)
260 stdcall -stub IsValidDevmodeW(ptr long)
261 stdcall -stub OpenPrinterA(str ptr ptr)
262 stdcall -stub OpenPrinterW(wstr ptr ptr)
263 stdcall -stub PlayGdiScriptOnPrinterIC(ptr ptr long ptr long long)
264 stdcall -stub PrinterMessageBoxA(ptr long ptr str str long)
265 stdcall -stub PrinterMessageBoxW(ptr long ptr wstr wstr long)
266 stdcall -stub PrinterProperties(ptr ptr)
267 stdcall -stub QueryColorProfile(ptr ptr long ptr ptr ptr)
268 stdcall -stub QueryRemoteFonts(ptr ptr long)
269 stdcall -stub QuerySpoolMode(ptr ptr ptr)
270 stdcall -stub ReadPrinter(ptr ptr long ptr)
271 stdcall -stub ResetPrinterA(ptr ptr)
272 stdcall -stub ResetPrinterW(ptr ptr)
273 stdcall -stub ScheduleJob(ptr long)
274 stdcall -stub SeekPrinter(ptr int64 ptr long long)
275 stub SetAllocFailCount
276 stdcall -stub SetFormA(ptr str long str)
277 stdcall -stub SetFormW(ptr str long str)
278 stdcall -stub SetJobA(ptr long long ptr long)
279 stdcall -stub SetJobW(ptr long long ptr long)
280 stdcall -stub SetPortA(str str long ptr)
281 stdcall -stub SetPortW(wstr wstr long ptr)
282 stdcall -stub SetPrinterA(ptr long ptr long)
283 stdcall -stub SetPrinterDataA(ptr str long ptr long)
284 stdcall -stub SetPrinterDataExA(ptr str str long ptr long)
285 stdcall -stub SetPrinterDataExW(ptr wstr wstr long ptr long)
286 stdcall -stub SetPrinterDataW(ptr wstr long ptr long)
287 stdcall -stub SetPrinterW(ptr long ptr long)
288 stdcall -stub SplDriverUnloadComplete(ptr)
289 stub SpoolerDevQueryPrintW
290 stdcall -stub SpoolerInit()
291 stdcall -stub SpoolerPrinterEvent(wstr long long long)
292 stdcall -stub StartDocDlgA(ptr ptr)
293 stdcall -stub StartDocDlgW(ptr ptr)
294 stdcall -stub StartDocPrinterA(ptr long ptr)
295 stdcall -stub StartDocPrinterW(ptr long ptr)
296 stdcall -stub StartPagePrinter(ptr)
297 stub WaitForPrinterChange
298 stdcall -stub WritePrinter(ptr ptr long ptr)
299 stdcall -stub XcvDataW(ptr wstr ptr long ptr long ptr ptr)
