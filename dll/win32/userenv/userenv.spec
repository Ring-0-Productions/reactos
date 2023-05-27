132 stdcall CreateEnvironmentBlock(ptr ptr long)
133 stdcall DeleteProfileA(str str str)
134 stdcall DeleteProfileW(wstr wstr wstr)
176 stdcall DestroyEnvironmentBlock(ptr)
@ stub -private DllCanUnloadNow                                              #stdcall DllCanUnloadNow()
@ stub -private DllGetClassObject                                            #stdcall DllGetClassObject(ptr ptr ptr)
@ stub -private DllInstall                                                   #stdcall DllInstall(long wstr)
@ stub -private DllRegisterServer                                            #stdcall DllRegisterServer()
@ stub -private DllUnregisterServer                                          #stdcall DllUnregisterServer()
182 stdcall EnterCriticalPolicySection(long)
183 stdcall ExpandEnvironmentStringsForUserA(ptr str str long)
184 stdcall ExpandEnvironmentStringsForUserW(ptr wstr wstr long)
185 stub ForceSyncFgPolicy                                            #stdcall ForceSyncFgPolicy(4)
186 stub FreeGPOListA                                                 #stdcall FreeGPOListA(ptr)
187 stub FreeGPOListW                                                 #stdcall FreeGPOListW(ptr)
188 stub GenerateRsopPolicy                                           #stdcall GenerateRsopPolicy(48)
189 stdcall GetAllUsersProfileDirectoryA(str ptr)
190 stdcall GetAllUsersProfileDirectoryW(wstr ptr)
191 stdcall GetAppliedGPOListA(long str ptr ptr ptr)
192 stdcall GetAppliedGPOListW(long wstr ptr ptr ptr)
193 stdcall GetDefaultUserProfileDirectoryA(str ptr)
194 stdcall GetDefaultUserProfileDirectoryW(wstr ptr)
195 stub GetGPOListA                                                  #stdcall GetGPOListA(ptr str str str long ptr)
196 stub GetGPOListW                                                  #stdcall GetGPOListW(ptr wstr wstr wstr long ptr)
197 stub GetNextFgPolicyRefreshInfo                                   #stdcall GetNextFgPolicyRefreshInfo(8)
198 stub GetPreviousFgPolicyRefreshInfo                               #stdcall GetPreviousFgPolicyRefreshInfo(8)
199 stdcall GetProfileType(ptr)
202 stdcall GetProfilesDirectoryA(str ptr)
203 stdcall GetProfilesDirectoryW(wstr ptr)
204 stdcall GetUserProfileDirectoryA(ptr str ptr)
205 stdcall GetUserProfileDirectoryW(ptr wstr ptr)
206 stdcall LeaveCriticalPolicySection(ptr)
207 stdcall LoadUserProfileA(ptr ptr)
208 stdcall LoadUserProfileW(ptr ptr)
209 stub ProcessGroupPolicyCompleted                                  #stdcall ProcessGroupPolicyCompleted(ptr ptr long)
210 stub ProcessGroupPolicyCompletedEx                                #stdcall ProcessGroupPolicyCompletedEx(ptr ptr long ptr)
211 stdcall RefreshPolicy(long)
212 stdcall RefreshPolicyEx(long long)
213 stdcall RegisterGPNotification(ptr long)
214 stub RsopAccessCheckByType                                        #stdcall RsopAccessCheckByType(ptr ptr ptr long ptr long ptr ptr ptr ptr ptr)
215 stub RsopFileAccessCheck                                          #stdcall RsopFileAccessCheck(wstr ptr long ptr ptr)
216 stub RsopLoggingEnabled                                           #stdcall RsopLoggingEnabled()
217 stub RsopResetPolicySettingStatus                                 #stdcall RsopResetPolicySettingStatus(long ptr ptr)
218 stub RsopSetPolicySettingStatus                                   #stdcall RsopSetPolicySettingStatus(long ptr ptr long ptr)
219 stdcall UnloadUserProfile(ptr ptr)
220 stdcall UnregisterGPNotification(ptr)
221 stdcall WaitForMachinePolicyForegroundProcessing()
222 stdcall WaitForUserPolicyForegroundProcessing()
100 stdcall -noname InitializeProfiles()
101 stdcall -noname CreateGroupA(str long)
102 stdcall -noname CreateGroupW(wstr long)
103 stdcall -noname DeleteGroupA(str long)
104 stdcall -noname DeleteGroupW(wstr long)
105 stdcall -noname AddItemA(str long str str str long str long long)
106 stdcall -noname AddItemW(wstr long wstr wstr wstr long wstr long long)
107 stdcall -noname DeleteItemA(str long str long)
108 stdcall -noname DeleteItemW(wstr long wstr long)
109 stdcall -noname CreateUserProfileA(ptr str)
110 stdcall -noname CreateUserProfileW(ptr wstr)
111 stdcall -noname CopyProfileDirectoryA(str str long)
112 stdcall -noname CopyProfileDirectoryW(wstr wstr long)
113 stdcall -noname AddDesktopItemA(long str str str long str long long)
114 stdcall -noname AddDesktopItemW(long wstr wstr wstr long wstr long long)
115 stdcall -noname DeleteDesktopItemA(long str)
116 stdcall -noname DeleteDesktopItemW(long wstr)
117 stdcall -stub -noname ApplyGroupPolicy(ptr)                            #stdcall -noname ApplyGroupPolicy(20)
118 stub -noname ShutdownGPOProcessing                                #stdcall -noname ShutdownGPOProcessing(4)
119 stub -noname CreateLinkFileA                                      #stdcall -noname CreateLinkFileA(40)
120 stub -noname CreateLinkFileW                                      #stdcall -noname CreateLinkFileW(40)
121 stub -noname DeleteLinkFileA                                      #stdcall -noname DeleteLinkFileA(16)
122 stub -noname DeleteLinkFileW                                      #stdcall -noname DeleteLinkFileW(16)
123 stub -noname CopyProfileDirectoryExA                              #stdcall -noname CopyProfileDirectoryExA(20)
124 stub -noname CopyProfileDirectoryExW                              #stdcall -noname CopyProfileDirectoryExW(20)
125 stub -noname GetSystemTempDirectoryA                              #stdcall -noname GetSystemTempDirectoryA(8)
126 stub -noname GetSystemTempDirectoryW                              #stdcall -noname GetSystemTempDirectoryW(8)
127 stub -noname MigrateNT4ToNT5                                      #stdcall -noname MigrateNT4ToNT5()
128 stub -noname ResetUserSpecialFolderPaths                          #stdcall -noname ResetUserSpecialFolderPaths()
129 stub -noname ApplySystemPolicyA                                   #stdcall -noname ApplySystemPolicyA(24)
130 stub -noname ApplySystemPolicyW                                   #stdcall -noname ApplySystemPolicyW(24)
131 stub -noname DetermineProfilesLocation                            #stdcall -noname DetermineProfilesLocation(4)
135 stub -noname PingComputer                                         #stdcall -noname PingComputer(8)
136 stub -noname CreateGroupExA                                       #stdcall -noname CreateGroupExA(16)
137 stub -noname CreateGroupExW                                       #stdcall -noname CreateGroupExW(16)
138 stub -noname CreateLinkFileExA                                    #stdcall -noname CreateLinkFileExA(48)
139 stub -noname CreateLinkFileExW                                    #stdcall -noname CreateLinkFileExW(48)
140 stub -noname InitializeUserProfile                                #stdcall -noname InitializeUserProfile()
#141 cdecl -noname RsopSidsFromToken@@YGJPAXPAPAU_TOKEN_GROUPS@@@Z
142 stdcall -noname GetUserSid(ptr)
143 stub -noname SecureUserProfiles                                   #stdcall -noname SecureUserProfiles()
144 stub -noname EnterUserProfileLock                                 #stdcall -noname EnterUserProfileLock(4)
145 stub -noname LeaveUserProfileLock                                 #stdcall -noname LeaveUserProfileLock(4)
146 stub -noname CheckAccessForPolicyGeneration                       #stdcall -noname CheckAccessForPolicyGeneration(20)
147 stub -noname GetGroupPolicyNetworkName                            #stdcall -noname GetGroupPolicyNetworkName(8)
148 stub -noname GetUserAppDataPathA                                  #stdcall -noname GetUserAppDataPathA(12)
149 stub -noname GetUserAppDataPathW                                  #stdcall -noname GetUserAppDataPathW(12)
150 stub -noname SignalUserPolicyForegroundProcessingDone             #stdcall -noname SignalUserPolicyForegroundProcessingDone()
151 stub -noname SignalMachinePolicyForegroundProcessingDone          #stdcall -noname SignalMachinePolicyForegroundProcessingDone()
152 stub -noname IsSyncForegroundPolicyRefresh                        #stdcall -noname IsSyncForegroundPolicyRefresh(8)
153 stdcall -noname CreateUserProfileExA(ptr str str str long long)
154 stdcall -noname CreateUserProfileExW(ptr wstr wstr wstr long long)
155 stdcall -noname CopySystemProfile(long)
156 stub -noname GetUserProfileDirFromSidA                            #stdcall -noname GetUserProfileDirFromSidA(12)
157 stub -noname GetUserProfileDirFromSidW                            #stdcall -noname GetUserProfileDirFromSidW(12)
158 stub -noname SetNextFgPolicyRefreshInfo                           #stdcall -noname SetNextFgPolicyRefreshInfo(12)
159 stub -noname TranslateNameXForest                                 #stdcall -noname TranslateNameXForest(20)
160 stub -noname AllocGpContainer                                     #stdcall -noname AllocGpContainer(60)
161 stub -noname AddGPO                                               #stdcall -noname AddGPO(84)
162 stub -noname GetWbemServices                                      #stdcall -noname GetWbemServices(20)
163 stub -noname FilterGPOs                                           #stdcall -noname FilterGPOs(8)
164 stub -noname ProcessMachAndUserGpoList                            #stdcall -noname ProcessMachAndUserGpoList(48)
165 stub -noname GPOExceptionFilter                                   #stdcall -noname GPOExceptionFilter(4)
166 stub -noname LogExtSessionStatus                                  #stdcall -noname LogExtSessionStatus(16)
167 stub -noname UpdateExtSessionStatus                               #stdcall -noname UpdateExtSessionStatus(16)
168 stub -noname UnloadGPExtensions                                   #stdcall -noname UnloadGPExtensions(4)
169 stub -noname FreeGpoInfo                                          #stdcall -noname FreeGpoInfo(4)
170 stub -noname LogSessionData                                       #stdcall -noname LogSessionData(8)
171 stub -noname LogGpoData                                           #stdcall -noname LogGpoData(4)
172 stub -noname ReadGPExtensions                                     #stdcall -noname ReadGPExtensions(4)
173 stub -noname CheckForSkippedExtensions                            #stdcall -noname CheckForSkippedExtensions(8)
174 stub -noname SetupGPOFilter                                       #stdcall -noname SetupGPOFilter(4)
175 stub -noname CheckXForestLogon                                    #stdcall -noname CheckXForestLogon(4)
200 stub -noname CreateURLFile                                        #stdcall -noname CreateURLFile(36)
201 stub -noname DeleteURLFile                                        #stdcall -noname DeleteURLFile(16)
