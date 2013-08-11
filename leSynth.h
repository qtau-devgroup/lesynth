#ifndef LESYNTH_H
#define LESYNTH_H

#include <QObject>
#include "QTau/PluginInterfaces.h"
#include "tools/utauloid/oto.h"
#include "tools/utauloid/ust.h"


class leSynth : public QObject, public IResampler
{
    Q_OBJECT
    Q_INTERFACES(IResampler)

public:
    QString name();
    QString description();
    QString version();

    bool setVoicebank(QString path);

    bool setVocals(const ust &u);
    bool setVocals(QStringList ustStrings);

    bool resample(const qtauAudio &a);
    bool resample(QString outFileName);

    bool isVbReady();
    bool isVocalsReady();

    bool supportsStreaming();

protected:
    QOtoMap vbCfg;
    ust     songCfg;
};

#endif // LESYNTH_H
