.set noreorder

#include "pspimport.s"
IMPORT_START "sceAudio",0x40010000
IMPORT_FUNC  "sceAudio",0x8C1009B2,sceAudioOutput
IMPORT_FUNC  "sceAudio",0x136CAF51,sceAudioOutputBlocking
IMPORT_FUNC  "sceAudio",0xE2D56B2D,sceAudioOutputPanned
IMPORT_FUNC  "sceAudio",0x13F592BC,sceAudioOutputPannedBlocking
IMPORT_FUNC  "sceAudio",0x5EC81C55,sceAudioChReserve
IMPORT_FUNC  "sceAudio",0x41EFADE7,sceAudioOneshotOutput
IMPORT_FUNC  "sceAudio",0x6FC46853,sceAudioChRelease
IMPORT_FUNC  "sceAudio",0xE9D97901,sceAudioGetChannelRestLen
IMPORT_FUNC  "sceAudio",0xCB2E439E,sceAudioSetChannelDataLen
IMPORT_FUNC  "sceAudio",0x95FD0C2D,sceAudioChangeChannelConfig
IMPORT_FUNC  "sceAudio",0xB7E1D8E7,sceAudioChangeChannelVolume
IMPORT_FUNC  "sceAudio",0x38553111,sceAudioSRCChReserve
IMPORT_FUNC  "sceAudio",0x5C37C0AE,sceAudioSRCChRelease
IMPORT_FUNC  "sceAudio",0xE0727056,sceAudioSRCOutputBlocking
IMPORT_FUNC  "sceAudio",0x086E5895,sceAudioInputBlocking
IMPORT_FUNC  "sceAudio",0x6D4BEC68,sceAudioInput
IMPORT_FUNC  "sceAudio",0xA708C6A6,sceAudioGetInputLength
IMPORT_FUNC  "sceAudio",0x87B2E651,sceAudioWaitInputEnd
IMPORT_FUNC  "sceAudio",0x7DE61688,sceAudioInputInit
IMPORT_FUNC  "sceAudio",0xA633048E,sceAudioPollInputEnd
IMPORT_FUNC  "sceAudio",0xB011922F,sceAudioGetChannelRestLength
IMPORT_FUNC  "sceAudio",0xE926D3FB,sceAudioInputInitEx
IMPORT_FUNC  "sceAudio",0x01562BA3,sceAudioOutput2Reserve
IMPORT_FUNC  "sceAudio",0x2D53F36E,sceAudioOutput2OutputBlocking
IMPORT_FUNC  "sceAudio",0x43196845,sceAudioOutput2Release
IMPORT_FUNC  "sceAudio",0x63F2889C,sceAudioOutput2ChangeLength
IMPORT_FUNC  "sceAudio",0x647CEF33,sceAudioOutput2GetRestSample
IMPORT_FUNC  "sceAudio",0xA2BEAA6C,sceAudioSetFrequency
IMPORT_FUNC  "sceAudio",0x927AC32B,sceAudioSetVolumeOffset
IMPORT_FUNC  "sceAudio",0xB61595C0,sceAudioLoopbackTest

IMPORT_START "sceVaudio",0x40090000
IMPORT_FUNC  "sceVaudio",0x8986295E,sceVaudioOutputBlocking
IMPORT_FUNC  "sceVaudio",0x03B6807D,sceVaudioChReserve
IMPORT_FUNC  "sceVaudio",0x67585DFD,sceVaudioChRelease
IMPORT_FUNC  "sceVaudio",0x346fbe94,sceVaudioSetEffectType
IMPORT_FUNC  "sceVaudio",0xcbd4ac51,sceVaudioSetAlcMode
IMPORT_FUNC  "sceVaudio",0x504E4745,sceVaudio_504E4745
IMPORT_FUNC  "sceVaudio",0xE8E78DC8,sceVaudio_E8E78DC8
IMPORT_FUNC  "sceVaudio",0x27ACC20B,sceVaudio_27ACC20B

