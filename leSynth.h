#ifndef LESYNTH_H
#define LESYNTH_H

#include "PluginInterfaces.h"
#include "utauloid/oto.h"
#include "utauloid/ust.h"


class leSynth : public QObject, public ISynth
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID c_isynth_comname FILE "leSynth.json")
    Q_INTERFACES(ISynth)

public:
    QString name()                              override;
    QString description()                       override;
    QString version()                           override;

    void setup(SSynthConfig &cfg)               override;
    bool setVoicebank(const QString &path)      override;

    bool setVocals(const ust &u)                override;
    bool setVocals(const QStringList &ust)      override;

    bool synthesize(qtauAudioSource &a)         override;
    bool synthesize(const QString &outFileName) override;

    bool isVbReady()                            override;
    bool isVocalsReady()                        override;

    bool supportsStreaming()                    override;

protected:
    vsLog*  log;
    QOtoMap vbCfg;
    ust     songCfg;

    inline void sLog(const QString &msg) { log->addMessage(msg, ELog::success); }
    inline void dLog(const QString &msg) { log->addMessage(msg, ELog::debug);   }
    inline void iLog(const QString &msg) { log->addMessage(msg, ELog::info);    }
    inline void eLog(const QString &msg) { log->addMessage(msg, ELog::error);   }
};

#endif // LESYNTH_H
