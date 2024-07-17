/*
  This file is part of KDToolBox.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Giuseppe D'Angelo <giuseppe.dangelo@kdab.com>

  SPDX-License-Identifier: MIT
*/

#ifndef KDSIGNALTHROTTLER_H
#define KDSIGNALTHROTTLER_H

#include <QObject>
#include <QTimer>

#include <chrono>

namespace KDToolBox
{

class KDGenericSignalThrottler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Kind kind READ kind CONSTANT)
    Q_PROPERTY(EmissionPolicy emissionPolicy READ emissionPolicy CONSTANT)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)
public:
    enum class Kind
    {
        Throttler,
        Debouncer,
    };
    Q_ENUM(Kind)

    enum class EmissionPolicy
    {
        Trailing,
        Leading,
    };
    Q_ENUM(EmissionPolicy)

    explicit KDGenericSignalThrottler(Kind kind, EmissionPolicy emissionPolicy, QObject *parent = nullptr);
    ~KDGenericSignalThrottler() override;

    Kind kind() const;
    EmissionPolicy emissionPolicy() const;

    int timeout() const;
    void setTimeout(int timeout);
    void setTimeout(std::chrono::milliseconds timeout);

    void throttle();

Q_SIGNALS:
    void triggered();
    void timeoutChanged(int timeout);

private:
    void maybeEmitTriggered();
    void emitTriggered();

    QTimer m_timer;
    Kind m_kind;
    EmissionPolicy m_emissionPolicy;
    bool m_hasPendingEmission;
};

} // namespace KDToolBox

#endif // KDSIGNALTHROTTLER_H
