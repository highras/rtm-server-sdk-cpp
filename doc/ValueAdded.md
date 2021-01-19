# RTM Server C++ SDK API Docs: ValueAdded

[TOC]

### ValueAdded api



#### Translate

	//-- Sync Method
	int32_t translate(TranslatedInfo& translatedInfo, const string& text, TranslateLanguage destinationLanguage, TranslateLanguage sourceLanguage = None, TranslateType type = Chat, ProfanityType profanity = Off, int64_t userId = 0, int32_t timeout = 0);
	
	//-- Async Method
	void translate(const string& text, TranslateLanguage destinationLanguage, std::function<void (TranslatedInfo translatedInfo, int32_t errorCode)> callback, TranslateLanguage sourceLanguage = None, TranslateType type = Chat, ProfanityType profanity = Off, int64_t userId = 0, int32_t timeout = 0);

Translate text to target language

Parameters:

+ `text` 

  the text need to be translated

+ `destinationLanguage` 

  target language, refer [RTM Structures](Structures.md)

+ `sourceLanguage` 

  source language, refer [RTM Structures](Structures.md)

+ `type` 

  tranlste type, chat or mail, refer [RTM Structures](Structures.md)

+ `profanity` 

  profanity filter action, refer [RTM Structures](Structures.md)

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 0(global configuration)


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_OK for success
  *  output parameter translatedInfo, translation result, refer : [RTM Structures](Structures.md)
+ Async methond returns nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  * output parameter translatedInfo, translation result, refer : [RTM Structures](Structures.md)

#### SpeechToText

  // -- Sync Method
  int32_t speechToText(string& resultText, string& resultLanguage, const string& audio, int32_t autoType, const string& language, const string codec = "", int32_t sampleRate = 0, int64_t userId = 0, int32_t timeout = 120);
  // -- Async Method
  void speechToText(const string& audio, int32_t audioType, const string& language, std::function<void (string resultText, string resultLanguage, int32_t errorCode)> callback, const string codec = "", int32_t sampleRate = 0, int64_t userId = 0, int32_t timeout = 120);

Speech Recognition, convert speech to text

Parameters:

+ `audio` 

  audio content

+ `audioType` 

  audio type, 1 for url, 2 for audio content

+ `language` 

  source language, refer [RTM Structures](Structures.md)

+ `codec` 

  audio codec

+ `sampleRate` 

  audioSampleRate

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 120


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_OK for success
  *  output parameter resultText
  *  output parameter resultLanguage, refer : [RTM Structures](Structures.md)
+ Async methond returns nothing：
  * output parameter errorCode, FPNN_EC_OK for success
  *  output parameter resultText
  *  output parameter resultLanguage, refer : [RTM Structures](Structures.md)

#### TextCheck

  // -- Sync Method
  int32_t textCheck(TextCheckResult& result, const string& text, int64_t userId = 0, int32_t timeout = 120);
  // -- Async Method
  void textCheck(const string& text, std::function<void (TextCheckResult result, int32_t errorCode)> callback, int64_t userId = 0, int32_t timeout = 120);

Text Check 

Parameters:

+ `text` 

  The text need to be check.

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 120


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_OK for success
  *  output parameter result, TextCheckResult refer : [RTM Structures](Structures.md)
+ Async methond returns nothing：
  *  output parameter errorCode, FPNN_EC_OK for success
  *  output parameter result, TextCheckResult refer : [RTM Structures](Structures.md)

#### ImageCheck

  // -- Sync Method
  int32_t imageCheck(CheckResult& result, const string& image, int32_t imageType, int64_t userId = 0, int32_t timeout = 120);
  // -- Async Method
  void imageCheck(const string& image, int32_t imageType, std::function<void (CheckResult result, int32_t errorCode)> callback, int64_t userId = 0, int32_t timeout = 120);

Image Check

Parameters:

+ `image` 

  The image need to be checked.

+ `imageType`

  image type, 1 for url, 2 for image content

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 120


Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_OK for success
  *  output parameter result, CheckResult refer : [RTM Structures](Structures.md)
+ Async methond returns nothing：
  *  output parameter errorCode, FPNN_EC_OK for success
  *  output parameter result, CheckResult refer : [RTM Structures](Structures.md)


#### AudioCheck

  // -- Sync Method
  int32_t audioCheck(CheckResult& result, const string& audio, int32_t audioType, const string& language, const string codec = "", int32_t sampleRate = 0, int64_t userId = 0, int32_t timeout = 120);
  // -- Async Method
  void audioCheck(const string& audio, int32_t audioType, const string& language, std::function<void (CheckResult result, int32_t errorCode)> callback, const string codec = "", int32_t sampleRate = 0, int64_t userId = 0, int32_t timeout = 120);

Audio Check

Parameters:

+ `audio` 

  The audio need to be checked

+ `audioType` 

  audio type, 1 for url, 2 for audio content

+ `language` 

  source language, refer [RTM Structures](Structures.md)

+ `codec` 

  audio codec

+ `sampleRate` 

  audioSampleRate

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 120

Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_OK for success
  *  output parameter result, CheckResult refer : [RTM Structures](Structures.md)
+ Async methond returns nothing：
  *  output parameter errorCode, FPNN_EC_OK for success
  *  output parameter result, CheckResult refer : [RTM Structures](Structures.md)

#### VideoCheck

  // -- Sync Method
  int32_t videoCheck(CheckResult& result, const string& video, int32_t videoType, const string& videoName, int64_t userId = 0, int32_t timeout = 120);
  // -- Async Method
  void videoCheck(const string& video, int32_t videoType, const string& videoName, std::function<void (CheckResult result, int32_t errorCode)> callback, int64_t userId = 0, int32_t timeout = 120);

Video Check

Parameters:

+ `video` 

  The video need to be checked

+ `videoType` 

  video type, 1 for url, 2 for video content

+ `videoName` 

  video name

+ `userId` 

  user id

+ `int timeout`

  timeout in second，default 120

Return Value & Output Parameters

+ Sync method returns a int value, FPNN_EC_OK for success
  *  output parameter result, CheckResult refer : [RTM Structures](Structures.md)
+ Async methond returns nothing：
  *  output parameter errorCode, FPNN_EC_OK for success
  *  output parameter result, CheckResult refer : [RTM Structures](Structures.md)