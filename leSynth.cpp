#include "leSynth.h"
#include "leConfig.h"

#include <QDir>
#include <QFile>
#include <QTextStream>


QString leSynth::name()        { return "Le Synth"; }
QString leSynth::description() { return "Le synthesizer pour QTau"; }
QString leSynth::version()     { return QString("%1.%2")
                                    .arg(CONST_LESYNTH_VER_MJ).arg(CONST_LESYNTH_VER_MN); }

void leSynth::setup(SSynthConfig &cfg)
{
    log = cfg.log;
}

bool leSynth::setVoicebank(const QString &path)
{
    bool result = false;
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

    return result;

}

bool leSynth::setVocals(const ust &u)           { songCfg = u;                    return isVocalsReady(); }
bool leSynth::setVocals(const QStringList &ust) { songCfg = ustFromStrings(ust);  return isVocalsReady(); }

bool leSynth::synthesize(const qtauAudioSource &/*a*/)
{
    sLog("Resampling now! I swear!");
    return false;
}

bool leSynth::synthesize(const QString &/*outFileName*/)
{
    sLog("Resampling now! I swear!");
    return false;
}

bool leSynth::isVbReady()         { return !vbCfg.isEmpty(); }
bool leSynth::isVocalsReady()     { return !songCfg.notes.isEmpty(); }
bool leSynth::supportsStreaming() { return false; }
