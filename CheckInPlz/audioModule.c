#include <stdio.h>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "dr_wav.h"
#include <time.h>

#include "audioModule.h"


#define SAMPLE_FORMAT   ma_format_f32 //���� (�����) ����)
#define CHANNEL_COUNT   5 //����� ä�� ���� = (�ͼ� Ʈ�� ����)
#define SAMPLE_RATE     48000 // ���� ����Ʈ (�Ҹ��� ����Ƽ, ����Ʈ��)

//1-100
static int VM_bgmVolume;
static int VM_effectVolume;

static ma_device device;

static ma_decoder loopDecoder;

//���� ���ڴ��� �������, ���ڴ��� ��ȯ��Ű�� ������ ���� ��. 
static ma_decoder normDecoders[10];

static int decoderNowIndex = 0; //amount of times called -1


ma_decoder RecycleDecoders()
{
	if (decoderNowIndex >= 9)
	{
		ma_decoder_uninit(&(normDecoders[0]));
		decoderNowIndex = 0;
		return normDecoders[decoderNowIndex];
	}
	else
	{
		ma_decoder_uninit(&(normDecoders[decoderNowIndex + 1]));
		decoderNowIndex++;
		return normDecoders[decoderNowIndex];
	}
}

void CallbackDataLooping(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
	if (pDecoder == NULL) {
		return;
	}

	/* Reading PCM frames will loop based on what we specified when called ma_data_source_set_looping(). */
	ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

	(void)pInput;
}

void PlayAudioLoop(char* audioFileName)
{
	ma_result result;
	ma_device_config deviceConfig;
	

	//��� 0-1����.
	ma_device_set_master_volume(&device, ((float)VM_bgmVolume/(float)100.0f));

	result = ma_decoder_init_file(audioFileName, NULL, &loopDecoder);
	if (result != MA_SUCCESS) {
		return;
	}


	ma_data_source_set_looping(&loopDecoder, MA_TRUE);

	deviceConfig = ma_device_config_init(ma_device_type_playback);
	deviceConfig.playback.format = loopDecoder.outputFormat;
	deviceConfig.playback.channels = loopDecoder.outputChannels;
	deviceConfig.sampleRate = loopDecoder.outputSampleRate;
	deviceConfig.dataCallback = CallbackDataLooping;
	deviceConfig.pUserData = &loopDecoder;

	if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
		// printf("Failed to open playback device.\n");
		ma_decoder_uninit(&loopDecoder);
		return;
	}

	if (ma_device_start(&device) != MA_SUCCESS) {
		// printf("Failed to start playback device.\n");
		ma_device_uninit(&device);
		ma_decoder_uninit(&loopDecoder);
		return;
	}

	///�÷��̰� ���ӵ� �ð��� �ʿ�. EX. while.
	//printf("Press Enter to quit...");
	int isAudioLoopWorking = 0;
	while (isAudioLoopWorking != 1)
	{
		Sleep(1L);
	}
	///


	ma_device_uninit(&device);
	ma_decoder_uninit(&loopDecoder);
}

ma_uint32   g_decoderCount;
ma_decoder* g_pDecoders;
ma_bool32* g_pDecodersAtEnd;

ma_event g_stopEvent; /* <-- Signaled by the audio thread, waited on by the main thread. */

ma_bool32 CheckEndDecoders()
{
	ma_uint32 iDecoder;
	for (iDecoder = 0; iDecoder < g_decoderCount; ++iDecoder) {
		if (g_pDecodersAtEnd[iDecoder] == MA_FALSE) {
			return MA_FALSE;
		}
	}

	return MA_TRUE;
}

