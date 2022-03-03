/****************************************************************************
**                                MIT License
**
** Copyright (C) 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, author Giuseppe D'Angelo <giuseppe.dangelo@kdab.com>
**
** This file is part of KDToolBox (https://github.com/KDAB/KDToolBox).
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, ** and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice (including the next paragraph)
** shall be included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF ** CONTRACT, TORT OR OTHERWISE,
** ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
** DEALINGS IN THE SOFTWARE.
****************************************************************************/

#ifndef KDSIGNALTHROTTLER_H
#define KDSIGNALTHROTTLER_H

#include <QObject>
#include <QTimer>

#include <chrono>

namespace KDToolBox {

class KDGenericSignalThrottler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Kind kind READ kind CONSTANT)
    Q_PROPERTY(EmissionPolicy emissionPolicy READ emissionPolicy CONSTANT)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)
public:
    enum class Kind {
        Throttler,
        Debouncer,
    };
    Q_ENUM(Kind)

    enum class EmissionPolicy {
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
