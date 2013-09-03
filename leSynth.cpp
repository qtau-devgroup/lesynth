#include "leSynth.h"
#include "leConfig.h"

#include "audio/Source.h"

#include <QDir>
#include <QFile>
#include <QTextStream>

float semitoneToFrequency[] = { 0, // skip index 0 since note numbers start from 1
    32.7,   34.6,   36.7,   38.9,   41.2,   43.7,   46.2,   49.0,   51.9,   55.0,   58.3,   61.7,    // 1st octave
    65.4,   69.3,   73.4,   77.8,   82.4,   87.3,   92.5,   98.0,   103.8,  110.0,  116.5,  123.5,   // 2nd
    130.8,  138.6,  146.8,  155.6,  164.8,  174.6,  185.0,  196.0,  207.7,  220.0,  233.1,  246.9,   // 3rd
    261.6,  277.2,  293.7,  311.1,  329.6,  349.2,  370.0,  392.0,  415.3,  440.0,  466.2,  493.9,   // 4th
    523.3,  554.4,  587.3,  622.3,  659.3,  698.5,  740.0,  784.0,  830.6,  880.0,  932.3,  987.8,   // 5th
    1046.5, 1108.7, 1174.7, 1244.5, 1318.5, 1396.9, 1480.0, 1568.0, 1661.2, 1760.0, 1864.7, 1975.5,  // 6th
    2093.0, 2217.5, 2349.3, 2489.0, 2637.0, 2793.8, 2960.0, 3136.0, 3322.4, 3520.0, 3729.3, 3951.1}; // 7th

QString leSynth::name()        { return "Le Synth"; }
QString leSynth::description() { return "Le synthesizer pour QTau"; }
QString leSynth::version()     { return QString("%1.%2")
                                    .arg(CONST_LESYNTH_VER_MJ).arg(CONST_LESYNTH_VER_MN); }

void leSynth::setup(SSynthConfig &cfg)
{
    log = cfg.log;
}

bool leSynth::setVoicebank(const QString &/*path*/)
{
/*  bool result = false;
    QFile otoIni(path + "/oto.ini");

    if (otoIni.open(QFile::ReadOnly))
    {
        QTextStream reader(&otoIni);
        reader.setAutoDetectUnicode(true);
        QStringList otoStrings;

        while (!reader.atEnd())
            otoStrings << reader.readLine();

        vbCfg = otoFromStrings(otoStrings);
        dLog(QString("configured with %1 oto keys").arg(vbCfg.keys().length()));
        result = !vbCfg.isEmpty();

        otoIni.close();
    }
    else
        eLog("Le Synth could not open oto.ini from " + path);

    return result; */ // no oto.ini reading currently, because tonal synth

    return true; // yesyesyes!
}

bool leSynth::setVocals(const ust &u)           { songCfg = u;                    return isVocalsReady(); }
bool leSynth::setVocals(const QStringList &ust) { songCfg = ustFromStrings(ust);  return isVocalsReady(); }

bool leSynth::synthesize(qtauAudioSource &a)
{
    bool result = false;

    if (a.isOpen())
        a.close();

    if (a.open(QIODevice::ReadWrite))
    {
        const int sampleRate      = 44100;
        const int channels        = 2;
        const int sampleSizeBits  = 16;
        const int sampleSizeBytes = 2;
        const int frameSizeBytes  = sampleSizeBytes * channels;

        QAudioFormat fmt = a.getAudioFormat();
        fmt.setByteOrder(QAudioFormat::LittleEndian);
        fmt.setSampleType(QAudioFormat::SignedInt);
        fmt.setCodec("audio/pcm");
        fmt.setSampleSize(sampleSizeBits);
        fmt.setSampleRate(sampleRate);
        fmt.setChannelCount(channels);
        a.setAudioFormat(fmt);

        float pulsesPerSecond = (float)songCfg.tempo / 60.f * MIDI_PPQ;
        int   pulseOffset  = 0;

        foreach (const ust_note &n, songCfg.notes)
        {
            if (n.pulseOffset > pulseOffset)
            {
                float silenceSeconds = (float)(n.pulseOffset - pulseOffset) / pulsesPerSecond;
                int   silenceSamples = silenceSeconds / sampleRate;
                a.write(QByteArray(silenceSamples * frameSizeBytes, '\0')); // write silence
            }

            SWavegenSetup genSetup((n.pulseLength * 1000) / pulsesPerSecond, semitoneToFrequency[n.keyNumber], sampleRate, true);
            qtauAudioSource as(genSetup, this);

            a.write(as.buffer());
            pulseOffset = n.pulseOffset + n.pulseLength;
        }

        a.close();
        result = a.size() > 0;
    }
    else eLog("LeSynth could not open audio for read/write, no synthesizing for you then.");

    return result;
}

bool leSynth::synthesize(const QString &outFileName)
{
    qtauAudioSource as;
    bool ok = synthesize(as);

    if (ok)
    {
        QFile f(outFileName);

        if (f.open(QFile::WriteOnly))
        {
            f.write(as.buffer());
            f.close();
            sLog("Synthesized to " + outFileName);
        }
        else
            ok = false;
    }

    return ok;
}

bool leSynth::isVbReady()         { return true; } //!vbCfg.isEmpty(); }
bool leSynth::isVocalsReady()     { return !songCfg.notes.isEmpty(); }
bool leSynth::supportsStreaming() { return false; }
