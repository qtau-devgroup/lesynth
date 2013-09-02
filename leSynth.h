#ifndef LESYNTH_H
#define LESYNTH_H

#include "editor/PluginInterfaces.h"
#include "tools/utauloid/oto.h"
#include "tools/utauloid/ust.h"


class leSynth : public QObject, public ISynth
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qtau.awesomesauce.ISynth" FILE "leSynth.json")
    Q_INTERFACES(ISynth)

public:
    QString name();
    QString description();
    QString version();

    void setup(SSynthConfig &cfg);
    bool setVoicebank(const QString &path);

    bool setVocals(const ust &u);
    bool setVocals(const QStringList &ust);

    bool synthesize(qtauAudioSource &a);
    bool synthesize(const QString &outFileName);

    bool isVbReady();
    bool isVocalsReady();

    bool supportsStreaming();

protected:
    vsLog*  log;
    QOtoMap vbCfg;
    ust     songCfg;

    inline void sLog(const QString &msg) { log->addMessage(msg, vsLog::success); }
    inline void dLog(const QString &msg) { log->addMessage(msg, vsLog::debug);   }
    inline void iLog(const QString &msg) { log->addMessage(msg, vsLog::info);    }
    inline void eLog(const QString &msg) { log->addMessage(msg, vsLog::error);   }
};

#endif // LESYNTH_H