ma_uint32 read_and_mix_pcm_frames_f32(ma_decoder* pDecoder, float* pOutputF32, ma_uint32 frameCount)
{
	/*
	The way mixing works is that we just read into a temporary buffer, then take the contents of that buffer and mix it with the
	contents of the output buffer by simply adding the samples together. You could also clip the samples to -1..+1, but I'm not
	doing that in this example.
	*/
	ma_result result;
	float temp[4096];
	ma_uint32 tempCapInFrames = ma_countof(temp) / CHANNEL_COUNT;
	ma_uint32 totalFramesRead = 0;

	while (totalFramesRead < frameCount) {
		ma_uint64 iSample;
		ma_uint64 framesReadThisIteration;
		ma_uint32 totalFramesRemaining = frameCount - totalFramesRead;
		ma_uint32 framesToReadThisIteration = tempCapInFrames;
		if (framesToReadThisIteration > totalFramesRemaining) {
			framesToReadThisIteration = totalFramesRemaining;
		}

		result = ma_decoder_read_pcm_frames(pDecoder, temp, framesToReadThisIteration, &framesReadThisIteration);
		if (result != MA_SUCCESS || framesReadThisIteration == 0) {
			break;
		}

		/* Mix the frames together. */
		for (iSample = 0; iSample < framesReadThisIteration * CHANNEL_COUNT; ++iSample) {
			pOutputF32[totalFramesRead * CHANNEL_COUNT + iSample] += temp[iSample];
		}

		totalFramesRead += (ma_uint32)framesReadThisIteration;

		if (framesReadThisIteration < (ma_uint32)framesToReadThisIteration) {
			break;  /* Reached EOF. */
		}
	}

	return totalFramesRead;
}

void CallbackDataMix(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	float* pOutputF32 = (float*)pOutput;
	ma_uint32 iDecoder;

	MA_ASSERT(pDevice->playback.format == SAMPLE_FORMAT);   /* <-- Important for this example. */

	for (iDecoder = 0; iDecoder < g_decoderCount; ++iDecoder) {
		if (!g_pDecodersAtEnd[iDecoder]) {
			ma_uint32 framesRead = read_and_mix_pcm_frames_f32(&g_pDecoders[iDecoder], pOutputF32, frameCount);
			if (framesRead < frameCount) {
				g_pDecodersAtEnd[iDecoder] = MA_TRUE;
			}
		}
	}


	if (CheckEndDecoders()) {
		ma_event_signal(&g_stopEvent);
	}

	(void)pInput;
}

