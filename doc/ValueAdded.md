# RTM Server C++ SDK API Docs: ValueAdded

[TOC]

### ValueAdded api



#### Translate

	//-- Sync Method
	int32_t translate(TranslatedInfo& translatedInfo, const string& text, TranslateLanguage destinationLanguage, TranslateLanguage sourceLanguage = None, TranslateType type = Chat, ProfanityType profanity = Off, int64_t userId = 0, int32_t timeout = 0);
	
	//-- Async Method
	void translate(const string& text, TranslateLanguage destinationLanguage, std::function<void (TranslatedInfo translatedInfo, int32_t errorCode)> callback, TranslateLanguage sourceLanguage = None, TranslateType type = Chat, ProfanityType profanity = Off, int64_t userId = 0, int32_t timeout = 0);

实时翻译

参数:

+ `text` 

  要翻译的文本

+ `destinationLanguage` 

  目标语言，参考：  [RTM Structures](Structures.md)

+ `sourceLanguage` 

  原始语言，参考：  [RTM Structures](Structures.md)

+ `type` 

  翻译的类别，参考：  [RTM Structures](Structures.md)

+ `profanity` 

  敏感词过滤的类别，参考：  [RTM Structures](Structures.md)

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  *  输出参数translatedInfo, 翻译结果，参考：  [RTM Structures](Structures.md)
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数translatedInfo, 翻译结果，参考：  [RTM Structures](Structures.md)



#### Profanity

	//-- Sync Method
	int32_t profanity(string& resultText, vector<string>& classification, const string& text, bool classify = false, int64_t userId = 0, int32_t timeout = 0);
	
	//-- Sync Method
	void profanity(const string& text, std::function<void (string resultText, vector<string> classification, int32_t errorCode)> callback, bool classify = false, int64_t userId = 0, int32_t timeout = 0);

敏感词过滤

参数:

+ `text` 

  原始文本

+ `classify` 

  是否进行分类

+ `userId` 

  用户id

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数resultText, 过滤结果
  * 输出参数classification, 分类结果
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数resultText, 过滤结果
  * 参数classification, 分类结果



#### Transcribe

	//-- Sync Method
	int32_t transcribe(string& resultText, string& resultLanguage, const string& audio, int64_t userId = 0, bool profanityFilter = false, int32_t timeout = 0);
	
	//-- Async Method
	void transcribe(const string& audio, std::function<void (string resultText, string resultLanguage, int32_t errorCode)> callback, int64_t userId = 0, bool profanityFilter = false, int32_t timeout = 0);

语音转文字

参数:

+ `audio` 

  语音私有二进制数据

+ `userId` 

  用户id

+ `profanityFilter` 

  是否进行敏感词过滤

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数resultText, 识别结果
  * 输出参数resultLanguage, 识别的语言
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数resultText, 识别结果
  * 参数resultLanguage, 识别的语言



#### TranscribeMessage

	//-- Sync Method
	int32_t transcribeMessage(string& resultText, string& resultLanguage, int64_t fromUid, int64_t mid, int64_t toId, MessageCategory messageCategory, bool profanityFilter = false, int32_t timeout = 0);
	
	//-- Async Method
	void transcribeMessage(int64_t fromUid, int64_t mid, int64_t toId, MessageCategory messageCategory, std::function<void (string resultText, string resultLanguage, int32_t errorCode)> callback, bool profanityFilter = false, int32_t timeout = 0);

语音消息识别

参数:

+ `fromUid` 

  用户id

+ `mid` 

  消息id

+ `toId` 

  groupId/roomId/userId

+ messageCategory

  消息类型

+ profanityFilter

  是否进行敏感词过滤

+ `int timeout`

  超时时间(秒)，默认0(使用全局设置)


返回值 & 输出参数:

+ 同步接口返回值为errorCode，FPNN_EC_OK 为成功，其他值为异常情况
  * 输出参数resultText, 识别结果
  * 输出参数resultLanguage, 识别的语言
+ 异步接口的lambda参数：
  * errorCode FPNN_EC_OK 为成功，其他值为异常情况
  * 参数resultText, 识别结果
  * 参数resultLanguage, 识别的语言


