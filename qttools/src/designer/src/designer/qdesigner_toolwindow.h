// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef QDESIGNER_TOOLWINDOW_H
#define QDESIGNER_TOOLWINDOW_H

#include "mainwindow.h"

#include <QtCore/qpointer.h>
#include <QtGui/qfontdatabase.h>
#include <QtWidgets/qmainwindow.h>

QT_BEGIN_NAMESPACE

struct ToolWindowFontSettings {
    bool equals(const ToolWindowFontSettings &) const;

    QFont m_font;
    QFontDatabase::WritingSystem m_writingSystem{QFontDatabase::Any};
    bool m_useFont{false};
};

inline bool operator==(const ToolWindowFontSettings &tw1, const ToolWindowFontSettings &tw2)
{
    return tw1.equals(tw2);
}

inline bool operator!=(const ToolWindowFontSettings &tw1, const ToolWindowFontSettings &tw2)
{
    return !tw1.equals(tw2);
}

class QDesignerWorkbench;

/* A tool window with an action that activates it. Note that in toplevel mode,
 * the Widget box is a tool window as well as the applications' main window,
 * So, we need to inherit from MainWindowBase. */

class QDesignerToolWindow : public MainWindowBase
{
    Q_OBJECT
protected:
    explicit QDesignerToolWindow(QDesignerWorkbench *workbench,
                                 QWidget *w,
                                 const QString &objectName,
                                 const QString &title,
                                 const QString &actionObjectName,
                                 Qt::DockWidgetArea dockAreaHint,
                                 QWidget *parent = nullptr,
                                 Qt::WindowFlags flags = Qt::Window);

public:
    // Note: The order influences the dock widget position.
    enum StandardToolWindow { WidgetBox,  ObjectInspector, PropertyEditor,
                              ResourceEditor, ActionEditor, SignalSlotEditor,
                              StandardToolWindowCount };

    static QDesignerToolWindow *createStandardToolWindow(StandardToolWindow which, QDesignerWorkbench *workbench);

    QDesignerWorkbench *workbench() const;
    QAction *action() const;

    Qt::DockWidgetArea dockWidgetAreaHint() const { return m_dockAreaHint; }
    virtual QRect geometryHint(const QRect &availableGeometry) const = 0;

private slots:
    void showMe(bool);

protected:
    void showEvent(QShowEvent *e) override;
    void hideEvent(QHideEvent *e) override;
    void changeEvent(QEvent *e) override;

private:
    const Qt::DockWidgetArea m_dockAreaHint;
    QDesignerWorkbench *m_workbench;
    QAction *m_action;
};

QT_END_NAMESPACE

#endif // QDESIGNER_TOOLWINDOW_H