void MixAudio(int audioTrackCount, char** audioFileNameList)
{
	clock_t clockStart, clockEnd;

	clockStart = clock();


	//����̽��� ������ �ϳ��� ����, ����ϴ� ���ڴ��� ���� ����. 
	ma_result result;
	ma_decoder_config decoderConfig;
	ma_device_config deviceConfig;
	
	ma_uint32 iDecoder;

	//audioTrackCount�� ��ǲ ������ ������ �ְ�, 
	if (audioTrackCount < 1) {
		//��ǲ���� ����.
		return -1;
	}

	g_decoderCount = audioTrackCount; //���ڴ� ������� ����.
	g_pDecoders = (ma_decoder*)malloc(sizeof(*g_pDecoders) * g_decoderCount); //���ڴ��� �޸� ���� �Ҵ� 
	if (g_pDecoders == NULL)
	{
		return;
	}
	g_pDecodersAtEnd = (ma_bool32*)malloc(sizeof(*g_pDecodersAtEnd) * g_decoderCount); //���ڴ� �Ϸ� 
	if (g_pDecodersAtEnd == NULL)
	{
		return;
	}

	//��� ���ڴ����� �� ��쿡�� ���� ��� ������ ����� �Ѵ�. 
	decoderConfig = ma_decoder_config_init(SAMPLE_FORMAT, CHANNEL_COUNT, SAMPLE_RATE);
	for (iDecoder = 0; iDecoder < g_decoderCount; ++iDecoder)
	{
		result = ma_decoder_init_file(audioFileNameList[iDecoder], &decoderConfig, &g_pDecoders[iDecoder]);

		if (result != MA_SUCCESS)
		{
			ma_uint32 iDecoder2;
			for (iDecoder2 = 0; iDecoder2 < iDecoder; ++iDecoder2)
			{
				ma_decoder_uninit(&g_pDecoders[iDecoder2]);
			}
			free(g_pDecoders);
			free(g_pDecodersAtEnd);

			//printf("Failed to load %s.\n", audioFileNameList[1 + iDecoder]);
			return -3;
		}
		g_pDecodersAtEnd[iDecoder] = MA_FALSE;
	}

	/* �ϳ��� ����̽����� �����. ���ڴ��� �ݹ鿡�� �ͽ���. ������ ������ ���ڴ��� �����ؾ�  */
	deviceConfig = ma_device_config_init(ma_device_type_playback);
	deviceConfig.playback.format = SAMPLE_FORMAT;
	deviceConfig.playback.channels = CHANNEL_COUNT;
	deviceConfig.sampleRate = SAMPLE_RATE;
	deviceConfig.dataCallback = CallbackDataMix;
	deviceConfig.pUserData = NULL;

	if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
		for (iDecoder = 0; iDecoder < g_decoderCount; ++iDecoder) {
			ma_decoder_uninit(&g_pDecoders[iDecoder]);
		}
		free(g_pDecoders);
		free(g_pDecodersAtEnd);

		//�÷��̹� ����̽��� ���� ����.
		return -3;
	}



	//����� �����忡�� ���� ���� ����. �̺�Ʈ�� ����ؾ� ��.
	//���� �����忡�� �� �����带 ��ٸ���, ����� ������� ��ȣ�� �ѱ�.
	//����̽� ���� ���� �̿� ���� ���� �ؾ� ��. 
	//Context�� �̺�Ʈ �ʱ�ȭ�� ���� �䱸��. 
	ma_event_init(&g_stopEvent);


	//���� �÷��̹� ����, ����� �����尡 �׸� ����϶�� �Ҷ����� ��ٸ�. 
	if (ma_device_start(&device) != MA_SUCCESS) {
		ma_device_uninit(&device);
		for (iDecoder = 0; iDecoder < g_decoderCount; ++iDecoder) {
			ma_decoder_uninit(&g_pDecoders[iDecoder]);
		}
		free(g_pDecoders);
		free(g_pDecodersAtEnd);

		//printf("Failed to start playback device.\n");
		return -4;
	}

	//printf("Waiting for playback to complete...\n");
	ma_event_wait(&g_stopEvent);


	//���� ������, ����� �����尡 ����̽��� ���߶�� ��ȣ�ߴٴ� ���� �ǹ�. 
	ma_device_uninit(&device);


	//����, ������ ���� ���õ� �޸� ����. 
	for (iDecoder = 0; iDecoder < g_decoderCount; ++iDecoder) {
		ma_decoder_uninit(&g_pDecoders[iDecoder]);
	}

	free(g_pDecoders);
	free(g_pDecodersAtEnd);
}

//

void CallbackDataBasic(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
	if (pDecoder == NULL) {
		return;
	}

	ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

	(void)pInput;
}

void PlayAudio(const char* _audioFileName, float lastingSeconds)
{
	//AUDIO_StopAllAudio();
	clock_t clockStart, clockEnd;

	clockStart = clock();

	ma_result result;
	ma_decoder decoder;
	//ma_decoder* pntDecoder;
	ma_device_config deviceConfig;
	ma_device device;


	ma_device_set_master_volume(&device, ((float)VM_effectVolume / (float)100.0f));

	result = ma_decoder_init_file(_audioFileName, NULL, &decoder);

	if (result != MA_SUCCESS)
	{
		//������ ���� ���
		return -2;
	}


	deviceConfig = ma_device_config_init(ma_device_type_playback);
	deviceConfig.playback.format = decoder.outputFormat;
	deviceConfig.playback.channels = decoder.outputChannels;
	deviceConfig.sampleRate = decoder.outputSampleRate;
	deviceConfig.dataCallback = CallbackDataBasic;
	deviceConfig.pUserData = &decoder;

	if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS)
	{
		//����̽� �� ã�� ���
		ma_decoder_uninit(&decoder);
		return -3;
	}

	if (ma_device_start(&device) != MA_SUCCESS) {
		//����̽��� ���� ���� ���
		ma_device_uninit(&device);
		ma_decoder_uninit(&decoder);
		return -4;
	}
	//PlayAudio �Լ��� ���� ����Ǿ�� (���ӵǾ�� ����!)
	int isAudioPlayWorking = 0;
	while (isAudioPlayWorking != 1)
	{
		clockEnd = clock() - clockStart;
		float elapsedSeconds = ((float)clockEnd) / CLOCKS_PER_SEC;
		if (elapsedSeconds >= lastingSeconds)
		{
			break;
		}
		Sleep(1L);
	}


	//�����ϴ� �κ�, �ݵ�� �ʿ�.
	ma_device_uninit(&device);
	ma_decoder_uninit(&decoder);
	
}

