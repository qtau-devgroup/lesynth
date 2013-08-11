#include "synth/lesynth/leSynth.h"
#include "synth/lesynth/leConfig.h"

#include <QDebug>

#include <QDir>
#include <QFile>
#include <QTextStream>


QString leSynth::name()        { return "Le Synth"; }
QString leSynth::description() { return "Le synthesizer pour QTau"; }
QString leSynth::version()     { return QString("%1.%2")
                                    .arg(CONST_LESYNTH_VER_MJ).arg(CONST_LESYNTH_VER_MN); }

bool leSynth::setVoicebank(QString path)
{
    bool result = false;
    QFile otoIni(path.append("/oto.ini"));

    if (otoIni.open(QFile::ReadOnly))
    {
        QTextStream reader(&otoIni);
        reader.setAutoDetectUnicode(true);
        QStringList otoStrings;

        while (!reader.atEnd())
            otoStrings << reader.readLine();

        vbCfg = otoFromStrings(otoStrings);
        qDebug() << "cfg:" << vbCfg.keys().length();
        result = !vbCfg.isEmpty();

        otoIni.close();
    }
    else
        qDebug() << "Le Synth could not open oto.ini from" << path;

    return result;

}

bool leSynth::setVocals(const ust &u)           { songCfg = u;                           return isVocalsReady(); }
bool leSynth::setVocals(QStringList ustStrings) { songCfg = ustFromStrings(ustStrings);  return isVocalsReady(); }

bool leSynth::resample(const qtauAudio &a)
{
    qDebug() << "Resampling now! I swear!";

    return false;
}

bool leSynth::resample(QString outFileName)
{
    // TODO:
    return false;
}

bool leSynth::isVbReady()         { return !vbCfg.isEmpty(); }
bool leSynth::isVocalsReady()     { return !songCfg.notes.isEmpty(); }
bool leSynth::supportsStreaming() { return false; }


Q_EXPORT_PLUGIN2(lesynth_resampler, leSynth)