typedef struct PlayAudioStruct
{
	const char* str_audioFileName;
	float str_lastingSeconds;

}PlayAudioStruct;

typedef struct PlayAudioLoopStruct
{
	const char* str_audioFileName;

}PlayAudioLoopStruct;

typedef struct MixAudioStruct
{
	int str_audioTrackCount;
	const char** str_audioFileNameList;
}MixAudioStruct;


DWORD CALLBACK ThreadProc_PlayAudio(LPVOID _lpParameter)
{
	PlayAudioStruct* pPlayAudioStruct = (PlayAudioStruct*)_lpParameter;
	
	PlayAudio(pPlayAudioStruct->str_audioFileName, pPlayAudioStruct->str_lastingSeconds);
	return 0;
}

DWORD CALLBACK ThreadProc_PlayAudioLoop(LPVOID _lpParameter)
{
	PlayAudioLoopStruct* pPlayAudioLoopStruct = (PlayAudioLoopStruct*)_lpParameter;

	//"Resources\/Sound\/";
	
	PlayAudioLoop(pPlayAudioLoopStruct->str_audioFileName);
	return 0;
}

DWORD CALLBACK ThreadProc_MixAudio(LPVOID _lpParameter)
{
	MixAudioStruct* pMixAudioStruct = (MixAudioStruct*)_lpParameter;
	MixAudio(pMixAudioStruct->str_audioTrackCount, pMixAudioStruct->str_audioFileNameList);
	return 0;
}

void AUDIO_PlayAudio(const char* _audioFileName, float lastingSeconds)
{
	DWORD threadID;
	DWORD hThread;

	
	PlayAudioStruct* playAudioStruct = (PlayAudioStruct*)malloc(sizeof(PlayAudioStruct));
	if (playAudioStruct == NULL)
	{
		return;
	}
	playAudioStruct->str_audioFileName = _audioFileName;
	playAudioStruct->str_lastingSeconds = lastingSeconds;

	hThread = CreateThread(NULL, 0, ThreadProc_PlayAudio, playAudioStruct, 0, &threadID);
	if (hThread == NULL)
	{
		return;
	}
	CloseHandle(hThread);
}

void AUDIO_PlayAudioLoop(const char* audioFileName)
{
	DWORD threadID;
	DWORD hThread;

	PlayAudioLoopStruct* playAudioLoopStruct = (PlayAudioLoopStruct*)malloc(sizeof(PlayAudioLoopStruct));
	if (playAudioLoopStruct == NULL)
	{
		return;
	}
	playAudioLoopStruct->str_audioFileName = audioFileName;
	hThread = CreateThread(NULL, 0, ThreadProc_PlayAudioLoop, playAudioLoopStruct, 0, &threadID);
	if (hThread == NULL)
	{
		return;
	}
	CloseHandle(hThread);
}

void AUDIO_MixAudio(int audioTrackCount, const char** audioFileNameList)
{
	DWORD threadID;
	DWORD hThread;

	MixAudioStruct* mixAudioStruct = (MixAudioStruct*)malloc(sizeof(MixAudioStruct));
	if (mixAudioStruct == NULL)
	{
		return;
	}
	mixAudioStruct->str_audioTrackCount = audioTrackCount;
	mixAudioStruct->str_audioFileNameList = audioFileNameList;
	hThread = CreateThread(NULL, 0, ThreadProc_MixAudio, mixAudioStruct, 0, &threadID);
	if (hThread == NULL)
	{
		return;
	}
	CloseHandle(hThread);
}





void AUDIO_SetBgmVolume(int vol)
{
	VM_bgmVolume = vol;
}

void AUDIO_SetEffectVolume(int vol)
{
	VM_effectVolume = vol;
}

int AUDIO_GetBgmVolume()
{
	return VM_bgmVolume;
}

int AUDIO_GetEffectVolume()
{
	return VM_effectVolume;
}

void AUDIO_StopAllAudio()
{
	ma_device_stop(&device);
}
